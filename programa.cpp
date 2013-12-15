#include "programa.h"

Programa::Programa(char* entradaName, char* saidaName)
{
	//abre a entrada
	entrada.open(entradaName);

	if(!entrada.is_open()){
		cout << "arquivo de entrada inexistente" << endl;
		return 1;
	}

	if(entrada.eofbit){
		cout << "arquivo de entrada vazio" << endl;
		return 1;
	}

	//pega o binario
	binInProgram = (int*) calloc (sizeof(unsigned short int));
	entrada >> binInProgram;
	for(int i = 0;!entrada.eofbit;i++)
	{
		binInProgram = (int*) realloc (binInProgram, (i+1)*sizeof(unsigned short int));
		entrada >> binInProgram[i];
	}
	

	//abre as saidas
	string nome, nomeasm;
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
}