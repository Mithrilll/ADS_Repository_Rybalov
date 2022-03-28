#include <iostream>
#include <chrono>
#include "tree.h"

int main()
{
	srand(time(0));
	binary_tree bt;
	for (int i = 0; i < 36; i++)
		bt.add(i%10);

	//bt.printHorizontal();

	//std::cout << "\n\n\n";

	//bt.printHorizontal(bt.find_by_index(0));

	//std::cout << "\n\n\n";

	//bt.printHorizontal(bt.findParent_by_index(3));

	binary_tree bt2 = bt;

	//std::cout << "\n\n\n";

	bt2.printHorizontal();

	std::cout << "\n\n\n";

	//std::cout << bt2.height() << std::endl;

	//std::cout << bt2.countNodes() << std::endl;

	//std::cout << bt2.max() << std::endl;

	//std::cout << bt2.min() << std::endl;

	//bt2.find_and_erase_by_key(1);
	bt2.printVertical();
	//bt2.printHorizontal();

	//std::cout << "\n\n\n";
	return 0;
}
