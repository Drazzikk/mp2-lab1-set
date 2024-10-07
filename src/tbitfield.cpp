// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tbitfield.cpp - Copyright (c) Гергель В.П. 07.05.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// 
// Битовое поле

#include "tbitfield.h"
#include "string"
#include <stdexcept>
#include "iostream"
#include "cstring"
#include "algorithm"
using namespace std;



// Fake variables used as placeholders in tests
static const int FAKE_INT = -1;
static TBitField FAKE_BITFIELD(1);

TBitField::TBitField(int len)
{
    if (len < 0)
    {
        throw underflow_error("The number of elements is not positive");
    }
         
    BitLen = len;
    MemLen = (len / (sizeof(TELEM) * 8)) + 1 ;
    pMem = new TELEM[MemLen];
    if (pMem == nullptr)
    {
        throw domain_error("pMem == nullptr");
    }

    memset(pMem, 0, MemLen * sizeof(TELEM));

    
}

TBitField::TBitField(const TBitField &bf) // конструктор копирования
{
    BitLen = bf.BitLen;
    MemLen = bf.MemLen;
    pMem = new TELEM[MemLen];

    if (pMem == nullptr)
    {
        throw domain_error("domain_error");
    }

    memcpy(pMem, bf.pMem, MemLen * sizeof(TELEM));

}

TBitField::~TBitField()
{
    delete[] pMem;
    pMem = nullptr;
}

int TBitField::GetMemIndex(const int n) const // индекс Мем для бита n
{
    if (n < 0 || n >= BitLen)
    {
        throw out_of_range("Index out of range");
    }

    return n / (sizeof(TELEM) * 8);
}

TELEM TBitField::GetMemMask(const int n) const // битовая маска для бита n
{
    if (n < 0 || n >= BitLen)
    {
        throw out_of_range("Index out of range");
    }

    return static_cast<TELEM>(1) << (n % (sizeof(TELEM) * 8));
}

// доступ к битам битового поля

int TBitField::GetLength(void) const // получить длину (к-во битов)
{
  return BitLen;
}

void TBitField::SetBit(const int n) // установить бит
{
    if (n < 0 || n >= BitLen)
    {
        throw out_of_range("Index out of range");
    }
    
    pMem[GetMemIndex(n)] |= GetMemMask(n);
    
}

void TBitField::ClrBit(const int n) // очистить бит
{
    if (n < 0 || n >= BitLen)
    {
        throw out_of_range("Index out of range");
    }
    else
    {
        pMem[GetMemIndex(n)] &= ~GetMemMask(n);
    }
}

int TBitField::GetBit(const int n) const // получить значение бита
{
    if (n < 0 || n >= BitLen)
    {
        throw ("Index out of range");
    }
    
    return (pMem[GetMemIndex(n)] & GetMemMask(n)) != 0;
    
}

// битовые операции

TBitField& TBitField::operator=(const TBitField &bf) // присваивание
{
    if (this != &bf)
    {
        if (MemLen != bf.MemLen)
        {
            delete[] pMem;
            pMem = new TELEM[MemLen];
            if (pMem == nullptr)
            {
                throw domain_error("domain_error");
            }
        }

        BitLen = bf.BitLen;
        memcpy(pMem, bf.pMem, MemLen * sizeof(TELEM));
    }
    
    return *this;
}

int TBitField::operator==(const TBitField &bf) const // сравнение
{
  if (this == &bf)
      return true;

  if (BitLen != bf.BitLen)
      return false;

  for (int i = 0; i < MemLen; i++)
      if (pMem[i] != bf.pMem[i])
          return false;

  return true;
}

int TBitField::operator!=(const TBitField &bf) const // сравнение
{
    return !(*this == bf);
}

TBitField TBitField::operator|(const TBitField &bf) // операция "или"
{
    int maxLength = max(BitLen, bf.BitLen);
    TBitField result(maxLength);

    for (int i = 0; i < result.MemLen; i++)
    {
        TELEM a = (i < MemLen) ? pMem[i] : 0;
        TELEM b = (i < bf.MemLen) ? bf.pMem[i] : 0;
        result.pMem[i] = a | b;
    }

    return result;
}

TBitField TBitField::operator&(const TBitField &bf) // операция "и"
{
    TBitField result(max(BitLen, bf.BitLen));
    int minim = min(MemLen, bf.MemLen);
    for (int i = 0; i < minim; i++) 
    {
        result.pMem[i] = pMem[i] & bf.pMem[i];
    }
    
    return result;
};

TBitField TBitField::operator~(void) // отрицание
{
    TBitField result(*this);

    for (int i = 0; i < MemLen - 1; i++)
        result.pMem[i] = ~pMem[i];

    for (int i = ((MemLen - 1) * sizeof(TELEM) * 8); i < GetLength(); i++) {
        if (GetBit(i) == 0) 
            result.SetBit(i);
        else result.ClrBit(i);
    }

    return result;

}

// ввод/вывод

istream &operator>>(istream &istr, TBitField &bf) // ввод
{
    for (int i = 0; i < bf.GetLength(); ++i) {
        char ch;
        istr >> ch;

        if (ch == '1')
            bf.SetBit(i);
        else if (ch == '0')
            bf.ClrBit(i);
    }

    return istr;
}

ostream &operator<<(ostream &ostr, const TBitField &bf) // вывод
{
    for (int i = 0; i < bf.GetLength(); ++i)
        ostr << bf.GetBit(i);
    return ostr;
}

