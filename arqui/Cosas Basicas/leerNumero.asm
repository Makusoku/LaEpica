section .data
	messageUno dq "Ingrese la cantidad de menores a quitar: "
	tamUno equ $ - messageUno
	messageDos dq "La media calculada es: "
	tamDos equ $ - messageDos

	;datos del areglo
	tamarr dq 6
	arr dq 5,3,4,8,9,7

section .bss
	n resb 4

section .text
	global _start

_start:

	;mostramos el mensaje 1
	mov rax, 1
	mov rdi, 1
	mov rsi, messageUno
	mov rdx, tamUno
	syscall
    
	;leemos el dato de entrada
	mov rax,0
	mov rdi, 0
	mov rsi, n
	mov rdx, 3
	syscall

	xor r11,r11
	call obtenerNum


	;terminamos el programa
	mov rax,	60
	mov rdi,	0
	syscall



obtenerNum:
	;Lo que queremos es obtener en el registro 11 el numero leido
	;asumiremos que el ultimo dijito es el de salto de linea
	push rax
	mov r13,0
	mov r14,0
	acumula:
    	mov rax,10
    	mov r13b, [r14+n]    
    	cmp r13b, 10
    	je fin
    	add r14,1
    	sub r13,48
    	mul r11
    	mov r11,rax
    	add r11,r13
    	xor r13,r13;limpiamos
    	jmp acumula
	fin:
	pop rax
ret