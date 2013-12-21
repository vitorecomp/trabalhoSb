#include "programa.h"

Programa::Programa(char* entradaName)
{
	string nome, nomeasm;

	//abre a entrada
	entrada.open(entradaName);


	if(!entrada.is_open()){
		cout << "arquivo de entrada inexistente" << endl;
		exit(1);
	}

	if(entrada.eof()){
		cout << "arquivo de entrada vazio" << endl;
		exit(1);
	}

	binReadProgram = new unsigned short int[USHRT_MAX];

	entrada.seekg (0, entrada.end);
    int length = entrada.tellg();
    entrada.seekg (0, entrada.beg);
    entrada.read((char*)binReadProgram,length);
    entrada.close();

    binSize = length/2;
    for(int i = 0; i < length/2; i++)
    	cout << binReadProgram[i] << "\t";
    cout << endl;
  
    
	//abre as saidas
	nome.append(entradaName);
	unsigned found = nome.find_last_of(".");
	nome = nome.substr(found+1);
	nomeasm = nome + ".asm";
	//.asm
	saidaAsm.open(nomeasm.c_str());
	//.efl
	saidaElf.open(nomeasm.c_str());

}

void Programa::run()
{
	//gera a tabela de variaveis
	ListaDeVariaveis variaveis(binReadProgram, binSize);

	//gera o asm
	generateAsm(variaveis);
	//otimiza a tabela de variavies
 	
	//traduz a tabela de variavies

	//gera a tabela de intruçoes

	//gera a string asm

	//controi os metadados necessarios para o elf

	//gera o binario elf
}

void Programa::saveElf()
{
	//passa o arquivo binario para o arquivo .elf
}

void Programa::saveAsm()
{
	//grava a string asm no arquivo .asm
	this->saidaAsm << asmOut;
	saidaAsm.close();
}


