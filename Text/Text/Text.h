#pragma once
#include <string>
#include <iostream>
#include <fstream>
#include "../Stack/Stack.h"
using namespace std;

const int MAX_SIZE = 80;

class TTextLink
{
protected:
	TTextLink *pNext, *pDown;
	char str[80];
public:
	TTextLink(char* s = NULL , TTextLink* pN = NULL, TTextLink* pD = NULL)
	{
		pNext = pN;
		pDown = pD;
		if (s)
			strcpy(str, s);
		else
			str[0] = '\n';

	}
	~TTextLink();
	
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

	//�������
	void InsNextLine(char* s);
	void InsNextSection(char* s);
	void InsDownLine(char* s);
	void InsDownSection(char* s);

	//��������
	void DelNextLine();
	void DelDownLine();
	
	//������,����������,������
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