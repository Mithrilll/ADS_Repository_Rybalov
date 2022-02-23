#include <iostream>
#include <fstream>
#include <string>
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

    int curr, prev;
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

// Merge sequences of numbers of size "size", from files "filenameIn1" and "filenameIn2" to file "filenameOut"
void Direct_Merge(const std::string filenameIn1, const std::string filenameIn2, const std::string filenameOut1, const std::string filenameOut2, int size)
{
    std::ifstream fin1;
    std::ifstream fin2;
    std::ofstream fout1;
    std::ofstream fout2;


    fin1.open(filenameIn1, std::ios_base::in);
    if (!fin1)
    {
        std::cout << "\nCan't open file: " << filenameIn1 << "!" << std::endl;
        return;
    }

    fin2.open(filenameIn2, std::ios_base::in);
    if (!fin2)
    {
        std::cout << "\nCan't open file: " << filenameIn2 << "!" << std::endl;
        return;
    }

    fout1.open(filenameOut1, std::ios_base::trunc);
    if (!fout1)
    {
        std::cout << "\nCan't open file: " << filenameOut1 << "!" << std::endl;
        return;
    }

    fout2.open(filenameOut2, std::ios_base::trunc);
    if (!fout2)
    {
        std::cout << "\nCan't open file: " << filenameOut2 << "!" << std::endl;
        return;
    }

    int x, y;
    fin1 >> x; // read number from first infile
    fin2 >> y; // read number from second infile
    while (!fin1.eof() && !fin2.eof())
    {
        int i = 0;
        int j = 0;
        while (!fin1.eof() && !fin2.eof() && i < size && j < size)
        {
            if (x < y)
            {
                fout1 << x << " "; // write number from first infile to fist outfile
                fin1 >> x;
                i++;
            }
            else
            {
                fout1 << y << " "; // write number from second infile to fist outfile
                fin2 >> y;
                j++;
            }
        }

        while (!fin1.eof() && i < size)
        {
            fout1 << x << " "; // write number from first infile to fist outfile
            fin1 >> x;
            i++;
        }

        while (!fin2.eof() && j < size)
        {
            fout1 << y << " "; // write number from second infile to fist outfile
            fin2 >> y;
            j++;
        }

        i = 0;
        j = 0;

        while (!fin1.eof() && !fin2.eof() && i < size && j < size)
        {
            if (x < y)
            {
                fout2 << x << " "; // write number from first infile to second outfile
                fin1 >> x;
                i++;
            }
            else
            {
                fout2 << y << " "; // write number from second infile to second outfile
                fin2 >> y;
                j++;
            }
        }

        while (!fin1.eof() && i < size)
        {
            fout2 << x << " "; // write number from first infile to second outfile
            fin1 >> x;
            i++;
        }

        while (!fin2.eof() && j < size)
        {
            fout2 << y << " "; // write number from second infile to second outfile
            fin2 >> y;
            j++;
        }
    }

    while (!fin1.eof())
    {
        fout1 << x << " "; // write number from first infile to fist outfile
        fin1 >> x;
    }

    while (!fin2.eof())
    {
        fout1 << y << " "; // write number from second infile to fist outfile
        fin2 >> y;
    }

    fin1.close();
    fin2.close();
    fout1.close();
    fout2.close();

    fout1.open(filenameIn1, std::ios_base::trunc); // clear first infile
    fout2.open(filenameIn2, std::ios_base::trunc); // clear second infile
    fout1.close();
    fout2.close();
}

// Split into sequences of numbers of size "size", from file "filenameIn" to files "filenameOut1" and "filenameOut2"
void split(const std::string& filenameIn, const std::string& filenameOut1, const std::string& filenameOut2)
{
    std::ifstream fin;
    std::ofstream fout1;
    std::ofstream fout2;
    int size = 1;

    fin.open(filenameIn, std::ios_base::in);
    if (!fin)
    {
        std::cout << "\nCan't open file: " << filenameIn << "!" << std::endl;
        return;
    }

    fout1.open(filenameOut1, std::ios_base::trunc);
    if (!fout1)
    {
        std::cout << "\nCan't open file: " << filenameOut1 << "!" << std::endl;
        return;
    }

    fout2.open(filenameOut2, std::ios_base::trunc);
    if (!fout2)
    {
        std::cout << "\nCan't open file: " << filenameOut2 << "!" << std::endl;
        return;
    }

    // split
    int x;
    fin >> x;
    while (!fin.eof())
    {
        int i = 0;
        while (!fin.eof() && i < size)
        {
            fout1 << x << " ";
            fin >> x;
            i++;
        }
        i = 0;
        while (!fin.eof() && i < size)
        {
            fout2 << x << " ";
            fin >> x;
            i++;
        }
    }

    fin.close();
    fout1.close();
    fout2.close();
}

