section     .data   
    son_iguales     db      "Son capicuas", 10
    son_len     equ     $ - son_iguales
    no_son_iguales     db      "No son capicuas", 10
    no_son_len     equ     $ - no_son_iguales    
    
; Declaracion de dato sin valor
section .bss
    buff    resb    100        

section .text
    global _start

_start: 

    ; Lectura del buffer (cadena de caracteres)
    xor     rax,    rax
    xor     rdi,    rdi
    mov     rsi,    buff        ; Se guarda en rsi 
    mov     rdx,    100
    syscall

    ; Leer el dato, el numero esta en rcx, si hay mas numeros, solo llama a atoi cuantas veces numeros halla y se guardaran en rdx
    mov     rsi,    buff        
    call    atoi                    ; El numero se guarda en rdx
    mov     rcx,    rdx             


    ; AQUI ESCRIBE TU CODIGO
    
    ; Primera forma, crear un numero nuevo invertido (r12) e igualarlo (r12 == r11)
    xor     r12,    r12
    mov     r11,    rcx
    mov     r9,     10
    mov     rax,    r11
    loop :
        xor     rdx,    rdx
        imul    r12,    10
        div     r9 
        add     r12,    rdx
        cmp     rax,    0
        jne     loop

    mov     rax,    1
    mov     rdi,    1

    cmp     r11,    r12
    jne     no_igual

    igual:
        mov     rsi,    son_iguales
        mov     rdx,    son_len
        syscall
        jmp fin

    no_igual:
        mov     rsi,    no_son_iguales
        mov     rdx,    no_son_len
        syscall
        jmp fin

_print: 
    mov     r15,    rcx
    ; Transformar rcx en cadena
    mov     rdi,    buff + 99       ; Vamos a sobreescribir buff, empezando del final
    mov     rsi,    rdi             ; rsi esta en el final de la cadena
    std                             ; Esto afecta a stosb, ahora disminuye rdi
    mov     rax,    10              ; Final de linea
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
    mov     rcx,    r15 



fin:     
    ; Fin del programa
    mov     rax,    60
    xor     rdi,    rdi
    syscall

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
    ret