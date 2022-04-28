#include <iostream>
#include "search_tree.h"

int main()
{
	search_tree st;

	std::cout << st.height_by_key(9) << std::endl;

	st.add(10);
	st.add(5);
	st.add(6);
	st.add(5);
	st.add(3);
	st.add(15);
	st.add(28);
	st.add(27);	

	st.printVertical();

	//std::cout << st.min() << " " << st.max() << std::endl;

	std::cout << st.height_by_key(9) << std::endl;
	std::cout << st.index_by_key(5) << std::endl;

	binary_tree* tree = &st;

	tree->deleteTree();
	tree->add(5);
	tree->add(2);
	tree->add(8);
	tree->add(1);
	tree->add(3);
	tree->add(6);
	tree->add(10);
	tree->add(9);
	tree->add(10);

	tree->printVertical();
	tree->find_and_erase_by_key(8);
	tree->printVertical();
	tree->find_and_erase_by_key(5);
	tree->printVertical();
	tree->find_and_erase_by_index(1);
	tree->printVertical();

	return 0;
}