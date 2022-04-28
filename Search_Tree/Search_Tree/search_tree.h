#pragma once

#include "../../Binary_Tree/Binary_Tree/tree.h"

class search_tree : public binary_tree
{
protected:
	node* find_by_key(int key);

	node* max(node* subTreeRoot);
	node* min(node* subTreeRoot);

	node* maxParent(node* subTreeRoot);
	node* minParent(node* subTreeRoot);

public:
	search_tree();
	search_tree(const search_tree& other);
	~search_tree();

	search_tree copy(int index);

	int max();
	int min();

	bool add(int key);
	bool erase_by_key(int key);
	bool erase_by_index(int index);

	int index_by_key(int key);

	int height_by_key(int key);

	search_tree operator=(const search_tree& other);
};