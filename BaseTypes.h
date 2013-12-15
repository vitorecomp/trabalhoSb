#ifndef BASETYPES_H
#define BASETYPES_H

#include <string.h>
class Variavel
{
public:
	unsigned short int address;
	int times;
	int realaddress;
	string varName;

	Variavel(unsigned short int, int, string);
	void traduzir();

};

class Instrucao
{

};


class Add : Instrucao
{

};
#endif