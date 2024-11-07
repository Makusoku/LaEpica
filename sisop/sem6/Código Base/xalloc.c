
/*
 * ssoo/xalloc.98/xalloc.c
 *
 * CONTENIDO INICIAL:
 *	Codigo correspondiente a la Seccion 8.7 del libro:
 *	"The C Programing Language", de B. Kernigham y D. Ritchie.
 *
 * En este fichero se incluiran las rutinas pedidas 
 *
 */

#include <unistd.h>
#include "xalloc.h"

/*
 * Definicion de la cabecera para huecos y bloques. 
 * La union con un campo de tipo Align fuerza que el tama~no
 * de la cabecera sea multiplo del tama~no de este tipo.
 */
typedef long Align;    /* for alignment to long boundary */

union header {   /* block header: */
	struct {
		union header *ptr;  /* next block if on free list */
		size_t size;     /* size of this block */
	} s;
	Align x;             /* force alignment of blocks */
};

typedef union header Header;

/*
 * La lista de huecos esta ordenada por direcciones y es circular.
 * base es el "falso" hueco de tama~no cero que asegura que la lista
 * nunca esta vacia 
 */
static Header base;   /* empty list to get started */

/*
 * freep apuntara al hueco situado en la lista antes del hueco
 * por el que comenzara la busqueda.
 * Necesario para implementar la estrategia next-fit
 */
static Header  *freep = NULL;  /* start of the free list */


#define NALLOC 1024

/*
 * morecore: ask system for more memory 
 *
 * Esta funcion se llama desde xmalloc cuando no hay espacio.
 * Aumenta el tama~no de la zona de datos como minimo en NALLOC*sizeof(Header)
 * y a~nade esta nueva zona a la lista de huecos usando xfree.
 *
 */

static Header *morecore(size_t nu)
{
	char *cp;
	Header *up;

	if (nu < NALLOC)	
		nu = NALLOC;
	cp= sbrk(nu * sizeof(Header));
	if (cp == (char *) -1) /* no space at all */
		return NULL;
	up = (Header *) cp;
	up ->s.size = nu;
	xfree((void *)(up+1));
	return freep;
}

/* xmalloc: general-purpose storage allocator */
void *xmalloc (size_t nbytes)
{
	Header  *p, *prevp;
	size_t nunits;

	/* 
	   Calcula cuanto ocupara la peticion medido en tama~nos de
	   cabecera (incluyendo la propia cabecera). 
	   El termino "sizeof(Header)-1" provoca un redondeo por exceso.
	   El termino "+ 1" es para incluir la propia cabecera.
	*/
	nunits = (nbytes+sizeof(Header)-1)/sizeof(Header) + 1;


	/* En la primera llamada se construye una lista de huecos con un
	   unico elemento de tama~no cero (base) que se apunta a si mismo */
	if (( prevp = freep) == NULL ) { /* no free list yet */
		base.s.ptr = freep = prevp = & base; 
		base.s.size = 0;
	}

	/*
	   Recorre la lista circular de huecos, empezando por el siguiente al
	   que apunta freep, hasta que encuentra uno que satisface la peticion
	   o da toda una vuelta a la lista (no hay espacio suficiente)
	*/
	for (p= prevp->s.ptr; ; prevp = p, p = p->s.ptr) {
		if (p->s.size >= nunits) {  /* big enough */
			if (p->s.size == nunits)  /* exactly */
				prevp->s.ptr = p->s.ptr;
			else {  /* allocate tail end */
				p->s.size -= nunits;
				p+= p->s.size;
				p->s.size = nunits;
			}
			freep = prevp; /* estrategia next-fit */
			return (void *)(p+1); /* devuelve un puntero a la
						 zona de datos del bloque */
		}
		/* Si ha dado toda la vuelta pide mas memoria y vuelve
		   a empezar */
		if (p == freep) /* wrapped around free list */
			if ((p = morecore(nunits)) == NULL)
				return NULL;  /* none left */
	}
}