void Programa::generateAsm(ListaDeVariaveis variavies)
{
	//cabecalho
	unsigned short int *memo = this->binReadProgram;
	stringstream saidaAsm;
	saidaAsm << "section .text" << endl;
	saidaAsm << "global _start" << endl;
	saidaAsm << "_start :" << endl;
	//programa
	for(int i = 0; i <= USHRT_MAX; i++)
	{
		switch(memo[i])
		{
			case 1:
				//add ok
				saidaAsm << "inst" << i << ": " << "add AX, " << variavies.getAsmOf(memo[i+1]) << endl;
				i++;
				break;
			case 2:
				//sub ok
				saidaAsm << "inst" << i << ": " << "sub AX, " << variavies.getAsmOf(memo[i+1]) << endl;
				i++;
				break;
			case 3:
				//imul ok
				saidaAsm << "inst" << i << ": " << "mov BX, " << variavies.getAsmOf(memo[i+1]) << endl;
				saidaAsm << "imul" << " bx" << endl;
				i++;
				break;
			case 4:
				//idiv ok
				saidaAsm << "inst" << i << ": " << "cwd"<< endl;
				saidaAsm << "mov BX, " << variavies.getAsmOf(memo[i+1]) << endl;
				saidaAsm << "idiv bx" << endl;
				i++;
				break;
			case 5:
				//jmp ok
				saidaAsm << "inst" << i << ": " << "jmp inst" << memo[i+1] << endl;
				i++;
				break;
			case 6:
				//jmon negativo //ok
				saidaAsm << "inst" << i << ": " << "cmp AX, 0" << endl;
				saidaAsm << "jl " << memo[i+1] << endl;
				i++;
				break;
			case 7:
				//jmpp positivo //ok
				saidaAsm << "inst" << i << ": " << "cmp AX, 0"  << endl;
				saidaAsm << "jg inst" << memo[i+1] << endl;
				i++;
				break;
			case 8:
				//jmpz //ok
				saidaAsm << "inst" << i << ": " << "cmp AX, 0"  << endl;
				saidaAsm << "jz inst" << memo[i+1] << endl;
				i++;
				break;
			case 9:
				//copy ok
				saidaAsm << "inst" << i << ": " << "mov bx ," << variavies.getAsmOf(memo[i+1]) << endl ;
				saidaAsm<< "mov " << variavies.getAsmOf(memo[i+2]) <<" , bx" << endl;
				i+=2;
				break;
			case 10:
				//load ok
				saidaAsm << "inst" << i << ": " << "mov AX, " << variavies.getAsmOf(memo[i+1]) << endl;
				i++;
				break;
			case 11:
				//store ok
				saidaAsm << "inst" << i << ": " << "mov " << variavies.getAsmOf(memo[i+1]) << ", AX" << endl;
				i++;
				break;
			case 12:
				//INPUT
				saidaAsm << "inst" << i << ": " << "call input" << endl;
				saidaAsm << "mov " << variavies.getAsmOf(memo[i+1]) << " , BX" << endl;
				i++;
				break;
			case 13:
				//OUTPUT
				saidaAsm << "inst" << i << ": " << "mov BX, " << variavies.getAsmOf(memo[i+1]) << endl;
				saidaAsm << "call output" << endl;
				i++;
				break;
			case 14:
				//STOP

				saidaAsm << "inst" << i << ": mov eax,1" << endl;
 				saidaAsm << "mov ebx,0" << endl;
 				saidaAsm << "int 80h" << endl;
				i = USHRT_MAX + 10;
				break;

			default:
				saidaAsm << "Intrucao invalida" << endl;
				exit(1);
		}
	}

	//funçoes
	saidaAsm << endl;
	saidaAsm << endl;
	saidaAsm << endl;

	saidaAsm << "input :" << endl;
	saidaAsm << "	push eax" << endl;
	saidaAsm << "	mov eax,3" << endl;
	saidaAsm << "	mov ebx,1" << endl;
	saidaAsm << "	mov ecx,temp" << endl;
	saidaAsm << "	mov edx,30" << endl;
	saidaAsm << "	int 80h" << endl;
	saidaAsm << "" << endl;
	saidaAsm << "	mov ebx, 0" << endl;
	saidaAsm << "	mov ecx, 0" << endl;
	saidaAsm << "pulo:" << endl;
	saidaAsm << "	" << endl;
	saidaAsm << "	mov al, [temp + ebx]" << endl;
	saidaAsm << "	cmp al, 10" << endl;
	saidaAsm << "	je fim" << endl;
	saidaAsm << "	" << endl;
	saidaAsm << "	cmp al, 45" << endl;
	saidaAsm << "	jne cont" << endl;
	saidaAsm << "	inc ebx" << endl;
	saidaAsm << "	jmp pulo" << endl;
	saidaAsm << "cont:" << endl;
	saidaAsm << "	mov eax, 10" << endl;
	saidaAsm << "	mul ecx" << endl;
	saidaAsm << "	mov ecx, eax" << endl;
	saidaAsm << "" << endl;
	saidaAsm << "	mov dl, [temp + ebx]" << endl;
	saidaAsm << "	sub dx, 48" << endl;
	saidaAsm << "	" << endl;
	saidaAsm << "	add ecx, edx" << endl;
	saidaAsm << "	inc ebx" << endl;
	saidaAsm << "	jmp pulo" << endl;
	saidaAsm << "fim:" << endl;
	saidaAsm << "	mov al, [temp]" << endl;
	saidaAsm << "	cmp al, 45" << endl;
	saidaAsm << "	jne fimfinal" << endl;
	saidaAsm << "	mov eax, 0" << endl;
	saidaAsm << "	sub eax, ecx" << endl;
	saidaAsm << "	mov ecx, eax" << endl;
	saidaAsm << "fimfinal:" << endl;
 	saidaAsm << "	pop eax" << endl;
 	saidaAsm << "	mov ebx, ecx" << endl;
 	saidaAsm << "	ret" << endl;

 	//output
	saidaAsm << "		output:" << endl;
	saidaAsm << "			push eax" << endl;
	saidaAsm << " 			mov cx, 1" << endl;
	saidaAsm << "			mov dx, bx" << endl;
	saidaAsm << "" << endl;
	saidaAsm << "			cmp bx, 0" << endl;
	saidaAsm << "			jge ini1" << endl;
	saidaAsm << "" << endl;
	saidaAsm << "" << endl;
	saidaAsm << "			mov dx, 0" << endl;
	saidaAsm << "			sub dx, bx" << endl;
	saidaAsm << "			mov bx, 1;" << endl;
	saidaAsm << "			push bx" << endl;
	saidaAsm << "			jmp ini" << endl;
	saidaAsm << "		ini1:" << endl;
	saidaAsm << "			mov bx, 0" << endl;
	saidaAsm << "			push bx" << endl;
	saidaAsm << "		ini:" << endl;
	saidaAsm << "" << endl;
	saidaAsm << "			mov ax, dx" << endl;
	saidaAsm << "			mov dx, 0" << endl;
	saidaAsm << "			mov bx, 0xA" << endl;
	saidaAsm << "			div bx" << endl;
	saidaAsm << "			add dx, 48" << endl;
	saidaAsm << "			push dx" << endl;
	saidaAsm << "" << endl;
	saidaAsm << "			mov dx, ax" << endl;
	saidaAsm << "" << endl;
	saidaAsm << "			inc cx" << endl;
	saidaAsm << "			cmp dx, 0" << endl;
	saidaAsm << "			jne ini" << endl;
	saidaAsm << "			" << endl;
	saidaAsm << "" << endl;
	saidaAsm << "			mov ax, 2" << endl;
	saidaAsm << "			mul cx" << endl;
	saidaAsm << "			mov ax , [esp + eax - 2]" << endl;
	saidaAsm << "			mov bx, 0" << endl;
	saidaAsm << "			cmp ax, 0" << endl;
	saidaAsm << "			je contF" << endl;
	saidaAsm << "			mov bx, 45" << endl;
	saidaAsm << "		contF:" << endl;
	saidaAsm << "			push bx" << endl;
	saidaAsm << "			mov dx, cx" << endl;
	saidaAsm << "		print:" << endl;
	saidaAsm << "			pop cx" << endl;
	saidaAsm << "			mov [temp], cx" << endl;
	saidaAsm << "			push dx" << endl;
	saidaAsm << "" << endl;
	saidaAsm << "			mov eax,4" << endl;
	saidaAsm << "			mov ebx,1" << endl;
	saidaAsm << "			mov ecx,temp" << endl;
	saidaAsm << "			mov edx,1" << endl;
	saidaAsm << "			int 80h" << endl;
	saidaAsm << "" << endl;
	saidaAsm << "			pop dx" << endl;
	saidaAsm << "			dec dx" << endl;
	saidaAsm << "			cmp dx, 0" << endl;
	saidaAsm << "			jz fimprin" << endl;
	saidaAsm << "			" << endl;
	saidaAsm << "			jmp print" << endl;
	saidaAsm << "		fimprin:" << endl;
	saidaAsm << "			mov BYTE [temp] , 10" << endl;
	saidaAsm << "			mov eax,4" << endl;
	saidaAsm << "			mov ebx,1" << endl;
	saidaAsm << "			mov ecx, temp" << endl;
	saidaAsm << "			mov edx,1" << endl;
	saidaAsm << "			int 80h" << endl;
	saidaAsm << "			pop ax" << endl;
	saidaAsm << "			pop eax" << endl;
	saidaAsm << "			ret" << endl;


 	//section de dadta
 	saidaAsm << endl;
	saidaAsm << endl;
	saidaAsm << endl;

	saidaAsm << "section .data" << endl;
	saidaAsm << "VAR1: dw  " << variavies.getInit() << endl;
	saidaAsm << "section .bss" << endl;
	saidaAsm << "temp resb 64" << endl;


	asmOut = saidaAsm.str();
	//seçao de data
}