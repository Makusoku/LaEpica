section .text
        global _start
; 12 0 21
atoi:   xor rax,rax
        xor rdx,rdx
        lodsb
        cmp al,'-'
        sete bl
        jne .lpv
.lp:    lodsb
.lpv:   sub al,'0'
        jl .end
        imul rdx,10
        add rdx,rax
        jmp .lp
.end:   test bl,bl
        jz .p
        neg rdx
.p      ret



itoa:   
        std             ; No es necesario, pero lo pones para recordarnos que esto esta activo
        mov r9,10
        bt rax,63
        setc bl
        jnc .lp
        neg rax
.lp:    
        xor rdx,rdx
        div r9
        xchg rax,rdx
        add rax,'0'
        stosb
        xchg rax,rdx
        test rax,rax
        jnz .lp
        test bl,bl
        jz .p
        mov al,'-'
        stosb
.p:     
        cld
        inc rdi
        ret


116
_start: 
    ; Lectura
        xor rax,rax
        xor rdi,rdi
        mov rsi,buff
        mov rdx,100
        syscall

        ; 45646 121
_pato:
        mov rsi,buff

        call atoi

        ; El numero esta en RDX
        mov rcx,rdx

        call atoi

        ; Ya esta la suma RCX
        add rcx,rdx


        mov     rdi,    buff + 99       ; Esto sobreescribe el codigo actual, pero no hay problema xq no lo necesitamos mas
        mov     rsi,    rdi
        std
        mov     rax,    10
        stosb

        ; La respuesta esta en RAX
        mov rax,rcx
        call itoa

        ; Longitud de la cadena
        sub rsi,rdi     ; RDI -> inicio de la cadena
                        ; RSI -> final de la cadena

        mov rdx,rsi     ; Copias la longitud
        mov rsi,rdi     ; Copias el inicio de la cadena
        mov rax,1       
        mov rdi,rax
        syscall
        
        
        ;   Fin
        mov rax,60
        xor rdi,rdi
        syscall


        section .bss
buff:   resb 100