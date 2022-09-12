#include <iostream>
#include "huffman.h"

int main()
{
	huffman code;

	std::cout << code.encode("input.txt", "output.txt") << std::endl;

	code.decode("output.txt", "decode.txt");

	return 0;
}