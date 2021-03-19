#include "Text.h"
#include <string>
#include <iostream>
#include <fstream>

using namespace std;

int main()
{
	setlocale(LC_CTYPE, "Russian");
    
	TText t;
	char NameofFile[80], s[80];
	cout << "Введите название файла для чтения" << endl;
	cin >> NameofFile;
	t.Read(NameofFile);
	t.Print();
}