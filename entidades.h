#ifndef ENTIDADES_H
#define ENTIDADES_H

#include "baseTypes.h"

#include <list>
#include <string>
#include <iostream>

class ListaDeVariaveis
{
private:
	static const string name = "variavel";
	static const string reg1 = "eax";
	static const string reg2 = "ebx";
	static const string reg3 = "ecx";
	static const string reg4 = "edx";
	static const string reg5 = "variavel"; // os dois da pilha
	static const string reg5 = "variavel"; // os dois da pilha

	list<Variavel> variaveis;

public:
	ListaDeVariaveis(int*, int);
	list<Variavel> optmizeList();
	list<Variavel> getList();

};

#endif