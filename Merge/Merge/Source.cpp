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
		// "Cannot open file";
		return false;
	}

	for (int i = 0; i < numbersCount; i++)
		fout << rand() % (maxNumberValue + 1) << " ";

	fout.close();

	return true;
}



int main()
{
	std::cout << "Hello world!" << std::endl;

	return 0;
}