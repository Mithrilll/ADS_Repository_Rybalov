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

	std::cout << st.min() << " " << st.max() << std::endl;

	std::cout << st.height_by_key(9) << std::endl;
	std::cout << st.index_by_key(5) << std::endl;

	st.deleteTree();
	st.add(5);
	st.add(2);
	st.add(8);
	st.add(1);
	st.add(3);
	st.add(6);
	st.add(10);
	st.add(9);
	st.add(10);

	st.printVertical();
	st.erase_by_key(8);
	st.printVertical();
	st.erase_by_key(5);
	st.printVertical();
	st.erase_by_index(1);
	st.printVertical();

	return 0;
}