// Checking if a sequence of numbers is sorted
bool check(const std::string& filenameIn1, const std::string& filenameIn2, const std::string& filenameIn3, const std::string& filenameIn4)
{
    std::ifstream fin;
    int cnt = 0;
    char c;

    fin.open(filenameIn1);
    if (fin.peek() == std::ifstream::traits_type::eof())
        cnt++;
    fin.close();

    fin.open(filenameIn2);
    if (fin.peek() == std::ifstream::traits_type::eof())
        cnt++;
    fin.close();

    fin.open(filenameIn3);
    if (fin.peek() == std::ifstream::traits_type::eof())
        cnt++;
    fin.close();

    fin.open(filenameIn4);
    if (fin.peek() == std::ifstream::traits_type::eof())
        cnt++;
    fin.close();

    //if 3 file are empty
    if (cnt == 3)
        return true;

    return false;
}

// Print sequence of numbers from file "filename"
void print(const std::string& filename)
{
    std::ifstream fin;
    std::ofstream fout;

    fin.open(filename, std::ios_base::in);
    int x;
    std::cout << std::endl;
    while (fin >> x)
    {
        std::cout << x << " ";
    }

    fin.close();
}

//returns filename stores sorted sequnce
std::string sorted(const std::string& filename1, const std::string& filename2, const std::string& filename3, const std::string& filename4)
{
    std::ifstream fin;

    fin.open(filename1);
    if (!(fin.peek() == std::ifstream::traits_type::eof()))
    {
        fin.close();
        return filename1;
    }
    fin.close();

    fin.open(filename2);
    if (!(fin.peek() == std::ifstream::traits_type::eof()))
    {
        fin.close();
        return filename2;
    }
    fin.close();

    fin.open(filename3);
    if (!(fin.peek() == std::ifstream::traits_type::eof()))
    {
        fin.close();
        return filename3;
    }
    fin.close();

    fin.open(filename4);
    if (!(fin.peek() == std::ifstream::traits_type::eof()))
    {
        fin.close();
        return filename4;
    }
    fin.close();

    return "A.txt";
}

void sortFile(const std::string& fileName)
{
    split(fileName, "C.txt", "D.txt");

    int i = 1;
    while (!check(fileName, "B.txt", "C.txt", "D.txt"))
    {
        Direct_Merge("C.txt", "D.txt", fileName, "B.txt", i);
        i *= 2;
        Direct_Merge(fileName, "B.txt", "C.txt", "D.txt", i);
        i *= 2;
    }
}

int createAndSortFile(const std::string& fileName, const int  numbersCount, const int maxNumberValue)
{
    if (!createFileWithRandomNumbers("A.txt", numbersCount, maxNumberValue))
        return -1;

    /*std::cout << "Primal sequence: ";
    print(fileName);*/

    clock_t start, finish;

    start = clock();

    sortFile(fileName);

    finish = clock();
    
    /*std::cout << "\nSorted sequence: ";
    print(sorted("A.txt", "B.txt", "C.txt", "D.txt"));*/

    std::cout << "\nAlgorithm running time : " << (float)(finish - start) / CLOCKS_PER_SEC << " sek.\n";

    if (!isFileContainsSortedArray(fileName))
        return -2;

    return 1;
}

int main()
{
    std::string fileName = "A.txt";
    const int numbersCount = 1000000;
    const int maxNumberValue = 100000;

    for (int i = 0; i < 10; i++)
    {
        switch (createAndSortFile(fileName, numbersCount, maxNumberValue))
        {
        case 1:
            std::cout << "Test passed." << std::endl;
            break;

        case -1:
            std::cout << "Test failed: can't create file." << std::endl;
            break;

        case -2:
            std::cout << "Test failed: file isn't sorted." << std::endl;
            break;
        }
    }

    return 0;
}