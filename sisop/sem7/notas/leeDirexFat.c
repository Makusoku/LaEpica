#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>
#include <math.h>
#include "exFATstruct.h"

#define SIZE 32

char name[500];
int contCpy;
void continuarImpresion(const char *entry){
    int dobCero=0,i;
    for(i = 2 ;i< 32;i ++){
        if(dobCero==2) break;
        if(entry[i]!=0){
            name[contCpy] = entry[i];
            contCpy++;
            dobCero=0;
        }
        else{
            dobCero++;
        }   
    }
    name[contCpy] = '\0';
}
void printNameDirect(const char *entry){
    int dobCero=0,i;
    contCpy=0;
    for(i = 2 ;i< 32;i ++){
        if(dobCero==2) break;
        if(entry[i]!=0){
            name[contCpy] = entry[i];
            contCpy++;
            dobCero=0;
        }
        else{
            dobCero++;
        }   
    }
    name[contCpy] = '\0';
}

void readRootDir(const char *image_file){
    int fd, n1, n2;
    exFatBootSector boot;
    char entry[SIZE];

    if((fd = open(image_file, O_RDONLY)) < 0){
        perror("No se pudo abrir la imagen del disco\n");
        exit(1);
    }

    if(read(fd, &boot, sizeof(boot) ) < 0){
        perror("No se pudo leer el sector de arranque del disco\n");
        exit(1);
    }
    printf("La data inicia en el sector: %d\n", boot.ClusterHeapOffset);
    n1 = boot.BytePerSector;
    printf("El tamaño de un sector en bytes es de: %d\n", (int)pow(2.0, n1));
    n2 = boot.SectorPerCluster;
    printf("El tamaño de sectores por cluster es de: %d\n", (int)pow(2.0, n2));
    printf("El directorio raiz se encuentra en el cluster: %d\n", boot.RootDirFirstCluster);
    printf("Archivos y/o directorios contenidos en el directorio raiz\n");
    int bytes_per_sector = 1 << boot.BytePerSector;
    int sectors_per_cluster = 1 << boot.SectorPerCluster;

    long rootDirOffset = (boot.ClusterHeapOffset * bytes_per_sector)+((boot.RootDirFirstCluster-2) * bytes_per_sector * sectors_per_cluster);

    if(lseek(fd, rootDirOffset, SEEK_SET)< 0){
        perror("Error al mover el puntero del archivo al inicio del del roorDir\n");
        close(fd);
        exit(1);
    }

    printf("Estamos en la posicion: %ld\n", rootDirOffset);
    printf("\nNombres de los archivos y/o directorios en el directorio raiz\n");;
    int anterC1 = 0;
    while(read(fd, entry, SIZE) == SIZE){
        if((unsigned char)entry[0] == 0x00) break;
        if((unsigned char)entry[0] == 0xC1){
            if((unsigned char)entry[0] == 0x83){
                printNameDirect(entry);
                printf("- %s\n", name);
                memset(name,0,sizeof(name));
                anterC1=0;
            }
            else if((unsigned char)entry[0] == 0xC1){
                if(anterC1 == 1){
                    continuarImpresion(entry);
                }
                else{
                    printNameDirect(entry);
                    anterC1=1;
                }
                continue;
            }
        }
        else if(anterC1==1){
            printf("- %s\n", name);
            contCpy=0;
            memset(name,0,sizeof(name));
        }
        anterC1=0;
    }
    close(fd);
    return;    
}



void main(int argc, char *argv[]){
    int fd;

    char *image_file = argv[1];
    
    readRootDir(image_file);

    exit(1);
}


