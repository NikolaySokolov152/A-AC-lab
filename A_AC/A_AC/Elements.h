#pragma once
#include <iostream>
#include <vector>
#include <list>
#include <random>
#include <ctime>  
#include <algorithm>
#include <string>
#include <locale>

//2^31 - 1
#define P (INT_MAX)

struct Hash
{
public:
	int a;
	int b;
	Hash()
	{
		std::random_device randD;
		std::mt19937 generator(randD());
		std::uniform_int_distribution <> diap_rand_a(1, (P - 1));
		a = diap_rand_a(generator);
		std::uniform_int_distribution <> diap_rand_b(0, (P - 1));
		b = diap_rand_b(generator);
	}
};


template <typename T>
struct Elem 
{
public:
	bool use;
	T value;
	Elem() 
	{
		value;
		use = false;
	}
	Elem(T val)
	{
		value = val;
		use = true;
	}

	bool operator ==(const Elem &B)
	{
		if (this->use == B.use)
			if (this->value == B.value)
				return true;
		return false;
	}
	bool operator !=(const Elem &B)
	{
		if (this->use != B.use)
			if (this->value != B.value)
				return false;
		return true;
	}

};


template <typename T>
int HeashFunction(const Hash hash,const int size_table,const T x) 
{
	return ((hash.a * x + hash.b) & P) % size_table;
}
template <typename T>
int HeashFunction(const Hash hash, const int size_table, const Elem<T> x)
{
	return ((hash.a * x.value + hash.b) & P) % size_table;
}


template <typename T>
int HeashFunction(const Hash hash, const int size_table, const std::vector<T> x)
{
	int64_t h = 0;
	for (int i = 0; i < x.size(); ++i)
	{
		int64_t stepen = 1;
		for (int x = 0; x < i; x++)
		{
			stepen *= hash.a;
		}
		h += x[i] * stepen;
	}
	return (h & P) % size_table;
}
template <typename T>
int HeashFunction(const Hash hash, const int size_table, const Elem<std::vector<T>> x)
{

	int64_t h = 0;
	for (int i = 0; i < x.value.size(); ++i)
	{
		int64_t stepen = 1;
		for (int x = 0; x < i; x++)
		{
			stepen *= hash.a;
		}
		h += x.value[i] * stepen;
	}
	return (h & P) % size_table;
	}





int HeashFunction(const Hash hash, const int size_table, const std::string x)
{
	int64_t h = 0;
	for (int i = 0; i < x.size(); ++i)
	{
		int64_t stepen = 1;
		for (int x = 0; x < i; x++)
		{
			stepen *= hash.a;
		}
		h += int64_t(x[i]) * stepen;
	}

	return (h & P) % size_table;
}
int HeashFunction(const Hash hash, const int size_table, const Elem<std::string> x)
{
	int64_t h = 0;
	for (int i = 0; i < x.value.size(); ++i)
	{
		int64_t stepen = 1;
		for (int x = 0; x < i; x++)
		{
			stepen *= hash.a;
		}
		h += int64_t(x.value[i]) * stepen;
	}
	return (h & P) % size_table;
}