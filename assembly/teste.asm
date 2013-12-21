%include "io.mac"
section .data
hl: db "Hello World!",0xD,0xA
NHL EQU $-hl
section .bss
temp: resb 30
section .text

global _start
_start:
	mov eax,3
	mov ebx,1
	mov ecx,temp
	mov edx,30
	int 80h

	mov ebx, 0
	mov ecx, 0
pulo:

	mov al, [temp + ebx]
	cmp al, 10
	je fim

	cmp al, 45
	jne cont
	inc ebx
	jmp pulo
cont:
	mov eax, 10
	mul ecx
	mov ecx, eax

	mov dl, [temp + ebx]
	sub dx, 48

	add ecx, edx
	inc ebx
	jmp pulo
fim:
	mov al, [temp]
	cmp al, 45
	jne fimfinal
	mov eax, 0
	sub eax, ecx
	mov ecx, eax
fimfinal:
	mov ebx, ecx
	mov cx, 0
	mov edx, ebx
ini:
	mov ax, dx
	mov bx, 0xA
	div bl
	mov dl, al
	mov al, ah
	mov ah, 0
	add ax, 48
	push ax
	inc cx
	cmp dx, 0
	jne ini
	
	mov dx, cx
print:
	pop cx
	push dx
	mov eax,4
	mov ebx,1
	mov edx,1
	int 80h

	pop dx
	dec dx
	cmp dx, 0
	jz fimprin
	jmp print
fimprin:

	mov eax,1
	mov ebx,0
	int 80h