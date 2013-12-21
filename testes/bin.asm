section .text
global _start
_start :
inst0: call input
mov [ VAR1 + 0] , BX
inst2: mov AX, [ VAR1 + 0]
inst4: sub AX, [ VAR1 + 2]
inst6: cmp AX, 0
jz inst18
inst8: mov [ VAR1 + 4], AX
inst10: mov BX, [ VAR1 + 0]
imul bx
inst12: mov [ VAR1 + 0], AX
inst14: mov AX, [ VAR1 + 4]
inst16: jmp inst4
inst18: mov BX, [ VAR1 + 0]
call output
inst20: mov eax,1
mov ebx,0
int 80h



input :
	push eax
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
	pop eax
	mov ebx, ecx
	ret
		output:
			push eax
 			mov cx, 1
			mov dx, bx

			cmp bx, 0
			jge ini1


			mov dx, 0
			sub dx, bx
			mov bx, 1;
			push bx
			jmp ini
		ini1:
			mov bx, 0
			push bx
		ini:

			mov ax, dx
			mov dx, 0
			mov bx, 0xA
			div bx
			add dx, 48
			push dx

			mov dx, ax

			inc cx
			cmp dx, 0
			jne ini
			

			mov ax, 2
			mul cx
			mov ax , [esp + eax - 2]
			mov bx, 0
			cmp ax, 0
			je contF
			mov bx, 45
		contF:
			push bx
			mov dx, cx
		print:
			pop cx
			mov [temp], cx
			push dx

			mov eax,4
			mov ebx,1
			mov ecx,temp
			mov edx,1
			int 80h

			pop dx
			dec dx
			cmp dx, 0
			jz fimprin
			
			jmp print
		fimprin:
			mov BYTE [temp] , 10
			mov eax,4
			mov ebx,1
			mov ecx, temp
			mov edx,1
			int 80h
			pop ax
			pop eax
			ret



section .data
VAR1: dw  0x0, 0x1, 0x0, 0x0
section .bss
temp resb 64
