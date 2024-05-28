section     .data
    num     equ     123

section     .bss
    number      resb    100

section     .text
    global      _start

_start:
    xor     rax,    rax
    xor     rdi,    rdi
    mov     rsi,    number
    mov     rdx,    100
    syscall

    mov     rax,    1
    mov     rdi,    1
    mov     rsi,    number
    mov     rdx,    100
    syscall

    mov     rsi,    number
    call atoi

    mov     rax,    60
    mov     rdi,    0
    syscall


; En RSI esta almacenado la direccion de memoria del inicio de la cadena

atoi:
    xor     rax,    rax                
    xor     rdx,    rdx                
    lodsb                       
    cmp     al,     '-'                  
    sete    bl                      
    jne     .lpv            

.lp:
    lodsb         

.lpv:
    sub     al,     '0'                
    jl      .end                      
    imul    rdx,    10                 
    add     rdx,    rax                 
    jmp     .lp     

.end:
    test    bl,     bl                  
    jz      .p                        
    neg     rdx       
                  
.p:
    ret
