// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tbitfield.cpp - Copyright (c) Гергель В.П. 07.05.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Битовое поле

#include "tbitfield.h"

TBitField::TBitField(int len)
{
	if (len > 0)
	{
		BitLen = len;
		MemLen = (len + 31) >> 5;
		pMem = new TELEM[MemLen];
		if (pMem != NULL)
			for (int i = 0; i < MemLen; i++)
				pMem[i] = 0;
	}
	else
		throw(len);
}

TBitField::TBitField(const TBitField &bf) // конструктор копирования
{
	BitLen = bf.BitLen;
	MemLen = bf.MemLen;
	pMem = new TELEM[MemLen];
	if (pMem != NULL)
		for (int i = 0; i < MemLen; i++)
			pMem[i] = bf.pMem[i];
}

TBitField::~TBitField()
{
	delete[] pMem;
	pMem = NULL;
}

int TBitField::GetMemIndex(const int n) const // индекс Мем для бита n
{
	return n >> 5;
}

TELEM TBitField::GetMemMask(const int n) const // битовая маска для бита n
{
	return 1 << (n & 31);
}

// доступ к битам битового поля

int TBitField::GetLength(void) const // получить длину (к-во битов)
{
  return BitLen;
}

void TBitField::SetBit(const int n) // установить бит
{
	if ((n > -1) && (n < BitLen))
		pMem[GetMemIndex(n)] |= GetMemMask(n);
	else
		throw(n);
}

void TBitField::ClrBit(const int n) // очистить бит
{
	if ((n > -1) && (n < BitLen))
		pMem[GetMemIndex(n)] &= ~GetMemMask(n);
	else
		throw(n);
}

int TBitField::GetBit(const int n) const // получить значение бита
{
	if ((n > -1) && (n < BitLen))
		return pMem[GetMemIndex(n)] & GetMemMask(n);
	else
		throw(n);
}

// битовые операции

TBitField& TBitField::operator=(const TBitField &bf) // присваивание
{
	if (bf != *this)
	{
		BitLen = bf.BitLen;
		if (MemLen != bf.MemLen)
		{
			MemLen = bf.MemLen;
			if (pMem != NULL)
				delete[] pMem;
			pMem = new TELEM[MemLen];
		}
		if (pMem != NULL)
			for (int i = 0; i < MemLen; i++)
				pMem[i] = bf.pMem[i];
	}
	return *this;
}

int TBitField::operator==(const TBitField &bf) const // сравнение
{

	if (BitLen != bf.BitLen)
		return 0;
	else
		for (int i = 0; i < MemLen; i++)
			if (pMem[i] != bf.pMem[i])
				return 0;
  return 1;
}

int TBitField::operator!=(const TBitField &bf) const // сравнение
{
	return !(bf==*this);
}

TBitField TBitField::operator|(const TBitField &bf) // операция "или"
{
	int i;
	int len = BitLen;
	if (bf.BitLen > len)
		len = bf.BitLen;
	TBitField tmp(len);
	for (i = 0; i < MemLen; i++)
		tmp.pMem[i] = pMem[i];
	for (i = 0; i < bf.MemLen; i++)
		tmp.pMem[i] |= bf.pMem[i];
	return tmp;
}

TBitField TBitField::operator&(const TBitField &bf) // операция "и"
{
	int i;
	int len = BitLen;
	if (bf.BitLen > len)
		len = bf.BitLen;
		TBitField tmp(len);
	for (i = 0; i < MemLen; i++)
		tmp.pMem[i] = pMem[i];
	for (i = 0; i < bf.MemLen; i++)
		tmp.pMem[i] &= bf.pMem[i];
	return tmp;
}

TBitField TBitField::operator~(void) // отрицание
{
	int i=0;
	int len = BitLen;
	TBitField tmp(len);
	for ( i ; i < BitLen; i++)
		if (GetBit(i) == 0)
			tmp.SetBit(i);
		else
			tmp.ClrBit(i);
	return tmp;
}

// ввод/вывод

istream &operator>>(istream &istr, TBitField &bf) // ввод 
{
	int i=0;
	char ch;
	do
		istr >> ch;
	while (ch != ' ');
	while (true)
	{
		if (i == bf.BitLen)
		{
			cout << "Введёное битовое поле больше поля, в которое ведётся запись.";
			break;
		}
		if (ch == '0')
		{
			bf.ClrBit(i);
			i++;
		}
		else if (ch == '1')
		{
			bf.SetBit(i);
			i++;
		}
		else break;
		istr >> ch;
	}
	return istr;
}

ostream &operator<<(ostream &ostr, const TBitField &bf) // вывод 
{
	int i = 0;
	int len = bf.BitLen;
	for (i; i < len; i++)
		if (bf.GetBit(i))
			ostr << '1';
		else 
			ostr << '0';
	return ostr;
}
