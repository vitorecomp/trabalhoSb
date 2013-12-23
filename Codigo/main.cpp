#include "programa.h"

#include <iostream>

using namespace std;


int main(int argc, char * argv[])
{
	Programa *programa = NULL;

	if(argc < 2){
		cout << "Numero de argumentos invalidos" << endl;
		return 1;
	}
	//passa para o programa
	programa =  new Programa(argv[1]);
	programa->run();
	programa->saveAsm();
	programa->saveElf();
}
