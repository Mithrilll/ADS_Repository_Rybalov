#include <iostream>
#include <chrono>
#include "tree.h"

int main()
{
	srand(time(0));
	binary_tree bt;
	for (int i = 0; i < 10; i++)
		bt.add(bt.getRoot(), i);

	bt.printHorizontal();

	std::cout << "\n\n\n";

	bt.printHorizontal(bt.find_by_key(4));

	std::cout << "\n\n\n";

	bt.printHorizontal(bt.findParent_by_key(4));

	return 0;
}
