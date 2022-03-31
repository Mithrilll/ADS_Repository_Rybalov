#include <iostream>
#include <chrono>
#include "tree.h"

int main()
{
	srand(time(0));
	binary_tree bt;
	for (int i = 0; i < 10; i++)
		bt.add(i%10);

	binary_tree bt2 = bt;

	bt.printVertical();
	bt2.printVertical();
	bt2.deleteSubTree();
	bt2.printVertical();

	std::cout << bt.isEmpty() << " " << bt2.isEmpty() << std::endl;

	bt2 = bt2.copySubTree(bt.find_by_index(1));
	bt2.printVertical();

	std::cout << bt2.height() << std::endl;

	std::cout << bt2.countNodes() << std::endl;

	std::cout << bt2.min() << std::endl;
	std::cout << bt2.max() << std::endl;

	bt2.add(7);
	bt2.printVertical();

	bt.find_and_erase_by_key(1);
	bt.printVertical();

	std::cout << bt.isBalanced() << std::endl;

	std::cout << bt.sum() << std::endl;

	std::cout << bt.level(4) << std::endl;

	std::vector<int> ans = bt.round();
	for (int i : ans)
		std::cout << i << " ";
	std::cout << std::endl;

	bt.printLeafs();

	return 0;
}
