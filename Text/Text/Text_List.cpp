#include "Text.h"
#include "../Stack/Stack.h"
#include <iostream>
using namespace std;

TTextLink::TTextLink(const char* s, TTextLink* next, TTextLink* down)
{
	flag = true;
	pNext = next;
	pDown = down;
	if (s != NULL)
	{
		int i = 0;
		do {
			str[i] = s[i];
			i++;
		} while (s[i - 1] != '\0');
	}
	else
	{
		str[0] = '\0';
	}
}

void TTextLink::InitMem(int s)
{
	int size = sizeof(TTextLink) * s;
	mem.pFirst = mem.pFree = (TTextLink*)malloc(size);
	mem.pLast = mem.pFirst + (s - 1);
	TTextLink* tmp = mem.pFirst;
	while (tmp != mem.pLast)
	{
		tmp->pNext = tmp + 1;
		tmp->flag = true;
		tmp->str[0] = '\0';
		tmp = tmp->pNext;
	}
	tmp->pNext = NULL;
	tmp->flag = true;
	tmp->str[0] = '\0';
}

void TTextLink::clean(TText& t)
{
	TTextLink* tmp = mem.pFree;
	while (tmp != mem.pLast)
	{
		tmp->flag = false;
		tmp = tmp->pNext;
	}
	tmp->flag = false;
	for (t.Reset(); !t.IsEmpty(); t.GoNext())
	{
		t.GetCurr()->flag = false;
	}
	tmp = mem.pFirst;
	while (tmp != mem.pLast)
	{
		if (tmp->flag)
		{
			TText::operator delete(tmp);
		}
		else
			tmp->flag = true;
		tmp = tmp + 1;
	}
	if (tmp->flag)
	{
		TText::operator delete(tmp);
	}
	else
		tmp->flag = true;
}

void TTextLink::PrintFree()
{
	TTextLink* tmp = mem.pFree;
	while (tmp != mem.pLast)
	{
		if (tmp->str[0] != '\0')
			std::cout << tmp->str << ' ';
		tmp = tmp->pNext;
	}
	if (tmp->str[0] != '\0')
		std::cout << tmp->str << ' ';
}

TText::TText()
{
	pFirst = NULL;
	pCurr = NULL;
}

void TText::GoFirstLink()
{
	while (!st.Empty())
		st.Pop();
	pCurr = pFirst;
}
void TText::GoNextLink()
{
	if (pCurr->pNext)
	{
		st.Push(pCurr);
		pCurr = pCurr->pNext;
	}
}
void TText::GoDownLink()
{
	if (pCurr->pDown)
	{
		st.Push(pCurr);
		pCurr = pCurr->pDown;
	}
}
void TText::GoPrevLink()
{
	if (!st.Empty())
	{
		pCurr = st.Top();
		st.Pop();
	}
}
void TText::InsNextLine(const char* s)
{
	if (pCurr)
	{
		TTextLink* t = (TTextLink*)(TText::operator new(1));
		strcpy_s(t->str, s);
		t->pNext = pCurr->pNext;
		t->pDown = NULL;
		pCurr->pNext = t;
	}
}
void TText::InsNextSections(const char* s)
{
	if (pCurr)
	{
		TTextLink* t = (TTextLink*)(TText::operator new(1));
		strcpy_s(t->str, s);
		t->pNext = NULL;
		t->pDown = pCurr->pNext;
		pCurr->pNext = t;
	}
}
void TText::InsDownLine(const char* s)
{
	if (pCurr)
	{
		TTextLink* t = (TTextLink*)(TText::operator new(1));
		strcpy_s(t->str, s);
		t->pNext = pCurr->pDown;
		t->pDown = NULL;
		pCurr->pDown = t;
	}
}
void TText::InsDownSections(const char* s)
{
	if (pCurr)
	{
		TTextLink* t = (TTextLink*)(TText::operator new(1));
		strcpy_s(t->str, s);
		t->pDown = pCurr->pDown;
		t->pNext = NULL;
		pCurr->pDown = t;
	}
}
void TText::DelNextLine()
{
	if (pCurr && pCurr->pNext)
	{
		TTextLink* t = pCurr->pNext;
		pCurr->pNext = t->pNext;
		TText::operator delete(t);
	}
}
void TText::DelDownLine()
{
	if (pCurr && pCurr->pDown)
	{
		TTextLink* t = pCurr->pDown;
		pCurr->pDown = t->pNext;
		TText::operator delete(t);
	}
}

