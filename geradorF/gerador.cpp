#include<stdio.h>
#include<stdlib.h>



#include <iostream>
#include <string.h>
#include <fstream>
#include <sstream>
#include <climits>
#include <cstdlib>

using namespace std;
int main(int argc, char const *argv[])
{
	unsigned short int i;
	ofstream saidaAsm;
	saidaAsm.open("sb.bin");
	cin >> i;

	while(i != 200)
	{
		saidaAsm.write((const char*)&i, 2);
		cin >> i;
	}
	saidaAsm.close();
	return 0;
}

