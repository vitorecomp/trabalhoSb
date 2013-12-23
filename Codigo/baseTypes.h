#ifndef TYPEBASE_H
#define TYPEBASE_H

#include <string>
#include <sstream>
#define VARIAVEL "VAR1"

using namespace std;

class Variavel
{
public:
	int pos;
	int nvezes;
	int asmmemopos;
	int value;
	Variavel(int, int);
	string getAsm();
	string getHexValue();
};

inline Variavel::Variavel(int pos, int asmmemopos)
{
	this->pos = pos;
	this->asmmemopos = asmmemopos;
	nvezes = 0;
	value = 0;
}

inline string Variavel::getAsm()
{
	stringstream ss;
	ss << "[ " << VARIAVEL << " + " << asmmemopos << "]";
	string str = ss.str();
	return str;
}

inline string Variavel::getHexValue()
{
	int ent = value;
	int i, cont, resto[10], j = 1;
	char *out;
    i = 0;         

    out = (char*)malloc(7*sizeof(char));               

    while(ent >=15)             
    {                
        resto[i] = ent % 16;                
        ent = ent / 16;                
        i++;                       
    }             
		

    resto[i] = ent % 16;             
    cont = i;

    out[0] = '0';
    out[1] = 'x';

    while(cont >= 0)             
    {   
    	j++;             
        if(resto[cont] == 10) 
            out[j] = 'A';               
        else if(resto[cont] == 11) 
            out[j] = 'B';               
        else if(resto[cont] == 12) 
            out[j] = 'C';              
        else if(resto[cont] == 13) 
            out[j] = 'D';              
        else if(resto[cont] == 14) 
            out[j] = 'E';               
        else if(resto[cont] == 15) 
            out[j] = 'F';                
        else 
            out[j] = resto[cont] + 48;                
        cont--;                        
    }                              
    out[j+1] = '\0';
    string a = out;
    return a;
}


#endif