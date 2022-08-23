#include "balanced_search_tree.h"
#include <iostream>

bool balanced_search_tree::erase(node* toDelete, node* parent)
{
	bool erased = true;
	erased = search_tree::erase(toDelete, parent);

	balance(m_root, nullptr);

	return erased;
}

void balanced_search_tree::balance(node* subTreeRoot, node* parent)
{
	if (subTreeRoot && (subTreeRoot->left || subTreeRoot->right))
	{
		balance(subTreeRoot->left, subTreeRoot);
		balance(subTreeRoot->right, subTreeRoot);

		int h1 = height(subTreeRoot->left);
		int h2 = height(subTreeRoot->right);

		if (h1 - h2 == 2)
		{
			int h1_1 = height(subTreeRoot->left->left);
			int h1_2 = height(subTreeRoot->left->right);
			if (h1_1 - h1_2 > -1)
			{
				node* temp = subTreeRoot->left;
				subTreeRoot->left = subTreeRoot->left->right;
				temp->right = subTreeRoot;
				if (parent == nullptr)
					m_root = temp;
				else
				{
					if (parent->left == subTreeRoot)
						parent->left = temp;
					else
						parent->right = temp;
				}
			}
			else
			{
				node* temp = subTreeRoot->left->right;
				subTreeRoot->left->right = temp->left;
				temp->left = subTreeRoot->left;
				subTreeRoot->left = temp->right;
				temp->right = subTreeRoot;
				if (parent == nullptr)
					m_root = temp;
				else
				{
					if (parent->left == subTreeRoot)
						parent->left = temp;
					else
						parent->right = temp;
				}
			}
		}

		if (h1 - h2 == -2)
		{
			int h2_1 = height(subTreeRoot->right->left);
			int h2_2 = height(subTreeRoot->right->right);
			if (h2_1 - h2_2 < 1)
			{
				node* temp = subTreeRoot->right;
				subTreeRoot->right = subTreeRoot->right->left;
				temp->left = subTreeRoot;
				if (parent == nullptr)
					m_root = temp;
				else
				{
					if (parent->left == subTreeRoot)
						parent->left = temp;
					else
						parent->right = temp;
				}
			}
			else
			{
				node* temp = subTreeRoot->right->left;
				subTreeRoot->right->left = temp->right;
				temp->right = subTreeRoot->right;
				subTreeRoot->right = temp->left;
				temp->left = subTreeRoot;
				if (parent == nullptr)
					m_root = temp;
				else
				{
					if (parent->left == subTreeRoot)
						parent->left = temp;
					else
						parent->right = temp;
				}
			}
		}
	}
}

balanced_search_tree::balanced_search_tree() : search_tree()
{

}

balanced_search_tree::balanced_search_tree(const balanced_search_tree& other) : search_tree(other)
{
}

balanced_search_tree::~balanced_search_tree()
{
	deleteTree();
}

balanced_search_tree balanced_search_tree::copyTree(int index)
{
	node* subTreeRoot = find_by_index(index);
	balanced_search_tree newTree;

	newTree.m_root = binary_tree::copy(subTreeRoot);
	return newTree;;
}

bool balanced_search_tree::add(int value)
{
	bool added = true;

	added = search_tree::add(value);

	balance(m_root, nullptr);

	return added;
}

balanced_search_tree& balanced_search_tree::operator=(const balanced_search_tree& other)
{
	binary_tree::operator=(other);
	return *this;
}
