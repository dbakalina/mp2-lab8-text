#pragma once
#include <string>
#include <iostream>
#include <fstream>

class TTextLink
{
	TTextLink* pNext, * pDown;
	char str[80];
	int level;
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
};
	
class TText
{
	TTextLink* pFirst, * pCurr;
	TStack <TTextLink> st;
public:
	void GoFirst();
	void ToDown();
	void ToPrev();
	void ToFirst();
	void InsNextLine(char* s);
	void InsNextSection(char* s);
	void InsDownLine(char* s);
	void InsDownSection(char* s);
	void DelNextLine();
	void PrintRec();
	void Print();
	void SaveRec(TTextLink *t,ofstream& ofs);
	void Save(char* fn);
	TTextLink* ReadRec(ifstream& ifs);
	void Read(char* fn);
};