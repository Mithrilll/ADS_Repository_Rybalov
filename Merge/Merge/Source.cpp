#include <iostream>
#include <fstream>
#include <random>
#include <time.h>

bool createFileWithRandomNumbers(const std::string& fileName, const int numbersCount, const int maxNumberValue)
{
	srand(time(0));

	std::ofstream fout;
	fout.open(fileName);
	if (!fout.is_open())
	{
		//throw "Cannot open file";
		return false;
	}

	std::default_random_engine generator;
	std::uniform_int_distribution<int> distribution(0, maxNumberValue);
	generator.seed(time(0));

	for (int i = 0; i < numbersCount; i++)
		fout << distribution(generator) << " ";

	fout.close();

	return true;
}

bool isFileContainsSortedArray(const std::string& fileName)
{
	std::ifstream fin;
	fin.open(fileName);
	if (!fin.is_open())
	{
		//throw "Cannot open file";
		return false;
	}

	int curr, int prev;
	fin >> prev;
	while (fin >> curr)
	{
		if (curr < prev)
		{
			fin.close();
			return false;
		}

		prev = curr;
	}

	fin.close();

	return true;
}

int main()
{
	createFileWithRandomNumbers("test.txt", 1000, 50000);

	return 0;
}