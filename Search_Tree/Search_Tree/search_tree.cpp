#include "search_tree.h"

binary_tree::node* search_tree::find_by_key(int key)
{
	if (m_root == nullptr)
		return nullptr;

	node* temp = m_root;
	while (temp->left && key < temp->value() || temp->right && key > temp->value())
	{
		if (key < temp->value())
			temp = temp->left;
		else
			temp = temp->right;
	}

	if (key == temp->value())
		return temp;
	else
		return nullptr;
}

binary_tree::node* search_tree::max(node* subTreeRoot)
{
	if (subTreeRoot == nullptr)
		return nullptr;

	node* temp = subTreeRoot;
	while (temp->right)
	{
		temp = temp->right;
	}

	return temp;
}

binary_tree::node* search_tree::min(node* subTreeRoot)
{
	if (subTreeRoot == nullptr)
		return nullptr;

	node* temp = subTreeRoot;
	while (temp->left)
	{
		temp = temp->left;
	}

	return temp;
}

binary_tree::node* search_tree::maxParent(node* subTreeRoot)
{
	if (subTreeRoot == nullptr || subTreeRoot->right == nullptr)
		return nullptr;

	node* m = max(subTreeRoot);
	node* temp = subTreeRoot;
	while (temp->right && temp->right->right)
	{
		temp = temp->right;
	}

	if (temp->right == m)
		return temp;
	else
		return nullptr;
}

binary_tree::node* search_tree::minParent(node* subTreeRoot)
{
	if (subTreeRoot == nullptr || subTreeRoot->left == nullptr)
		return nullptr;
	node* m = min(subTreeRoot);
	node* temp = subTreeRoot;
	while (temp->left && temp->left->left)
	{
		temp = temp->left;
	}

	if (temp->left == m)
		return temp;
	else
		return nullptr;
}

bool search_tree::erase(node* toDelete, node* parent)
{
	if (toDelete == nullptr)
		return false;

	if (toDelete->left == nullptr && toDelete->right == nullptr)
	{
		if (parent && parent->left == toDelete)
			parent->left = nullptr;

		if (parent && parent->right == toDelete)
			parent->right = nullptr;

		if (!parent)
			m_root = nullptr;

		delete toDelete;

		return true;
	}

	if (toDelete->left == nullptr && toDelete->right != nullptr)
	{
		if (parent && parent->left == toDelete)
			parent->left = toDelete->right;

		if (parent && parent->right == toDelete)
			parent->right = toDelete->right;

		if (!parent)
			m_root = toDelete->right;

		delete toDelete;

		return true;
	}

	if (toDelete->left != nullptr && toDelete->right == nullptr)
	{
		if (parent && parent->left == toDelete)
			parent->left = toDelete->left;

		if (parent && parent->right == toDelete)
			parent->right = toDelete->left;

		if (!parent)
			m_root = toDelete->left;

		delete toDelete;

		return true;
	}

	if (toDelete->left && toDelete->right)
	{
		node* to_insert = min(toDelete->right);
		node* parent_insert = minParent(toDelete->right);

		if (parent_insert)
		{
			parent_insert->left = to_insert->right;
			to_insert->left = toDelete->left;
			to_insert->right = toDelete->right;
		}
		else
		{
			to_insert->left = toDelete->left;
		}

		if (parent && parent->left == toDelete)
			parent->left = to_insert;

		if (parent && parent->right == toDelete)
			parent->right = to_insert;

		if (!parent)
			m_root = to_insert;

		delete toDelete;

		return true;
	}
}

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
	
	newTree.m_root = binary_tree::copy(subTreeRoot);
	return newTree;
}

bool search_tree::add(int key)
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

	return true;
}

int search_tree::height_by_key(int key)
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

search_tree& search_tree::operator=(const search_tree& other)
{
	binary_tree::operator=(other);
	return *this;
}