void TText::Print()
{
	int level = 0;
	TText::PrintRec(pFirst, level);
}
void TText::PrintRec(TTextLink* t, int level)
{
	if (t != NULL)
	{
		for (int i = 0; i < level; i++)
			std::cout << ' ';
		std::cout << t->str << std::endl;
		++level;
		PrintRec(t->pDown, level);
		level--;
		PrintRec(t->pNext, level);
	}
}
void TText::Save(const char* file_name)
{
	std::ofstream ofs(file_name);
	SaveRec(pFirst, ofs);
	ofs.close();
}
void TText::SaveRec(TTextLink* t, std::ofstream& ofs)
{
	if (t != NULL)
	{
		ofs << t->str << '\n';
		if (t->pDown)
		{
			ofs << '{' << '\n';
			SaveRec(t->pDown, ofs);
			ofs << '}' << '\n';
		}
		if (t->pNext)
			SaveRec(t->pNext, ofs);
	}
}
void TText::Read(const char* file_name)
{
	std::ifstream ifs(file_name);
	pFirst = ReadRec(ifs);
	ifs.close();
}
TTextLink* TText::ReadRec(std::ifstream& ifs)
{
	TTextLink* pF, * pC;
	pF = NULL;
	pC = NULL;
	char buff[MAX_SIZE];
	while (!ifs.eof())
	{
		ifs.getline(buff, MAX_SIZE, '\n');
		if (buff[0] == '}')
			break;
		if (buff[0] == '{')
		{
			pC->pDown = ReadRec(ifs);
		}
		else
		{
			if (!pC)
			{
				TTextLink* t = (TTextLink*)(TText::operator new(1));
				strcpy_s(t->str, buff);
				t->pDown = NULL;
				t->pNext = NULL;
				pF = t;
				pC = pF;
			}
			else
			{
				TTextLink* t = (TTextLink*)(TText::operator new(1));
				strcpy_s(t->str, buff);
				t->pDown = NULL;
				t->pNext = NULL;
				pC->pNext = t;
				pC = t;
			}
		}
	}
	return pF;
}
void TText::PrintS()
{
	if (pFirst != NULL)
	{
		Stack<int> level;
		level.Push(0);
		TTextLink* curr = pFirst;
		std::cout << curr->str << std::endl;
		Stack<TTextLink*> s;
		std::set<TTextLink*>replay;
		replay.insert(curr);
		s.Push(curr);
		while (!s.Empty())
		{
			bool flag = true;
			curr = s.Top();
			while (curr->pDown != NULL && replay.count(curr->pDown) == 0)
			{
				level.Push(level.Top() + 1);
				for (int i = 0; i < level.Top(); i++)
					std::cout << ' ';
				std::cout << curr->pDown->str << std::endl;
				curr = curr->pDown;
				s.Push(curr);
				replay.insert(curr);
				flag = false;
			}
			while (curr->pNext != NULL && replay.count(curr->pNext) == 0)
			{
				level.Push(level.Top());
				for (int i = 0; i < level.Top(); i++)
					std::cout << ' ';
				std::cout << curr->pNext->str << std::endl;
				curr = curr->pNext;
				s.Push(curr);
				replay.insert(curr);
				flag = false;
				break;
			}
			if (flag)
			{
				s.Pop();
				level.Pop();
			}
		}
	}
}
void TText::SaveS(const char* name_file)
{
	std::ofstream ofs(name_file);
	if (pFirst != NULL)
	{
		TTextLink* curr = pFirst;
		ofs << curr->str << '\n';
		Stack<TTextLink*>s;
		std::set<TTextLink*>replay;
		Stack<int>level;
		s.Push(curr);
		level.Push(0);
		replay.insert(curr);
		while (!s.Empty())
		{
			bool flag = true;
			curr = s.Top();
			while (curr->pDown != NULL && replay.count(curr->pDown) == 0)
			{
				level.Push(1);
				ofs << '{' << '\n' << curr->pDown->str << '\n';
				curr = curr->pDown;
				s.Push(curr);
				replay.insert(curr);
				flag = false;
			}
			while (curr->pNext != NULL && replay.count(curr->pNext) == 0)
			{
				level.Push(0);
				ofs << curr->pNext->str << '\n';
				curr = curr->pNext;
				s.Push(curr);
				replay.insert(curr);
				flag = false;
				break;
			}
			if (flag)
			{
				s.Pop();
				int a = level.Top();
				level.Pop();
				if (a == 1)
					ofs << '}' << '\n';
			}
		}
		ofs.close();
	}
}
void TText::ReadS(const char* name_file)
{
	std::ifstream ifs(name_file);
	if (!ifs.eof())
	{
		char buff[MAX_SIZE];
		ifs.getline(buff, MAX_SIZE, '\n');
		TTextLink* curr = (TTextLink*)(TText::operator new(1));
		strcpy_s(curr->str, buff);
		curr->pDown = NULL;
		curr->pNext = NULL;
		pFirst = curr;
		pCurr = curr;
		Stack<TTextLink*> prev_down;
		char prev_simb = ' ';
		while (!ifs.eof())
		{
			ifs.getline(buff, MAX_SIZE, '\n');
			if (buff[0] != '{' && buff[0] != '}')
			{
				TTextLink* t = (TTextLink*)(TText::operator new(1));
				strcpy_s(t->str, buff);
				t->pNext = NULL;
				t->pDown = NULL;
				if (prev_simb == '{')
					curr->pDown = t;
				else
					curr->pNext = t;
				curr = t;
				prev_simb = ' ';
			}
			else
			{
				if (buff[0] == '{')
				{
					prev_down.Push(curr);
					prev_simb = '{';
				}
				else
				{
					curr = prev_down.Top();
					prev_down.Pop();
					prev_simb = '}';
				}
			}
		}
		ifs.close();
	}
}
void TText::Reset()
{
	if (pFirst)
	{
		while (!st.Empty())
			st.Pop();
		pCurr = pFirst;
		st.Push(pFirst);
		if (pFirst->pNext)
			st.Push(pFirst->pNext);
		if (pFirst->pDown)
			st.Push(pFirst->pDown);
	}
}
void TText::GoNext()
{
	if (!st.Empty())
	{
		pCurr = st.Top();
		st.Pop();
		if (pCurr != pFirst)
		{
			if (pCurr->pDown)
				st.Push(pCurr->pDown);
			if (pCurr->pNext)
				st.Push(pCurr->pNext);
		}
	}
}
bool TText::IsEmpty()
{
	return st.Empty();
}
void* TText::operator new(std::size_t n)
{
	TTextLink* pC = mem.pFree;
	if (mem.pFree)
		mem.pFree = mem.pFree->pNext;
	return pC;
}
void TText:: operator delete(void* memory)
{
	TTextLink* pC = (TTextLink*)memory;
	pC->pNext = mem.pFree;
	mem.pFree = pC;
}

void TText::PointerCreate()
{
	if (pCurr != NULL)
	{
		char Point[80] = "->";
		strcat(Point, pCurr->str);
		strcpy(pCurr->str, Point);
	}
}

void TText::PointerDelete()
{
	if (pCurr != NULL && strstr(pCurr->str, "->") != NULL)
		strcpy(pCurr->str, pCurr->str + 2);
}