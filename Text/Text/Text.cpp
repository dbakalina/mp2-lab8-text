#include "Text.h"
#include <string>
#include <iostream>
#include <fstream>

using namespace std;

TMem TTextLink::mem;

int main()
{
	setlocale(LC_CTYPE, "Russian");
    
	TTextLink::InitMem(1000);
	TText t;
	char NameofFile[80], s[80];
	cout << "Введите название файла для чтения" << endl;
	cin >> NameofFile;
	t.Read(NameofFile);
	t.Print();
}