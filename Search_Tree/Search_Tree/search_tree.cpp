#include "search_tree.h"

search_tree::search_tree() : binary_tree()
{
}

search_tree::search_tree(const search_tree& other) : binary_tree(other)
{
}

search_tree::~search_tree()
{

}

search_tree search_tree::copy(node* subTreeRoot)
{
	return search_tree();
}

int search_tree::max()
{
	return 0;
}

int search_tree::min()
{
	return 0;
}

void search_tree::add(int key)
{
}

void search_tree::erase_by_key(int key)
{
}

void search_tree::erase_by_index(int index)
{
}

binary_tree::node* search_tree::find(int key)
{
	return nullptr;
}

int search_tree::heihght(int key)
{
	return 0;
}

search_tree search_tree::operator=(const search_tree& other)
{
	return search_tree();
}
