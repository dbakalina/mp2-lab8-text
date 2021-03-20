#include "Text.h"
#include "../Stack/Stack.h"
#include <iostream>
using namespace std;


void TText :: GoFirst()
{
	if (pCurr->pNext)
	{
		st.Push(pCurr);
		pCurr = pCurr->pNext;
	}
}

void TText::ToDown()
{
	if (pCurr->pDown)
	{
		st.Push(pCurr);
		pCurr = pCurr->pDown;
	}
}

void TText::ToPrev()
{
	if (!st.Empty())
		pCurr = st.Pop();
}

void TText:: ToFirst()
{
	pCurr = pFirst;
	st.Clear();
}

void TText:: InsNextLine(char* s)
{
	if (pCurr != NULL)
	{
		TTextLink* tmp;
		tmp = new TTextLink(s, pCurr->pNext, NULL);
		pCurr->pNext = tmp;
	}
}
void TText::InsNextSection(char* s)
{
	if (pCurr != NULL)
	{
		TTextLink* tmp;
		tmp = new TTextLink(s, NULL, pCurr->pNext);
		pCurr->pNext = tmp;
	}
}

void TText::InsDownLine(char* s)
{
	if (pCurr != NULL)
	{
		TTextLink* tmp;
		tmp = new TTextLink(s, pCurr->pDown, NULL);
		pCurr->pDown = tmp;
	}
}

void TText::InsDownSection(char* s)
{
	if (pCurr != NULL)
	{
		TTextLink* tmp;
		tmp = new TTextLink(s, NULL, pCurr->pDown);
		pCurr->pDown = tmp;
	}
}

void TText::DelNextLine()
{
	if (pCurr->pNext != NULL)
	{
		TTextLink* tmp;
		tmp = pCurr->pNext;
		pCurr->pNext = pCurr->pNext->pNext;
		delete tmp;
	}
}

void TText::DelDownLine()
{
	if (pCurr->pDown != NULL)
	{
		TTextLink* tmp;
		tmp = pCurr->pDown;
		tmp = pCurr->pDown->pNext;
		delete tmp;
	}
}

void TText:: ToStart()
{
	pCurr = pFirst;
}

void TText::PrintRec(TTextLink* t)
{
	if (t != NULL)
	{
		for (int i = 0; i < level; i++)
			cout << " ";
		std::cout << t->str << endl;
			level++;
			PrintRec(t->pDown);
			level--;
			PrintRec(t->pNext);
	}
}

void TText::Print()
{
	level = 0;
	PrintRec(pFirst);
}

void TText::SaveRec(TTextLink* t, ofstream& ofs)
{
	ofs << t->str << endl;
	if (t->pDown != NULL)
	{
		ofs << '{' << endl;
		SaveRec(t->pDown, ofs);
		ofs << '}' << endl;
	}
	if (t->pNext != NULL)
	{
		SaveRec(t->pNext ,ofs);
	}
}
void TText::Save(char* fn)
{
	ofstream ofs(fn);
	SaveRec(pFirst,ofs);
	ofs.close();
}

void TText:: Read(char* fn)
{
	ifstream ifs(fn);
	pFirst = ReadRec(ifs);
	ifs.close();
}

TTextLink* TText:: ReadRec(ifstream& ifs)
{

	TTextLink* pF = NULL, *pC = NULL;
	char Buff[80];

	while (ifs.eof() == 0)
	{
		ifs.getline(Buff, MAX_SIZE , '\n');

		if (Buff[0] == '}')
		{
			break;
		}
		else
			if (Buff[0] == '{')
			{
				pC->pDown = ReadRec(ifs);
			}
			else
			{
				if (pF)
				{
					pC->pNext = new TTextLink(Buff);
					pC = pC->pNext;
				}
				else {
					pF = new TTextLink(Buff);
					pC = pF;
				}

			}
	}
	return pF;
}

int TText::IsEnd()
{
	return st.Empty();
}

void TText::GoNext()
{
	if (!IsEnd())
	{
		pCurr = st.Pop();

		if (pCurr != pFirst)
		{
			if (pCurr->pNext != NULL) st.Push(pCurr->pNext);
			if (pCurr->pDown != NULL) st.Push(pCurr->pDown);
		}
	}
}

void TText::Reset()
{
	st.Clear();
	pCurr = pFirst;
	if (pCurr != NULL)
	{
		st.Push(pCurr);

		if (pCurr->pNext != NULL) st.Push(pCurr->pNext);
		if (pCurr->pDown != NULL) st.Push(pCurr->pDown);
	}
}

void TText::PointerCreate()
{
	if (pCurr != NULL)
	{
		char Point[80] = "->";
		strcat_s(Point, pCurr->str);
		strcpy_s(pCurr->str, Point);
	}
}

void TText::PointerDelete()
{
	if (pCurr != NULL && strstr(pCurr->str, "->") != NULL)
	{
		strcpy(pCurr->str, pCurr->str + 2);
	}
}