/*

El código que has proporcionado es un programa en C que lee y muestra los nombres de archivos o directorios de un sistema de archivos **exFAT** desde una imagen de disco (un archivo binario que simula un disco). Este programa se centra en la lectura del directorio raíz del sistema exFAT. A continuación te explico las principales secciones del código:

### 1. **Estructuras y Definiciones**

```c
#define SIZE 32
char name[500];
int contCpy;
```
- `SIZE` se define como 32, que es el tamaño de cada entrada de directorio en exFAT.
- `name` es un arreglo de caracteres (cadena de texto) que se utiliza para almacenar el nombre de los archivos o directorios leídos.
- `contCpy` es un contador usado para ir almacenando el nombre de los archivos/directorios.

### 2. **Funciones para Extraer y Mostrar Nombres de Archivos/Directorios**

#### `continuarImpresion(const char *entry)`
Esta función procesa la entrada de un archivo o directorio en la que ya se ha comenzado a imprimir el nombre. El objetivo es continuar la impresión del nombre, concatenando los caracteres del nombre cuando se encuentren después de un byte con valor `0x00` (el cual marca el fin de un segmento del nombre en exFAT). Si se encuentran dos bytes `0x00`, significa que el nombre ya ha sido completamente procesado.

#### `printNameDirect(const char *entry)`
Esta función es responsable de leer y almacenar el nombre de un archivo o directorio directamente desde una entrada de directorio en exFAT. Lee hasta 32 bytes, procesando los caracteres del nombre hasta que se encuentre con dos bytes `0x00`. En cuanto el nombre se obtiene, lo guarda en la variable global `name`.

### 3. **Lectura del Directorio Raíz**

```c
void readRootDir(const char *image_file){
    int fd, n1, n2;
    exFatBootSector boot;
    char entry[SIZE];
    
    // Abrir la imagen del disco
    if((fd = open(image_file, O_RDONLY)) < 0){
        perror("No se pudo abrir la imagen del disco\n");
        exit(1);
    }

    // Leer el sector de arranque
    if(read(fd, &boot, sizeof(boot)) < 0){
        perror("No se pudo leer el sector de arranque del disco\n");
        exit(1);
    }
    
    // Mostrar información del sector de arranque
    printf("La data inicia en el sector: %d\n", boot.ClusterHeapOffset);
    n1 = boot.BytePerSector;
    printf("El tamaño de un sector en bytes es de: %d\n", (int)pow(2.0, n1));
    n2 = boot.SectorPerCluster;
    printf("El tamaño de sectores por cluster es de: %d\n", (int)pow(2.0, n2));
    printf("El directorio raiz se encuentra en el cluster: %d\n", boot.RootDirFirstCluster);
    printf("Archivos y/o directorios contenidos en el directorio raiz\n");
    
    // Cálculos para determinar la ubicación del directorio raíz
    int bytes_per_sector = 1 << boot.BytePerSector;
    int sectors_per_cluster = 1 << boot.SectorPerCluster;
    long rootDirOffset = (boot.ClusterHeapOffset * bytes_per_sector) + ((boot.RootDirFirstCluster - 2) * bytes_per_sector * sectors_per_cluster);

    // Mover el puntero al directorio raíz
    if(lseek(fd, rootDirOffset, SEEK_SET) < 0){
        perror("Error al mover el puntero del archivo al inicio del rootDir\n");
        close(fd);
        exit(1);
    }

    // Leer las entradas del directorio raíz
    int anterC1 = 0;
    while(read(fd, entry, SIZE) == SIZE){
        if((unsigned char)entry[0] == 0x00) break;  // Fin de las entradas de directorio

        // Procesar una entrada de directorio
        if((unsigned char)entry[0] == 0xC1){
            if((unsigned char)entry[0] == 0x83){  // Es una entrada de archivo o directorio
                printNameDirect(entry);
                printf("- %s\n", name);
                memset(name, 0, sizeof(name));
                anterC1 = 0;
            } else if((unsigned char)entry[0] == 0xC1){ 
                if(anterC1 == 1){
                    continuarImpresion(entry);  // Continuar impresión si ya se comenzó
                } else {
                    printNameDirect(entry);  // Iniciar impresión del nombre
                    anterC1 = 1;
                }
                continue;
            }
        } else if(anterC1 == 1){
            printf("- %s\n", name);  // Imprimir nombre completo
            contCpy = 0;
            memset(name, 0, sizeof(name));  // Limpiar nombre
        }
        anterC1 = 0;
    }
    
    close(fd);  // Cerrar el archivo de imagen
}
```

- **Abrir la imagen del disco**: El archivo de imagen (que simula el disco) se abre en modo solo lectura.
- **Leer el sector de arranque**: Se lee el sector de arranque para obtener información sobre la estructura del sistema de archivos (tamaño de sector, tamaño de cluster, etc.).
- **Calcular la ubicación del directorio raíz**: Utilizando la información de la estructura `exFatBootSector`, se calcula el desplazamiento dentro del archivo para acceder al directorio raíz.
- **Leer las entradas del directorio raíz**: El directorio raíz se lee entrada por entrada (32 bytes a la vez). Si el primer byte es `0x00`, significa que se ha llegado al final de las entradas del directorio. Las entradas se procesan y se muestran si son directorios o archivos.

### 4. **Función `main`**

```c
void main(int argc, char *argv[]){
    char *image_file = argv[1];
    readRootDir(image_file);
    exit(1);
}
```

En la función `main`, se recibe como argumento el nombre del archivo de imagen (un archivo binario que contiene el sistema de archivos exFAT). Luego se llama a `readRootDir` para leer y mostrar el contenido del directorio raíz de la imagen del disco.

### Conclusión

Este código está diseñado para leer el directorio raíz de una imagen de disco exFAT y mostrar los nombres de los archivos y directorios que contiene. El proceso implica:
1. Leer el sector de arranque para obtener información de la estructura del disco.
2. Calcular la ubicación del directorio raíz en el disco.
3. Leer las entradas de directorio, procesar los nombres y mostrarlos en pantalla.

Este tipo de programas es útil para explorar o manipular sistemas de archivos en discos o imágenes de disco.
*/