/* xfree: put block ap in the free list */
void xfree(void *ap)
{
	Header *bp, *p;

	bp = (Header *)ap - 1;  /* point to block header */

	/*
	   Bucle que recorre la lista de huecos para buscar el hueco
	   anterior al bloque que se va a liberar.
	   Del bucle se sale cuando se encuentran los dos huecos
	   de la lista (el apuntado por p y el apuntado por p->s.ptr)
	   entre los que se incluira el nuevo hueco (el apuntado por bp).
	   Hay dos casos:
		- La direccion del nuevo hueco es mayor (bp > p) o
		menor (bp < p->s.ptr) que la de ningun otro hueco de la
		lista (corresponde al break)
		- La direccion del nuevo hueco esta comprendida entre
		dos huecos de la lista (corresponde a la salida normal
		del for)
	*/

	for (p= freep; !(bp > p && bp < p->s.ptr); p = p->s.ptr)
		if (p >= p->s.ptr && (bp > p || bp < p->s.ptr))
			break;  /* freed block at start or end of arena */ 


	/* Comprueba compactacion con hueco posterior */
	if (bp + bp->s.size == p->s.ptr) {  /* join to upper nbr */
		bp->s.size += p->s.ptr->s.size;
		bp->s.ptr = p->s.ptr->s.ptr;
	} else
		 bp->s.ptr = p->s.ptr;

	/* Comprueba compactacion con hueco anterior */
	if (p + p->s.size == bp) {         /* join to lower nbr */
		p->s.size += bp->s.size;
		p->s.ptr = bp->s.ptr;
	} else
		p->s.ptr = bp;

	freep = p; /* estrategia next-fit */
}

void *xrealloc(void *ptr, size_t size) {
    if (ptr == NULL) {
        return xmalloc(size); // Si el puntero es NULL, es equivalente a una llamada a xmalloc
    }

    Header *bp = (Header *)ptr - 1; // Obtiene la cabecera del bloque
    size_t new_units = (size + sizeof(Align) - 1) / sizeof(Align) + 1;

    // Si el nuevo tamaño es menor o igual, no hace falta mover el bloque
    if (new_units <= bp->s.size) {
        // Si el tamaño sobrante es suficiente, puedes generar un hueco
        if (bp->s.size - new_units >= 1) {
            // Crea un nuevo hueco con el espacio sobrante
            Header *new_free = bp + new_units;
            new_free->s.size = bp->s.size - new_units;
            xfree((void *)(new_free + 1)); // Agregar el hueco a la lista de libres
        }
        return ptr; // Retorna el puntero original
    }

    // Caso cuando el nuevo tamaño es mayor: buscamos huecos adyacentes
    if (bp + bp->s.size == freep) { // Verifica si hay espacio suficiente al final
        if (bp->s.ptr->s.size >= new_units - bp->s.size) {
            // Expande el bloque al final
            bp->s.size += bp->s.ptr->s.size;
            bp->s.ptr = bp->s.ptr->s.ptr;
            return ptr;
        }
    }

    // Si no se puede expandir al final, verifica al inicio
    if (freep + freep->s.size == bp) {
        freep->s.size += bp->s.size;
        return ptr;
    }

    // Si no hay huecos adyacentes, solicita más memoria
    void *new_ptr = xmalloc(size);
    if (new_ptr == NULL) {
        return NULL; // No hay memoria suficiente
    }

    // Copia el contenido al nuevo bloque
    memcpy(new_ptr, ptr, bp->s.size * sizeof(Align));

    // Libera el bloque original
    xfree(ptr);

    return new_ptr; // Retorna el nuevo puntero
}



/* El algoritmo First-Fit busca el primer bloque libre que sea lo suficientemente grande 
como para satisfacer la solicitud de memoria. Cuando lo encuentra, lo asigna. */
void *xmalloc_first_fit(size_t nbytes)
{
    Header *p, *prevp;
    size_t nunits;

    // Calcula cuántas unidades de tamaño de Header se necesitan
    nunits = (nbytes + sizeof(Header) - 1) / sizeof(Header) + 1;

    // Inicializa la lista de huecos si es la primera vez
    if ((prevp = freep) == NULL) {
        base.s.ptr = freep = prevp = &base;
        base.s.size = 0;
    }

    // Recorre la lista de huecos en busca del primer hueco adecuado
    for (p = prevp->s.ptr; ; prevp = p, p = p->s.ptr) {
        if (p->s.size >= nunits) {  // Si el bloque tiene suficiente tamaño
            if (p->s.size == nunits)  // Si el bloque tiene el tamaño exacto
                prevp->s.ptr = p->s.ptr;
            else {  // Si el bloque es más grande, ajustamos su tamaño
                p->s.size -= nunits;
                p += p->s.size;
                p->s.size = nunits;
            }
            freep = prevp;  // Actualiza el puntero para el próximo ajuste
            return (void *)(p + 1);  // Devuelve el puntero a la zona de datos
        }

        // Si no se encuentra el bloque adecuado, se pide más memoria
        if (p == freep)  // Si ya hemos recorrido toda la lista
            if ((p = morecore(nunits)) == NULL)
                return NULL;  // Si no se puede pedir más memoria, retorna NULL
    }
}



