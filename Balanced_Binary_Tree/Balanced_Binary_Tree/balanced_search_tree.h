#pragma once

#include "../../Search_Tree/Search_Tree/search_tree.h"

class balanced_search_tree : public search_tree
{
private:

	bool erase(node* toDelete, node* parent) override;

	void balance(node* subTreeRoot, node* parent);

public:
	balanced_search_tree();
	balanced_search_tree(const balanced_search_tree& other);
	~balanced_search_tree();

	balanced_search_tree copyTree(int index);

	bool add(int value) override;

	balanced_search_tree& operator=(const balanced_search_tree& other);

};