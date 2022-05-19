#include <iostream>
#include "balanced_search_tree.h"

int main()
{
	balanced_search_tree bst;

	for (int i = 0; i < 10; i++)
		bst.add(10-i);

	bst.printVertical();

	bst.find_and_erase_by_key(7);

	bst.printVertical();

	return 0;
}