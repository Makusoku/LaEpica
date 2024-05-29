; Declaracion de dato sin valor
section .bss
    buff    resb    100000000
    arr     resq    1000
section .text
    global _start

_start: 

    ; Lectura del buffer (cadena de caracteres)
    xor     rax,    rax
    xor     rdi,    rdi
    mov     rsi,    buff        ; Se guarda en rsi 
    mov     rdx,    100000000
    syscall

    ; Leer el dato, el numero esta en rcx, si hay mas numeros, solo llama a atoi cuantas veces numeros halla y se guardaran en rdx
    mov     rsi,    buff        
    call    atoi                    ; El numero se guarda en rdx
    mov     rcx,    rdx             


    ; AQUI ESCRIBE TU CODIGO

    ; Lee arreglo

    push    rdx
    mov     r15,    rdx
    mov     rcx,    arr
    mov     r10,     8

    loop:
        dec     r15
        call    atoi
        mov     [rcx],    rdx
        add     rcx,    r10    
        cmp     r15,    0
        jne     loop
        sub     rcx,    r10
    pop     rdx
    
    ; RCX -> Ultimo elemento (posicion de memoria)
    call bubble_sort    

    ; Imprime arreglo ordenado

    mov     r15,    rdx
    mov     r14,    arr
    
    loop_4:
        dec     r15
        mov     rcx,    [r14]
        call    _print
        add     r14,    r10
        cmp     r15,    0
        jne     loop_4


_end:     
    ; Fin del programa
    mov     rax,    60
    xor     rdi,    rdi
    syscall

_print: 
    push    rcx
    push    rsi
    ; Transformar rcx en cadena
    mov     rdi,    buff + 99999999       ; Vamos a sobreescribir buff, empezando del final
    mov     rsi,    rdi             ; rsi esta en el final de la cadena
    std                             ; Esto afecta a stosb, ahora disminuye rdi
    mov     rax,    10              ; Final de linea ('\n', cambialo segun te convenga)
    stosb                           ; Esto carga el byte de rax a la memoria que apunta rdi
    mov     rax,    rcx             ; Ahora pasamos el numero a rax
    call    itoa

    ; La cadena empieza en rdi, y termina en rsi
    sub     rsi,    rdi             ; Longitud de la cadena
    mov     rdx,    rsi             
    mov     rsi,    rdi             ; Inicio de la cadena
    inc     rdx                     ; Longitud + 1 para imprimir el salto de linea
    mov     rax,    1               
    mov     rdi,    rax
    syscall
    pop     rsi
    pop     rcx 
    ret


; Cadena a numero (Resultado en rdx)
atoi:   
    xor     rax,    rax
    xor     rdx,    rdx
    lodsb                           ; Carga el byte de rsi en al
    cmp     al,     '-'             ; Comprueba si el numero es negativo
    sete    bl                      ; Si es negativo, bl es 1       
    jne     .lpv                    

.lp:    
    lodsb                           ; Cargas el byte posterior a '-'

.lpv:   
    sub     al,     '0'             ; Le restas '0'
    jl      .end                    ; Si es menor, entonces termino la cadena (' ', '\n' son menores que '0')
    imul    rdx,    10              ; Multiplicas el valor actual rdx por 10
    add     rdx,    rax             ; Le agregas el nuevo valor
    jmp     .lp                     ; Repites el bucle

.end:  
    test    bl,     bl              ; Realiza una operacion AND consigo misma, si es cero la bandera ZF (Zero Flag) se eleva
    jz      .p                          
    neg     rdx                     ; Caso contrario, negamos el valor (negativo)

.p:      
    ret                             


; Pasar numero a cadena (el numero esta en rax, inicio de la cadena en rdi, final en rsi)
itoa:   
    push    r9
    std                             ; rdi retrocede (tiene efecto en todo el programa)
    mov     r9,     10               
    bt      rax,    63              ; Comprueba si el bit mas siginicativo es 1
    setc    bl                      ; Si es 1, entonces bl sera 1 (Significa que el numero es negativo)
    jnc     .lp                     ; Si es 1, entonce el CF (Carry flag) se eleva  
    neg     rax                     ; Si es negativo lo volvemos positivo

.lp:    
    xor     rdx,    rdx             
    div     r9                      ; Divimos el numero / 10
    xchg    rax,    rdx             ; Cociente en RAX, residuo en RDX (Intercambiamos valores)
    add     rax,    '0'             ; Agregamos '0' para pasarlo a ascii
    stosb                           ; Cargamos el byte RAX a RDI
    xchg    rax,    rdx             ; Intercambiamo
    test    rax,    rax             ; Comprobamos que el numero (Cociente), no sea cero
    jnz     .lp                     ; Si no es cero, seguimos 
    test    bl,     bl              ; Si el numero era negativo
    jz      .p                      
    mov     al,     '-'                 
    stosb                           ; Le agregamos '-'

.p:     
    cld                             ; Cancelamos std
    inc     rdi                     ; Aumentamos en 1 para que rdi apunte al inicio de la cadena
    pop     r9
    ret


; Sabemos que el numero siempre es positivo (cadena inicia en rsi, n_cifras esta en rdx)
n_cifras_cadena:
    xor     rax,    rax
    xor     rdx,    rdx
    lodsb                           ; Carga el byte de rsi en al
    jmp     .lpv

.lp:    
    lodsb                           ; Cargas el byte posterior a '-'

.lpv:   
    sub     al,     '0'             ; Le restas '0'
    jl      .end                    ; Si es menor, entonces termino la cadena (' ', '\n' son menores que '0')
    inc     rdx
    jmp     .lp                     ; Repites el bucle

.end: 
    ret

; El bubble sort de un arreglo (RCX -> Posicion de memoria del ultimo elemento, arr -> Inicio del arreglo)
bubble_sort:
    push    rcx
    push    r15
    push    r14
    push    r11
    push    r8
    loop_2:
        cmp     rcx,    arr
        je      end_loop_2            
        mov     r15,    arr

        loop_3:
            cmp     r15,    rcx
            je      end_loop_3   
            mov     r14,    r15  
            add     r15,    r10  
            mov     r11,    [r15]
            mov     r8,     [r14]
            cmp     r11,    r8 
            jge      loop_3
            mov     [r14],  r11
            mov     [r15],  r8
            jmp     loop_3
        
        end_loop_3:
            sub     rcx,    r10    
            jmp     loop_2

    end_loop_2:
        pop     r8
        pop     r11
        pop     r14
        pop     r15 
        pop     rcx
        ret