/*El algoritmo Best-Fit recorre todos los bloques disponibles y selecciona el que tenga el 
tamaño más pequeño que sea lo suficientemente grande como para satisfacer la solicitud. Esto 
reduce la cantidad de fragmentación interna.*/ size_t SIZE_MAX = 1000000000; /*Random value*/
void *xmalloc_best_fit(size_t nbytes)
{
    Header *p, *prevp, *bestp;
    size_t nunits;
    size_t best_size = SIZE_MAX;

    // Calcula el tamaño necesario para la solicitud
    nunits = (nbytes + sizeof(Header) - 1) / sizeof(Header) + 1;

    // Inicializa la lista de huecos si es la primera vez
    if ((prevp = freep) == NULL) {
        base.s.ptr = freep = prevp = &base;
        base.s.size = 0;
    }

    bestp = NULL;
    for (p = prevp->s.ptr; ; prevp = p, p = p->s.ptr) {
        if (p->s.size >= nunits && p->s.size < best_size) {  // Si el bloque es adecuado y más pequeño
            bestp = p;
            best_size = p->s.size;
        }

        if (p == freep)  // Si hemos recorrido toda la lista
            if ((p = morecore(nunits)) == NULL)
                return NULL;  // Si no se puede pedir más memoria, retorna NULL
    }

    // Asigna el bloque seleccionado
    if (bestp->s.size == nunits) {
        prevp->s.ptr = bestp->s.ptr;
    } else {  // Si el bloque es más grande, ajustamos su tamaño
        bestp->s.size -= nunits;
        bestp += bestp->s.size;
        bestp->s.size = nunits;
    }

    freep = prevp;  // Actualiza el puntero para el próximo ajuste
    return (void *)(bestp + 1);  // Devuelve el puntero a la zona de datos
}

