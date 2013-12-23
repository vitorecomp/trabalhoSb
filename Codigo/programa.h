#ifndef PROGRAMA_H
#define PROGRAMA_H

#include <iostream>
#include <string.h>
#include <fstream>
#include <sstream>
#include <climits>
#include <cstdlib>
#include "entidades.h"

using namespace std;

class Programa
{
private:
	unsigned short int *binReadProgram;
	int binSize;
	string asmOut;
	unsigned int *elf;

	ifstream entrada;
	ofstream saidaAsm;
	ofstream saidaElf;

	void generateAsm(ListaDeVariaveis variavies);
public:

	//abre a entra e saida, e gera o arquivo de inteiros
	Programa(char*);

	void run();
	void saveAsm();
	void saveElf();
};


#endif