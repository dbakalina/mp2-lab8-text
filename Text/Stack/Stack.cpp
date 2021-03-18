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
	cout << "Введите выражение: " << endl;
	cin >> exp;
	calc.SetFormula(exp);
	try
	{
		cout << "Арифметическое выражение: " << calc.GetInfix() << endl;
		calc.ToPostfix();
		cout << "Постфиксная форма: " << calc.GetPostfix() << endl;
		cout << "Ответ: " << calc.CalcPostfix() << endl;
	}
	catch (const char* n) { cout << n << endl; }

	return 0;
}