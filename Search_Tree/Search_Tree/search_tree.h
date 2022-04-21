#pragma once

#include "../../Binary_Tree/Binary_Tree/tree.h"

class search_tree : public binary_tree
{
public:
	search_tree();
	search_tree(const search_tree& other);
	~search_tree();

	search_tree copy(node* subTreeRoot);

	int max();
	int min();

	void add(int key);
	void erase_by_key(int key);
	void erase_by_index(int index);

	node* find(int key);

	int heihght(int key);

	search_tree operator=(const search_tree& other);
};