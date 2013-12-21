#ifndef ENTIDADES_H
#define ENTIDADES_H

#include "baseTypes.h"

#include <list>
#include <string>
#include <iostream>
#include <climits>

using namespace std;

class ListaDeVariaveis
{
private:
/*	static const string name = "variavel";
	static const string reg1 = "eax";
	static const string reg2 = "ebx";
	static const string reg3 = "ecx";
	static const string reg4 = "edx";
	static const string reg5 = "variavel"; // os dois da pilha
	static const string reg5 = "variavel"; // os dois da pilha*/

	int asmmemopos;
	list<Variavel> variaveis;
	void add(unsigned short int nova);
	void setvalue(unsigned short int nova, unsigned short int value);
public:
	ListaDeVariaveis(unsigned short int*, int);
	list<Variavel> optmizeList();
	list<Variavel> getList();
	string getAsmOf(unsigned short int);
	string getInit();

};

inline ListaDeVariaveis::ListaDeVariaveis(unsigned short int* memo, int size)
{
	asmmemopos = 0;
	for(int i = 0; i <= USHRT_MAX; i++)
	{
		switch(memo[i])
		{
			case 1:
				this->add(memo[i+1]);
				if(memo[i+1] <= size) 
					this->setvalue(memo[i+1], memo[memo[i+1] ]);
				i++;
				break;
			case 2:
				this->add(memo[i+1]);					
				if(memo[i+1] <= size) 
					this->setvalue(memo[i+1], memo[memo[i+1] ]);
				i++;
				break;
			case 3:
				this->add(memo[i+1]);					
				if(memo[i+1] <= size) 
					this->setvalue(memo[i+1], memo[memo[i+1] ]);
				i++;
				break;
			case 4:
				this->add(memo[i+1]);
				if(memo[i+1] <= size) 
					this->setvalue(memo[i+1], memo[memo[i+1] ]);
				i++;
				break;
			case 5:
			case 6:
			case 7:
			case 8:
				i++;
				break;
			case 9:
				this->add(memo[i+1]);					
				if(memo[i+1] <= size) 
					this->setvalue(memo[i+1], memo[memo[i+1] ]);
				this->add(memo[i+2]);
				if(memo[i+2] <= size) 
					this->setvalue(memo[i+2], memo[memo[i+2] ]);
				i+=2;
				break;
			case 10:
				this->add(memo[i+1]);					
				if(memo[i+1] <= size) 
					this->setvalue(memo[i+1], memo[memo[i+1] ]);
				i++;
				break;
			case 11:
				this->add(memo[i+1]);					
				if(memo[i+1] <= size) 
					this->setvalue(memo[i+1], memo[memo[i+1] ]);
				i++;
				break;
			case 12:
				this->add(memo[i+1]);					
				if(memo[i+1] <= size) 
					this->setvalue(memo[i+1], memo[memo[i+1] ]);
				i++;
				break;
			case 13:
				this->add(memo[i+1]);					
				if(memo[i+1] <= size) 
					this->setvalue(memo[i+1], memo[memo[i+1] ]);
				i++;
				break;
			case 14:
				i = USHRT_MAX + 10;
				break;
			default:
				cout << "Intrucao invalida" << endl;
				exit(1);
		}
	}
}

inline void ListaDeVariaveis::add(unsigned short int nepos)
{
	int pos = nepos;
	for(list<Variavel>::iterator it = variaveis.begin(); it != variaveis.end(); ++it)
	{
		if(it->pos == pos)
		{
			it->nvezes++;
			return;
		}
	}
	Variavel var(pos, asmmemopos);
	variaveis.push_front(var);
	asmmemopos += 2;
}

inline void ListaDeVariaveis::setvalue(unsigned short int nepos, unsigned short int value)
{
	int pos = nepos;
	for(list<Variavel>::iterator it = variaveis.begin(); it != variaveis.end(); ++it)
	{
		if(it->pos == pos)
		{
			it->value = value;
			return;
		}
	}
	Variavel var(pos, asmmemopos);
	var.value = value;
	variaveis.push_front(var);
	asmmemopos += 2;
}

inline string ListaDeVariaveis::getAsmOf(unsigned short int nepos)
{
	int pos = nepos;
	for(list<Variavel>::iterator it = variaveis.begin(); it != variaveis.end(); ++it)
	{
		if(it->pos == pos)
		{
			it->nvezes++;
			return it->getAsm();
		}
	}

	Variavel var(pos, asmmemopos);
	variaveis.push_front(var);
	asmmemopos += 2;
	return var.getAsm();
}

inline string ListaDeVariaveis::getInit()
{
	stringstream init;
	for(int i = 0; i < asmmemopos; i +=2)
		for(list<Variavel>::iterator it = variaveis.begin(); it != variaveis.end(); ++it)
		{
			if(it->asmmemopos == i)
				init <<  it->getHexValue() << ", ";
		}	
	init << "0x0";
	return init.str();
}


#endif