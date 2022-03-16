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

	bt.printHorizontal(bt.find_by_index(0));

	std::cout << "\n\n\n";

	bt.printHorizontal(bt.findParent_by_index(3));

	binary_tree bt2 = bt;

	std::cout << "\n\n\n";

	bt2.printHorizontal();

	return 0;
}
