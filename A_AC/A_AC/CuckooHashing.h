#pragma once
#include "Elements.h"


template <typename T>
class CuckooHash
{
public:
	int Search(T x)
	{
		int i_second = HeashFunction(hash_second, sizeTwoTable, x);

		if (Arr_second[i_second].value == x)
			if (Arr_second[i_second].use == true)
				return i_second + sizeTwoTable;
			else return -1;

		int i_first = HeashFunction(hash_first, sizeTwoTable, x);

		if (Arr_first[i_first].value == x)
			if (Arr_first[i_first].use == true)
				return i_first;
			else return -1;

		int count = 2;

		while (count < len_search)
		{

			i_second = HeashFunction(hash_second, sizeTwoTable, Arr_first[i_first]);

			if (Arr_second[i_second].value == x)
				if (Arr_second[i_second].use == true)
					return i_second + sizeTwoTable;
				else return -1;

			i_first = HeashFunction(hash_first, sizeTwoTable, Arr_second[i_second]);

			if (Arr_first[i_first].value == x)
				if (Arr_first[i_first].use == true)
					return i_first;
				else return -1;
				
			count += 2;

		}
		return -1;
	}
	int Insert(T x)
	{
		int i_second = HeashFunction(hash_second, sizeTwoTable, x);
		if (Arr_second[i_second].use == false)
		{
			Arr_second[i_second].use = true;
			Arr_second[i_second].value = x;
			++sizeElem;
			return 0;
		}
		else
			if (Arr_second[i_second].value == x)
				return 0;


		int i_first = HeashFunction(hash_first, sizeTwoTable, x);
		if (Arr_first[i_first].use == false)
		{
			++sizeElem;
			Arr_first[i_first].use = true;
			Arr_first[i_first].value = x;
			return 0;
		}
		else
			if (Arr_first[i_first].value == x)
				return 0;

		int count = 2;

		while (count < len_search)
		{
			i_second = HeashFunction(hash_second, sizeTwoTable, Arr_first[i_first].value);
			if (Arr_second[i_second].use == false)
			{
				Arr_second[i_second].use = true;
				Arr_second[i_second].value = x;
				++sizeElem;
				return 0;
			}
			else
				if (Arr_second[i_second].value == x)
					return 0;

			i_first = HeashFunction(hash_first, sizeTwoTable, Arr_second[i_second].value);
			if (Arr_first[i_first].use == false)
			{
				++sizeElem;
				Arr_first[i_first].use = true;
				Arr_first[i_first].value = x;
				return 0;

			}
			else
				if (Arr_first[i_first].value == x)
					return 0;


			count += 2;



		}
		return 1;
	}
	int Delete(T x)
	{
		int index = Search(x);
		if (index == -1)
			return 1;

		int count = 0;
		if (index < sizeTwoTable)
		{
			Arr_first[index].use = false;
		}
		else
		{
			Arr_second[index - sizeTwoTable].use = false;
		}
		sizeElem--;
		//~(*iter).value();
		return 0;

	}

	void Print()
	{
		if (sizeElem > 0)
		{
			for (int i = 0; i < sizeTwoTable; i++)
			{
				if (Arr_first[i].use == true)
					std::cout << Arr_first[i].value << " ";
				if (Arr_second[i].use == true)
					std::cout << Arr_second[i].value << " ";
			}
			std::cout << std::endl;
		}
	}
	int size()
	{
		return sizeElem;
	}

	CuckooHash()
	{
		sizeTwoTable = 10;
		Arr_first = std::vector<Elem<T>>(10);
		Arr_second = std::vector<Elem<T>>(10);
		sizeElem = 0;
		len_search = 3 * log(10);
	}
	CuckooHash(int m) :sizeTwoTable(m)
	{
		Arr_first = std::vector<Elem<T>>(m);
		Arr_second = std::vector<Elem<T>>(m);
		sizeElem = 0;
		len_search = round(3 * std::log2(2 * m));
	}
	~CuckooHash() {}
private:
	int sizeElem;
	int sizeTwoTable;
	int len_search;
	std::vector<Elem<T>> Arr_first;
	std::vector<Elem<T>> Arr_second;
	Hash hash_first;
	Hash hash_second;
};

