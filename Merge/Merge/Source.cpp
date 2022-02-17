#include <iostream>
#include <fstream>
#include <random>
#include <time.h>

bool createFileWithRandomNumbers(const std::string& filename, const int numbersCount, const int maxNumberValue)
{
	srand(time(0));

	std::ofstream fout;
	fout.open(filename);
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



int main()
{
	createFileWithRandomNumbers("test.txt", 1000, 50000);

	return 0;
}