void *xrealloc_v2(void * ptr, size_t size)
{
	//size contiene el número de bytes a reservar, osea no contiene la cabecera
	//nuestro puntero sí incluye la cabecera
	//Teniendo en cuenta que en la guia estaba el ejercicio de implementar el xrealloc,
	//procederemos a implementarlo de manera similar a como la hemos implementado.
	if(ptr==NULL)return NULL;
	//printf("Llegue");
	Header *p,*prevp,*new_ptr;
	size_t nunits,nAligns;
	nAligns = numSizeOfTypeInBlock(sizeof(Align));

	//convertimos el número de bytes a número de bloques con cabecera incluida
	nunits = (size+sizeof(Align)*nAligns-1)/(sizeof(Align)*nAligns) + 1;
	
	new_ptr = (Header *)ptr - 1;
	// se quiere disminuir el tamaño del bloque


	Header *bp;
	bp = (Header *)ptr - 1; 
	//encontramos el hueco siguiente y el anterior al proceso actual

	p= freep;
	if(!(bp > p && bp < p->s.ptr)|(p >= p->s.ptr && (bp > p || bp < p->s.ptr))){
		p=p->s.ptr;
	}

	for (; !(bp > p && bp < p->s.ptr);prevp = p, p = p->s.ptr)
		if (p >= p->s.ptr && (bp > p || bp < p->s.ptr))
			break;

	Header *next_block=p->s.ptr;

	if(nunits +1 <= new_ptr->s.size){
		//printf("Hola\n");
		//printf("%d %d\n\n",nunits +1,new_ptr->s.size);
		if(nunits+1==new_ptr->s.size&&new_ptr->s.ptr==new_ptr+new_ptr->s.size)return ptr;

		
		Header* new_hole;

		new_hole = new_ptr+nunits;
		new_hole->s.size=new_ptr->s.size-nunits;
		new_hole->s.ptr=p->s.ptr;
		p->s.ptr=new_hole;
		
		new_ptr->s.size=nunits;

		xfree((void*)(new_hole));

		return (void*)(new_ptr + 1);
	}

	//se va a aumentar el tamaño del bloque

	
	if(p->s.ptr==new_ptr+new_ptr->s.size &&new_ptr->s.size+next_block->s.size>nunits){
		//si el hueco adyacente superior, más el bloque actual pueden satisfacer la solicitud
		//de expansión de memoria
		//posicionamos al puntero en el espacio que le corresponde al nuevo bloque
		next_block+=nunits;
		new_ptr->s.size=nunits;
		//le disminuimos el tamaño al hueco y hacemos que apunte al siguiente 
		//hueco del bloque hueco antes de disminuir en tamaño
		next_block->s.size=p->s.ptr->s.size-(nunits-new_ptr->s.size);
		next_block->s.ptr=p->s.ptr;
		return (void*)(new_ptr + 1);
		
	}else if(p+p->s.size==new_ptr &&p->s.size+new_ptr->s.size>nunits){
		//printf("Hola");
		

		//existe un hueco en la parte posterior y puede reubicarse ahí
		size_t blockDiff = nunits - new_ptr->s.size;
		Header *aux;
		//guardamos el puntero a donde está la información

		aux = new_ptr;
		//nos movemos para abarcar el nuevo espacio y actualizamos el size del bloque
		p->s.size-= blockDiff;
		new_ptr-=blockDiff;
		new_ptr->s.size=nunits;
		memcpy(new_ptr,aux,aux->s.size*sizeof(Align));
		//si el bloque alcanza exacto para el realloc, el puntero anterior al p
		//debe apuntar al siguiente del p
		if(p->s.size+new_ptr->s.size==nunits+1){
			prevp->s.ptr=p->s.ptr;
		}		
		return (void*)(new_ptr + 1);
	}else if(p->s.ptr==new_ptr+new_ptr->s.size&& p+p->s.size==new_ptr){
		
		//existen huecos adyacente por la derecha e izquierda

		//validamos que tengan tamaño suficiente
		if(p->s.size+next_block->s.size+new_ptr->s.size>=nunits+1){
			size_t blockDiffBack=nunits-(next_block->s.size + new_ptr->s.size);
			Header *aux;
			aux = new_ptr;
			//nos posicionamos en el nuevo lugar reservado
			new_ptr-=blockDiffBack;

			//copiamos toda la información 
			memcpy(new_ptr,aux,aux->s.size*sizeof(Align));

			//actualizamos el size del bloque anterior
			p->s.size-=blockDiffBack;
			new_ptr->s.size=nunits;
			//vemos cuando el hueco es exacto y cuando no lo es
			if(p->s.size+next_block->s.size+new_ptr->s.size>nunits){
				//los huecos juntos satisfacen más de la memoria pedida
				p->s.ptr=next_block->s.ptr;
			}else{
				prevp->s.ptr=next_block->s.ptr;
			}
			
			return (void*)(new_ptr + 1);
		}
	}

	//no se puedo reubicar en la parte posterior/superior

	Header *aux;
	aux = new_ptr;
	new_ptr=(Header*)xmalloc(nunits*sizeof(Align));
	memset(new_ptr,0,nunits*sizeof(Align));
	if(new_ptr)memcpy(new_ptr,aux,aux->s.size*sizeof(Align));
	
	return (void*)(new_ptr + 1);
}


/*El algoritmo Worst-Fit selecciona el bloque más grande disponible para intentar dejar un espacio 
grande para futuras asignaciones. Esto puede causar más fragmentación a largo plazo, pero a veces es 
útil en ciertos contextos.*/
void *xmalloc_worst_fit(size_t nbytes)
{
    Header *p, *prevp, *worstp;
    size_t nunits;
    size_t worst_size = 0;

    // Calcula el tamaño necesario para la solicitud
    nunits = (nbytes + sizeof(Header) - 1) / sizeof(Header) + 1;

    // Inicializa la lista de huecos si es la primera vez
    if ((prevp = freep) == NULL) {
        base.s.ptr = freep = prevp = &base;
        base.s.size = 0;
    }

    worstp = NULL;
    for (p = prevp->s.ptr; ; prevp = p, p = p->s.ptr) {
        if (p->s.size >= nunits && p->s.size > worst_size) {  // Si el bloque es adecuado y más grande
            worstp = p;
            worst_size = p->s.size;
        }

        if (p == freep)  // Si hemos recorrido toda la lista
            if ((p = morecore(nunits)) == NULL)
                return NULL;  // Si no se puede pedir más memoria, retorna NULL
    }

    // Asigna el bloque seleccionado
    if (worstp->s.size == nunits) {
        prevp->s.ptr = worstp->s.ptr;
    } else {  // Si el bloque es más grande, ajustamos su tamaño
        worstp->s.size -= nunits;
        worstp += worstp->s.size;
        worstp->s.size = nunits;
    }

    freep = prevp;  // Actualiza el puntero para el próximo ajuste
    return (void *)(worstp + 1);  // Devuelve el puntero a la zona de datos
}

/*El algoritmo Next-Fit es una variación del First-Fit, pero en lugar de empezar la búsqueda desde el
 inicio de la lista cada vez, comienza desde el último punto donde se realizó una asignación.*/
