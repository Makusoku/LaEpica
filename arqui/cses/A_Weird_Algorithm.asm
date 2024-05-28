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

    ; Numero en rcx
    mov     rsi,    buff        
    call    atoi                    ; El numero se guarda en rdx
    mov     rcx,    rdx
    jmp     _print
    
    ; AQUI VA LA LOGICA DEL CODIGO

loop:        
    
    bt      rcx,    0
    jnc     es_par                     ; Si es 1, entonce el CF (Carry flag) se eleva  
    imul    rcx,    3    
    inc     rcx
    jmp     _print

es_par:
    xor     rdx,    rdx
    mov     r9,     2
    mov     rax,    rcx
    div     r9
    xchg    rcx,    rax

_print:
    push    rcx             ; El syscall altera el valor de rcx
    ; Transformar rcx en cadena
    mov     rdi,    buff + 99       ; Vamos a sobreescribir buff, empezando del final
    mov     rsi,    rdi             ; rsi esta en el final de la cadena
    std                             ; Esto afecta a stosb, ahora disminuye rdi
    mov     rax,    ' '              ; Final de linea
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

    pop     rcx             ; Recuperamos el valor
    cmp     rcx,    1
    jne     loop

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