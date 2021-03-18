#include <iostream>
#include "Stack.h"
#include "Calculator.h"
#include <cstdlib>

using namespace std;

int main()
{
	setlocale(LC_ALL, "RUS");
	string exp;
	TCalculator calc;
	cout << "������� ���������: " << endl;
	cin >> exp;
	calc.SetFormula(exp);
	try
	{
		cout << "�������������� ���������: " << calc.GetInfix() << endl;
		calc.ToPostfix();
		cout << "����������� �����: " << calc.GetPostfix() << endl;
		cout << "�����: " << calc.CalcPostfix() << endl;
	}
	catch (const char* n) { cout << n << endl; }

	return 0;
}