#pragma once

#include "../../Binary_Tree/Binary_Tree/tree.h"

class search_tree : public binary_tree
{
public:
	search_tree();
	search_tree(const search_tree& other);
	~search_tree();

	search_tree copy(int index);

	int max();
	int min();

	void add(int key);
	void erase_by_key(int key);
	void erase_by_index(int index);

	int index_by_key(int key);

	int heihght(int key);

	search_tree operator=(const search_tree& other);
};