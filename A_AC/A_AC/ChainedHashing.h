#pragma once
#include "Elements.h"


template <typename T>
class ChainedHash
{
public:
	auto Search(T x)
	{
		int i = HeashFunction(hash, sizeTable, x);
		return std::find(Arr[i].begin(), Arr[i].end(), Elem<T>(x));
	}
	int Insert(T x)
	{
		int i = HeashFunction(hash, sizeTable, x);
		if (std::find(Arr[i].begin(), Arr[i].end(), Elem<T>(x)) == Arr[i].end())
		{
			Arr[i].push_back(Elem<T>(x));
			sizeElem++;
			return 0;
		}
        return 1;
	}
	int Delete(T x)
	{
		int i = HeashFunction(hash, sizeTable, x);
		int before = Arr[i].size();
		Arr[i].remove(Elem<T>(x));
		if (before == Arr[i].size())
			return 1;
		sizeElem--;
			return 0;
	}

	void Print()
	{
		if (sizeElem > 0)
		{
			for (int i = 0; i < sizeTable; i++)
			{
				for (auto iter = Arr[i].begin(); iter != Arr[i].end(); ++iter)
				{
					if ((*iter).use == true)
						std::cout << (*iter).value << " ";
				}
			}
			std::cout << std::endl;
		}
	}
	int size()
	{
		return sizeElem;
	}


	ChainedHash()
	{
		sizeTable = 10;
		Arr = std::vector<std::list<Elem<T>>>(10);
		sizeElem = 0;
	}
	ChainedHash(int m) :sizeTable(m)
	{
		Arr = std::vector<std::list<Elem<T>>>(m);
		sizeElem = 0;
	}
	~ChainedHash() 	{}
private:
	int sizeTable;     //m
	int sizeElem;
	std::vector<std::list<Elem<T>>> Arr;
	Hash hash;
};