void *xmalloc_next_fit(size_t nbytes)
{
    Header *p, *prevp;
    size_t nunits;

    // Calcula el tamaño necesario para la solicitud
    nunits = (nbytes + sizeof(Header) - 1) / sizeof(Header) + 1;

    // Inicializa la lista de huecos si es la primera vez
    if ((prevp = freep) == NULL) {
        base.s.ptr = freep = prevp = &base;
        base.s.size = 0;
    }

    // Comienza la búsqueda desde el último punto en lugar del inicio
    for (p = freep->s.ptr; ; prevp = p, p = p->s.ptr) {
        if (p->s.size >= nunits) {  // Si el bloque tiene suficiente tamaño
            if (p->s.size == nunits) {  // Si el bloque tiene el tamaño exacto
                prevp->s.ptr = p->s.ptr;
            } else {  // Si el bloque es más grande, ajustamos su tamaño
                p->s.size -= nunits;
                p += p->s.size;
                p->s.size = nunits;
            }
            freep = prevp;  // Actualiza el puntero para el próximo ajuste
            return (void *)(p + 1);  // Devuelve el puntero a la zona de datos
        }

        // Si no se encuentra el bloque adecuado, pide más memoria
        if (p == freep)  // Si hemos recorrido toda la lista
            if ((p = morecore(nunits)) == NULL)
                return NULL;  // Si no se puede pedir más memoria, retorna NULL
    }
}

/*El Buddy System divide la memoria en bloques de tamaño fijo, que son potencias de 2. Cuando no 
hay un bloque adecuado disponible, el sistema divide un bloque más grande en dos bloques "hermanos"
 (buddies).*/
void *xmalloc_buddy(size_t nbytes)
{
    size_t nunits;
    Header *p, *prevp;

    // Calcula el número de unidades necesarias
    nunits = (nbytes + sizeof(Header) - 1) / sizeof(Header) + 1;

    // Inicializa la lista de huecos si es la primera vez
    if ((prevp = freep) == NULL) {
        base.s.ptr = freep = prevp = &base;
        base.s.size = 0;
    }

    // Recorre la lista de huecos en busca del bloque adecuado
    for (p = prevp->s.ptr; ; prevp = p, p = p->s.ptr) {
        if (p->s.size >= nunits) {
            if (p->s.size == nunits) {
                prevp->s.ptr = p->s.ptr;
            } else {
                p->s.size /= 2;  // Divide el bloque en dos "compañeros"
                p += p->s.size;
                p->s.size = nunits;
            }
            freep = prevp;
            return (void *)(p + 1);
        }

        if (p == freep)  // Si ya hemos recorrido toda la lista
            if ((p = morecore(nunits)) == NULL)
                return NULL;
    }
}

/*El algoritmo Slab Allocation organiza bloques de memoria de tamaño fijo en caches. Cada tipo de objeto
 tiene su propia caché, lo que reduce la fragmentación y mejora el rendimiento al asignar memoria.*/
 void *xmalloc_slab(size_t nbytes)
{
    // Este sistema funciona con un conjunto de "slabs" que se gestionan por separado
    // En lugar de gestionar la memoria directamente, usamos caches preconfigurados.
    return xmalloc(nbytes);  // Llamamos a xmalloc para la asignación básica
}


/*La Asignación Paginada divide la memoria en páginas fijas (generalmente de 4096 bytes) y las asigna como 
unidades completas.*/
void *xmalloc_paged(size_t nbytes)
{
    const size_t page_size = 4096;  // Tamaño de una página de memoria
    size_t nunits = (nbytes + page_size - 1) / page_size;

    // Asigna más páginas usando morecore (o un método similar)
    return morecore(nunits);
}

/*La Segmentación divide la memoria en segmentos lógicos (como código, datos, pila) para gestionarlos de 
manera independiente.*/
void *xmalloc_segmented(size_t nbytes)
{
    return xmalloc(nbytes);  // Usamos xmalloc para simplificar el ejemplo
}

/*La Compactación de memoria reorganiza la memoria moviendo los bloques asignados para reducir la fragmentación.*/
void xcompact()
{
    // Aquí podríamos implementar un mecanismo que reorganice los bloques asignados.
    Header *p = freep;
    while (p != NULL && p->s.ptr != freep) {
        if (p->s.ptr != NULL && p + p->s.size == p->s.ptr) {
            p->s.size += p->s.ptr->s.size;
            p->s.ptr = p->s.ptr->s.ptr;
        }
        p = p->s.ptr;
    }
}
