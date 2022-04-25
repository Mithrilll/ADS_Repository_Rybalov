#include "search_tree.h"

search_tree::search_tree() : binary_tree()
{
}

search_tree::search_tree(const search_tree& other) : binary_tree(other)
{
}

search_tree::~search_tree()
{
	deleteTree();
}

search_tree search_tree::copy(int index)
{
	node* subTreeRoot = find_by_index(index);
	search_tree newTree;
	
	newTree.m_root = copy(subTreeRoot);
	return newTree;
}

int search_tree::max()
{
	
	if (m_root == nullptr)
		return INT_MIN;

	int key = m_root->value();
	node* temp = m_root;
	while (temp->right)
	{
		temp = temp->right;
		key = temp->value();
	}

	return key;
}

int search_tree::min()
{
	if (m_root == nullptr)
		return INT_MIN;

	int key = m_root->value();
	node* temp = m_root;
	while (temp->left)
	{
		temp = temp->left;
		key = temp->value();
	}

	return key;
}

void search_tree::add(int key)
{
	if (m_root == nullptr)
	{
		m_root = new node(key);
	}
	else
	{
		node* temp = m_root;
		while (temp->left && key < temp->value() || temp->right && key >= temp->value())
		{
			if (key < temp->value())
				temp = temp->left;
			else
				temp = temp->right;
		}
		if (key < temp->value())
		{
			node* left = new node(key);
			temp->left = left;
		}
		else
		{
			node* right = new node(key);
			temp->right = right;
		}
	}
}

void search_tree::erase_by_key(int key)
{
}

void search_tree::erase_by_index(int index)
{
}

int search_tree::index_by_key(int key)
{
	return 0;
}

int search_tree::heihght(int key)
{
	if (m_root == nullptr)
		return -1;

	int h = 0;
	node* temp = m_root;
	while (temp->left && key < temp->value() || temp->right && key > temp->value())
	{
		if (key < temp->value())
			temp = temp->left;
		else
			temp = temp->right;
		h++;
	}

	if (key == temp->value())
		return h;
	else
		return -1;
}

search_tree search_tree::operator=(const search_tree& other)
{
	if (&other == this)
		return *this;

	deleteSubTree(m_root);

	m_root = copy(other.m_root);

	return *this;
}
