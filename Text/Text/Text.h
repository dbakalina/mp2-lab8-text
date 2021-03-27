#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <string>
#include <iostream>
#include <fstream>
#include "../Stack/Stack.h"
using namespace std;

const int MAX_SIZE = 80;

struct TMem {
	TTextLink* pFirst, * pLast, * pFree;
};

class TTextLink
{
protected:
	TTextLink *pNext, *pDown;
	char str[80];
	bool flag;
public:
	TTextLink(char* s = NULL , TTextLink* pN = NULL, TTextLink* pD = NULL)
	{
		pNext = pN;
		pDown = pD;
		if (s)
		{
			strcpy(str, s);
		}
		else
			str[0] = '\n';

	}
	~TTextLink(){}

	static TMem mem;
	static void InitMem(int size);
	static void Cleaner(TText &t);
	static void PrintFree();
	
	void* operator new(size_t size);
	void operator delete(void* p);

	friend class TText;
};
	
class TText
{
	TTextLink* pFirst, *pCurr;
	Stack <TTextLink*> st;
	int level;
public:
	TText(TTextLink* pf = NULL)
	{
		if (!pf) pf = new TTextLink;

		pFirst = pf;
		pCurr = pFirst;
	}
	~TText() {};

	void GoFirst();
	void ToDown();
	void ToPrev();
	void ToFirst();
	void ToStart();

	//Вставка
	void InsNextLine(char* s);
	void InsNextSection(char* s);
	void InsDownLine(char* s);
	void InsDownSection(char* s);

	//Удаление
	void DelNextLine();
	void DelDownLine();
	
	//Печать,сохранение,чтение
	void PrintRec(TTextLink* t);
	void Print();
	void SaveRec(TTextLink *t,ofstream& ofs);
	void Save(char* fn);
	TTextLink* ReadRec(ifstream& ifs);
	void Read(char* fn);


	TTextLink* GetCurrent() { return pCurr; };
	int IsEnd();
	void GoNext();
	void Reset();
	void PointerCreate();
	void PointerDelete();
};