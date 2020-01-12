#pragma once

#include "Elements.h"

template <typename T>
class DerectAddresHeash
{
public:
	int Search(const T x)
	{
		int i = HeashFunction(hash, sizeTable, x);
		while (i < sizeTable)
		{
			if ((Arr[i].use == true) && (Arr[i].value == x))
				return i;
			++i;
		}
		return -1;
	}
	int Insert(T x)
	{
		int i = HeashFunction(hash, sizeTable, x);
		while (i < sizeTable)
		{
			if (Arr[i].use == true)
				if (Arr[i].value == x)
					return 0;
				else
				++i;
			else
			{
				Arr[i] = Elem<T>(x);
				sizeElem++;
				return 0;
			}
		}
		return 1;
	}
	int Delete(T x)
	{
		int index = Search(x);
		if (index == -1)
		{
			return 1;
		}
		else
		{
			sizeElem--;
			Arr[index].use = false;
			return 0;
		}
	}
	void Print()
	{
		if (sizeElem > 0)
		{
			for (int i = 0; i < sizeTable; i++)
			{
				if (Arr[i].use == true)
					std::cout << Arr[i].value << " ";
			}
			std::cout << std::endl;
		}
	}
	int size()
	{
		return sizeElem;
	}
	DerectAddresHeash()
	{
		sizeTable = 10;
		sizeElem = 0;
		Arr= std::vector<Elem<T>>(10);
	}
	DerectAddresHeash(int m):sizeTable(m)
	{
		Arr = std::vector<Elem<T>>(m);
		sizeElem = 0;
	}
	~DerectAddresHeash(){}

private:
	int sizeTable;  //m
	int sizeElem;
	std::vector<Elem<T>> Arr;
	Hash hash;
};