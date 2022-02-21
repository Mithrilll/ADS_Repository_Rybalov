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
void split(const char* filenameIn, const char* filenameOut1, const char* filenameOut2)
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
bool check(const char* filenameIn1, const char* filenameIn2, const char* filenameIn3, const char* filenameIn4)
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
void print(const char* filename)
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
const char* sorted(const char* filename1, const char* filename2, const char* filename3, const char* filename4)
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

int main()
{
    int n;

    std::cout << "Enter count of numbers in sequence: ";
    std::cin >> n;

    createFileWithRandomNumbers("A.txt", n, 10000);
    std::cout << "Primal sequence: ";
    print("A.txt");

    clock_t start, finish;

    start = clock();

    split("A.txt", "C.txt", "D.txt");

    int i = 1;
    while (!check("A.txt", "B.txt", "C.txt", "D.txt"))
    {
        Direct_Merge("C.txt", "D.txt", "A.txt", "B.txt", i);
        i *= 2;
        Direct_Merge("A.txt", "B.txt", "C.txt", "D.txt", i);
        i *= 2;
    }

    finish = clock();

    std::cout << "\nSorted sequence: ";
    print(sorted("A.txt", "B.txt", "C.txt", "D.txt"));

    std::cout << "\nAlgorithm running time : " << (float)(finish - start) / CLOCKS_PER_SEC << " sek.";

    return 0;
}