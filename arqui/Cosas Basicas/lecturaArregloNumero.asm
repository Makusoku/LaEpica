section .data
    numbers dw 400, 300, 500, 100, 200   ; Array de números
    len equ 5
    mss db "arreglossss", 10
    lenMss equ $ - mss
    divisor equ 7
    respuesta dq 0  

section .text
    global _start

_start:
    
    ; Impresion
    mov rax, 1
    mov rdi, 1
    mov rsi,    mss
    mov rdx,    lenMss
    syscall

    mov r15, numbers
    mov r14, len
    mov bx, 0

for:
    mov ax,   [r15]
    add bx, ax
    add r15, 2
    dec r14
    jnz for

    ;bx tiene 1500

despues:
    mov al, 2
    mul bx    

    ; rax tiene 3000

    mov bx, 3
    div bx      ; Solo registros, no inmediatos

punto_flotante:
    ; dividir 1000 / 3
    mov bx, 3

    cvtsi2ss    xmm0,   rbx     ; Solo Rax, Rbx 64 bits o ? 32 bits ?
    cvtsi2ss    xmm1,   rax     ; xmm1 <- xmm1 / xmm0, para ver es p $xmm1.v4_float

    divss   xmm1,   xmm0


imprimir_numero:
    ; La estrategia aqui sera encontra la cantidad de cifras del maximo valor rax -> 1000 => "1 0 0 0 \n", son 5 cifras
    add rax,    562
    mov [respuesta],    rax
    mov rbx,    respuesta + 4

    xor rcx, rcx
    and [respuesta], rcx    ; Con 0 lo inicializamos

    mov CL, 10
    mov [rbx],  CL          ; Ojo, al final es CL, por que no puedes dividir entre cero

    impresion:
        cmp ax, 0
        je fin
        dec rbx
        div CL      ;   rdx:rax = rdx:rax / cl
        add ah, '0'
        mov [rbx],  ah
        xor ah, ah
        jmp impresion

fin:

    ; Imprime 1562

    mov rax, 1
    mov rdi, 1
    mov rsi,    respuesta
    mov rdx,    5
    syscall

    mov rax,    60
    mov rdi,    0
    syscall