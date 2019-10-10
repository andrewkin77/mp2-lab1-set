// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tbitfield.cpp - Copyright (c) Гергель В.П. 07.05.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Битовое поле

#include "tbitfield.h"

TBitField::TBitField(int len)
{
    BitLen = len;
    MemLen = BitLen / (8 * sizeof(TELEM)) + 1;
    pMem = new TELEM[MemLen];
    for (int i = 0; i < MemLen; i++) {
        pMem[i] = 0;
    }
}

TBitField::TBitField(const TBitField &bf) // конструктор копирования
{
    BitLen = bf.BitLen;
        MemLen = bf.MemLen;
        pMem = new TELEM[MemLen];
        for (int i = 0; i < MemLen; i++) {
            pMem[i] = bf.pMem[i];
        }
}

TBitField::~TBitField()
{
      delete[] pMem;
}

int TBitField::GetMemIndex(const int n) const // индекс Мем для бита n
{
    return n / 32;
}

TELEM TBitField::GetMemMask(const int n) const // битовая маска для бита n
{
    int v;
    v = n % 32;
    TELEM tmp = 1;
    tmp = tmp << v;
    return tmp;
}

// доступ к битам битового поля

int TBitField::GetLength(void) const // получить длину (к-во битов)
{
  return 0;
}

void TBitField::SetBit(const int n) // установить бит
{
    int i = GetMemIndex(n);
    pMem[i] |= GetMemMask(n);
}

void TBitField::ClrBit(const int n) // очистить бит
{
    int i = GetMemIndex(n);
    pMem[i] &= GetMemMask(n);
}

int TBitField::GetBit(const int n) const // получить значение бита
{
    int i = GetMemIndex(n);
    if (pMem[i] & GetMemMask(n) != 0){
        return 1;
    }
    return 0;
}

// битовые операции

TBitField& TBitField::operator=(const TBitField &bf) // присваивание
{
    BitLen = bf.BitLen;
    if (MemLen != bf.MemLen) {
        MemLen = bf.MemLen;
        delete[] pMem;
        pMem = new TELEM[MemLen];
    }
    for (int i = 0; i < MemLen; i++) {
        pMem[i] = bf.pMem[i];
    }
    return *this;
}

int TBitField::operator==(const TBitField &bf) const // сравнение
{
  return 0;
}

int TBitField::operator!=(const TBitField &bf) const // сравнение
{
  return 0;
}

TBitField TBitField::operator|(const TBitField &bf) // операция "или"
{
}

TBitField TBitField::operator&(const TBitField &bf) // операция "и"
{
}

TBitField TBitField::operator~(void) // отрицание
{
}

// ввод/вывод

istream &operator>>(istream &istr, TBitField &bf) // ввод
{
    char c;
    int i = 0;
    do{
        istr >> c;
        if (c == '1'){
            bf.SetBit(i);
        } else bf.ClrBit(i);
        k++;
    } while (c == '1' || c == '0');
    return istr;
}

ostream &operator<<(ostream &ostr, const TBitField &bf) // вывод
{
    for (int i = 0; i < BitLen; i++){
        ostr << GetBit(i);
    }
    return ostr;
}
