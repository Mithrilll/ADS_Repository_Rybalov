#include <iostream>
#include <chrono>
#include "tree.h"

int main()
{
	srand(time(0));
	binary_tree bt;
	int treeSize = 50;
	for (int i = 0; i < treeSize; i++) {
		bt.add(i);
		std::cout << bt.countNodes() << " " << bt.height() << std::endl;
	}

	std::cout << "------------------------------------------" << std::endl;

	/*for (int i = 0; i < treeSize; i++) {
		bt.find_and_erase_by_index(i);
		std::cout << bt.countNodes() << " " << bt.height() << std::endl;
	}*/

	for (int i = treeSize - 1; i >= 0; --i)
	{
		bt.find_and_erase_by_index(i);
		std::cout << bt.countNodes() << " " << bt.height() << std::endl;
	}

	std::cout << "------------------------------------------" << std::endl;

	bt.printVertical();

	std::cout << bt.indexParent_by_key(7) << std::endl;;

	return 0;
}

