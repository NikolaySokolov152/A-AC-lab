// A_AC.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include "pch.h"

#include "ChainedHashing.h"
#include "CuckooHashing.h"
#include "DerectAddresHeashing.h"
#include <map>
#include <unordered_map>


#include "fstream"
#include <ctime>

//Лабораторная работа № 2. Сравнение различных подходов к хешированию.
//Целью данной работы является сравнение различных методов борьбы с коллизиями :
//1) Метод цепочек;
//2) Метод открытой адресации(см.Кормен, 3 - е издание, 11.4 Открытая адреация);
//3) Метод кукушки(см.https://en.wikipedia.org/wiki/Cuckoo_hashing).
//4) Для интереса, предлагается также сделать сравнения со стандартными средствами языка
//c++: std::map, std::hash_map.Вдруг получится их обогнать.


#define COUNT 50000
#define SIZE_TABLE (COUNT*2)
#define QUANT 100
#define LEN_STR 15
#define TYPE std::string
//std::string

int testHashingTabels()
{
	std::vector<std::vector<std::clock_t>> timeArrInsert(5);
	std::vector<std::vector<std::clock_t>> timeArrDelete(5);
	std::vector<std::vector<std::clock_t>> timeArrSearch(5);

	clock_t start;
	clock_t end;
	int temp;

	int countColisionDerAddHeash = 0;
	int countColisionCuckHeash = 0;


	std::random_device randD;
	std::mt19937 generator(randD());
	//std::uniform_int_distribution <> diap_rand_p(-P, P);
	std::uniform_int_distribution <> diap_rand_p(1, 255);
	std::uniform_int_distribution <> diap_rand_str(5, LEN_STR);


	DerectAddresHeash<TYPE> DerAddHeash(SIZE_TABLE);
	ChainedHash<TYPE> ChanHeash(SIZE_TABLE);
	CuckooHash<TYPE> CuckHeash(SIZE_TABLE / 2);

	//key, value
	std::map<TYPE, TYPE> Map;
	std::unordered_map<TYPE, TYPE> HeashMap;

	std::vector<TYPE> ArrCount;


	for (int i = 0; i < COUNT / QUANT; i++)
	{
		std::cout << i + 1 << " / " << COUNT / QUANT << std::endl;

		TYPE InsertElement[QUANT];
		for (int k = 0; k < QUANT; k++)
		{
			int len = diap_rand_str(generator);
			for (int s = 0; s < len; s++)
			{
				InsertElement[k] += char(diap_rand_p(generator));
			}
			//InsertElement[k] = diap_rand_p(generator);
			//std::cout << InsertElement[k] << " ";
			ArrCount.push_back(InsertElement[k]);
		}
		temp = 0;
		start = clock();
		for (int j = 0; j < QUANT; j++)
		{
			temp += DerAddHeash.Insert(InsertElement[j]);
		}
		end = clock();
		timeArrInsert[0].push_back(end - start);
		countColisionDerAddHeash += temp;


		start = clock();
		for (int j = 0; j < QUANT; j++)
		{
			ChanHeash.Insert(InsertElement[j]);
		}
		end = clock();
		timeArrInsert[1].push_back(end - start);



		temp = 0;
		start = clock();
		for (int j = 0; j < QUANT; j++)
		{
			temp += CuckHeash.Insert(InsertElement[j]);
		}
		end = clock();
		timeArrInsert[2].push_back(end - start);
		countColisionCuckHeash += temp;



		start = clock();
		for (int j = 0; j < QUANT; j++)
		{
			Map.insert(std::pair<TYPE, TYPE>(InsertElement[j], InsertElement[j]));
		}
		end = clock();
		timeArrInsert[3].push_back(end - start);



		start = clock();
		for (int j = 0; j < QUANT; j++)
		{
			HeashMap.insert(std::pair<TYPE, TYPE>(InsertElement[j], InsertElement[j]));
		}
		end = clock();
		timeArrInsert[4].push_back(end - start);


		TYPE  SesrchElements[QUANT];
		for (int k = 0; k < QUANT; k++)
		{
			SesrchElements[k] = InsertElement[k];
		}


		start = clock();
		for (int j = 0; j < QUANT; j++)
		{
			DerAddHeash.Search(SesrchElements[j]);
		}
		end = clock();
		timeArrSearch[0].push_back(end - start);

		start = clock();
		for (int j = 0; j < QUANT; j++)
		{
			ChanHeash.Search(SesrchElements[j]);
		}
		end = clock();
		timeArrSearch[1].push_back(end - start);

		start = clock();
		for (int j = 0; j < QUANT; j++)
		{
			CuckHeash.Search(SesrchElements[j]);
		}
		end = clock();
		timeArrSearch[2].push_back(end - start);

		start = clock();
		for (int j = 0; j < QUANT; j++)
		{
			Map.find(SesrchElements[j]);
		}
		end = clock();
		timeArrSearch[3].push_back(end - start);

		start = clock();
		for (int j = 0; j < QUANT; j++)
		{
			HeashMap.find(SesrchElements[j]);
		}
		end = clock();
		timeArrSearch[4].push_back(end - start);


	}

	std::cout << "end insert and search" << std::endl;

	for (int i = 0; i < COUNT / QUANT; i++)
	{
		std::cout << i + 1 << " / " << COUNT / QUANT << std::endl;

		TYPE DeletElements[QUANT];

		for (int k = 0; k < QUANT; k++)
		{
			DeletElements[k] = *(ArrCount.end() - 1);
			ArrCount.pop_back();
		}
		start = clock();
		for (int j = 0; j < QUANT; j++)
		{
			DerAddHeash.Delete(DeletElements[j]);
		}
		end = clock();
		timeArrDelete[0].push_back(end - start);

		start = clock();
		for (int j = 0; j < QUANT; j++)
		{
			ChanHeash.Delete(DeletElements[j]);
		}
		end = clock();
		timeArrDelete[1].push_back(end - start);

		start = clock();
		for (int j = 0; j < QUANT; j++)
		{
			CuckHeash.Delete(DeletElements[j]);
		}
		end = clock();
		timeArrDelete[2].push_back(end - start);

		start = clock();
		for (int j = 0; j < QUANT; j++)
		{
			Map.erase(DeletElements[j]);
		}
		end = clock();
		timeArrDelete[3].push_back(end - start);

		start = clock();
		for (int j = 0; j < QUANT; j++)
		{
			HeashMap.erase(DeletElements[j]);
		}
		end = clock();
		timeArrDelete[4].push_back(end - start);
	}

	std::cout << "end " << std::endl;

	std::ofstream file;
	file.open("result.txt");
	file << "CountDerColision " << countColisionDerAddHeash << " CountCuckColision " << countColisionCuckHeash << std::endl;

	file << "Insert" << std::endl;
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < COUNT / QUANT; j++)
		{
			file << timeArrInsert[i][j] << " ";
		}
		file << std::endl;
	}
	file << std::endl;
	file << "Search" << std::endl;
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < COUNT / QUANT; j++)
		{
			file << timeArrSearch[i][j] << " ";
		}
		file << std::endl;
	}
	file << std::endl;
	file << "InvDelete" << std::endl;
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < COUNT / QUANT; j++)
		{
			file << timeArrDelete[i][j] << " ";
		}
		file << std::endl;
	}
	file.close();



	std::cout << "CountDerColision " << countColisionDerAddHeash << " CountCuckColision " << countColisionCuckHeash << std::endl;
	std::cout << DerAddHeash.size() << std::endl;
	std::cout << ChanHeash.size() << std::endl;
	std::cout << CuckHeash.size() << std::endl;
	std::cout << Map.size() << std::endl;
	std::cout << HeashMap.size() << std::endl;



	return 0;
}
int tesrForRealData()
{
	std::ifstream rfile;
	rfile.open("vocabulary.txt", std::ios_base::in);
	if (!rfile.is_open())
	{
		std::cout << "error open" << std::endl;
		return -1;
	}
	else
	{
		std::list<std::string> List;

		while (!rfile.eof())
		{
			std::string buf;
			rfile >> buf;
			if ((((buf != ".") && (buf != ",")) && ((buf != "|") && (buf != "."))) && (((buf != "-") && (buf != " ")) && ((buf != "(") && (buf != ")"))))
			{
				List.push_back(buf);
			}
		}
		rfile.close();

		std::cout << "vocabulary size = " << List.size() << std::endl;


		std::vector<std::vector<std::clock_t>> timeArrInsert(5);
		std::vector<std::vector<std::clock_t>> timeArrDelete(5);
		std::vector<std::vector<std::clock_t>> timeArrSearch(5);

		clock_t start;
		clock_t end;
		int temp;

		int countColisionDerAddHeash = 0;
		int countColisionCuckHeash = 0;


		int sizeTable = List.size()*2;
		int countElem = List.size();

		DerectAddresHeash<TYPE> DerAddHeash(sizeTable);
		ChainedHash<TYPE> ChanHeash(sizeTable);
		CuckooHash<TYPE> CuckHeash(sizeTable/2);

		//key, value
		std::map<TYPE, TYPE> Map;
		std::unordered_map<TYPE, TYPE> HeashMap;

		std::vector<TYPE> ArrCount;



		auto listIterator = List.begin();

		for (int i = 0; i < countElem / QUANT; i++)
		{
			std::cout << i + 1 << " / " << countElem / QUANT << std::endl;

			listIterator = List.begin();
			for (int l = 0; l < i*QUANT; l++)
			{
				++listIterator;
			}


			for (int k = 0; k < QUANT; k++)
			{
				ArrCount.push_back(*listIterator);
				++listIterator;
			}

			temp = 0;
			listIterator = List.begin();
			for (int l = 0; l < i*QUANT; l++)
			{
				++listIterator;
			}
			start = clock();
			for (int j = 0; j < QUANT; j++)
			{
				temp += DerAddHeash.Insert(*listIterator);
				++listIterator;
			}
		
			end = clock();
			timeArrInsert[0].push_back(end - start);
			countColisionDerAddHeash += temp;

			listIterator = List.begin();
			for (int l = 0; l < i*QUANT; l++)
			{
				++listIterator;
			}
			start = clock();
			for (int j = 0; j < QUANT; j++)
			{
				ChanHeash.Insert(*listIterator);
				++listIterator;
			}
			end = clock();
			timeArrInsert[1].push_back(end - start);


			listIterator = List.begin();
			for (int l = 0; l < i*QUANT; l++)
			{
				++listIterator;
			}
			temp = 0;
			start = clock();
			for (int j = 0; j < QUANT; j++)
			{
				temp += CuckHeash.Insert(*listIterator);
				++listIterator;
			}
			end = clock();
			timeArrInsert[2].push_back(end - start);
			countColisionCuckHeash += temp;


			listIterator = List.begin();
			for (int l = 0; l < i*QUANT; l++)
			{
				++listIterator;
			}
			start = clock();
			for (int j = 0; j < QUANT; j++)
			{
				Map.insert(std::pair<TYPE, TYPE>(*listIterator, *listIterator));
				++listIterator;
			}
			end = clock();
			timeArrInsert[3].push_back(end - start);


			listIterator = List.begin();
			for (int l = 0; l < i*QUANT; l++)
			{
				++listIterator;
			}
			start = clock();
			for (int j = 0; j < QUANT; j++)
			{
				HeashMap.insert(std::pair<TYPE, TYPE>(*listIterator, *listIterator));
				++listIterator;
			}
			end = clock();
			timeArrInsert[4].push_back(end - start);

			listIterator = List.begin();
			for (int l = 0; l < i*QUANT; l++)
			{
				++listIterator;
			}
			start = clock();
			for (int j = 0; j < QUANT; j++)
			{
				DerAddHeash.Search(*listIterator);
				++listIterator;
			}
			end = clock();
			timeArrSearch[0].push_back(end - start);
			listIterator = List.begin();

			for (int l = 0; l < i*QUANT; l++)
			{
				++listIterator;
			}
			start = clock();
			for (int j = 0; j < QUANT; j++)
			{
				ChanHeash.Search(*listIterator);
				++listIterator;
			}
			end = clock();
			timeArrSearch[1].push_back(end - start);

			listIterator = List.begin();
			for (int l = 0; l < i*QUANT; l++)
			{
				++listIterator;
			}
			start = clock();
			for (int j = 0; j < QUANT; j++)
			{
				CuckHeash.Search(*listIterator);
				++listIterator;
			}
			end = clock();
			timeArrSearch[2].push_back(end - start);

			listIterator = List.begin();
			for (int l = 0; l < i*QUANT; l++)
			{
				++listIterator;
			}
			start = clock();
			for (int j = 0; j < QUANT; j++)
			{
				Map.find(*listIterator);
				++listIterator;
			}
			end = clock();
			timeArrSearch[3].push_back(end - start);

			listIterator = List.begin();
			for (int l = 0; l < i*QUANT; l++)
			{
				++listIterator;
			}
			start = clock();
			for (int j = 0; j < QUANT; j++)
			{
				HeashMap.find(*listIterator);
				++listIterator;
			}
			end = clock();
			timeArrSearch[4].push_back(end - start);


		}

		std::cout << "end insert and search" << std::endl;



		for (int p = 0; p < 65; p++)
		{
			List.pop_back();
		}
			
		std::cout << List.size() << std::endl;


		for (int i = 0; i < countElem / QUANT; i++)
		{
			std::cout << i + 1 << " / " << countElem / QUANT << std::endl;

			TYPE DeletElements[QUANT];

			for (int k = 0; k < QUANT; k++)
			{
				DeletElements[k] = List.back();
				List.pop_back();
				//std::cout << DeletElements[k] << " " << List.size() << std::endl;
			}

			start = clock();
			for (int j = 0; j < QUANT; j++)
			{
				DerAddHeash.Delete(DeletElements[j]);
			}
			end = clock();
			timeArrDelete[0].push_back(end - start);

			start = clock();
			for (int j = 0; j < QUANT; j++)
			{
				ChanHeash.Delete(DeletElements[j]);
			}
			end = clock();
			timeArrDelete[1].push_back(end - start);

			start = clock();
			for (int j = 0; j < QUANT; j++)
			{
				CuckHeash.Delete(DeletElements[j]);
			}
			end = clock();
			timeArrDelete[2].push_back(end - start);

			start = clock();
			for (int j = 0; j < QUANT; j++)
			{
				Map.erase(DeletElements[j]);
			}
			end = clock();
			timeArrDelete[3].push_back(end - start);

			start = clock();
			for (int j = 0; j < QUANT; j++)
			{
				HeashMap.erase(DeletElements[j]);
			}
			end = clock();
			timeArrDelete[4].push_back(end - start);
		}

		std::cout << "end " << std::endl;





		std::ofstream wfile;
		wfile.open("realrez.txt");


		wfile << "CountDerColision " << countColisionDerAddHeash << " CountCuckColision " << countColisionCuckHeash << std::endl;

		wfile << "Insert" << std::endl;
		for (int i = 0; i < 5; i++)
		{
			for (int j = 0; j < countElem / QUANT; j++)
			{
				wfile << timeArrInsert[i][j] << " ";
			}
			wfile << std::endl;
		}
		wfile << std::endl;
		wfile << "Search" << std::endl;
		for (int i = 0; i < 5; i++)
		{
			for (int j = 0; j < countElem / QUANT; j++)
			{
				wfile << timeArrSearch[i][j] << " ";
			}
			wfile << std::endl;
		}
		wfile << std::endl;
		wfile << "InvDelete" << std::endl;
		for (int i = 0; i < 5; i++)
		{
			for (int j = 0; j < countElem / QUANT; j++)
			{
				wfile << timeArrDelete[i][j] << " ";
			}
			wfile << std::endl;
		}

		wfile.close();



		std::cout << "CountDerColision " << countColisionDerAddHeash << " CountCuckColision " << countColisionCuckHeash << std::endl;
		//std::cout << DerAddHeash.size() << std::endl;
		//std::cout << ChanHeash.size() << std::endl;
		//std::cout << CuckHeash.size() << std::endl;
		//std::cout << Map.size() << std::endl;
		//std::cout << HeashMap.size() << std::endl;

		return 0;
	}
}


int main()
{

	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	setlocale(LC_ALL, "Russian");

	//testHashingTabels();
	tesrForRealData();
	return 0;
}

