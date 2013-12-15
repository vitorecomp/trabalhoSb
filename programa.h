#ifndef PROGRAMA_H
#define PROGRAMA_H

#include <iostream>
#include <string.h>
#include <fstream>

using namespace std;

class Programa
{
	unsigned short int *binReadProgram;
	srtring asmOut;
	unsigned int *elf;

	ofstream entrada;
	ofstream saidaAsm;
	ofstream saidaElf;
public:

	//abre a entra e saida, e gera o arquivo de inteiros
	Programa(char*, char*);

	void run();
	void saveAsm();
	void saveElf();
};


#endif