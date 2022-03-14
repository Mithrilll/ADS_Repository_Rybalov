#include <random>
#include <iostream>
#include "tree.h"

binary_tree::node* binary_tree::getRoot()
{
    return m_root;
}

binary_tree::node* binary_tree::add(const int key)
{
    return add(m_root, key);
}

binary_tree::node* binary_tree::add(node* subTreeRoot, const int key)
{
	if (subTreeRoot == nullptr) {
		if (m_root == nullptr) {
			m_root = new node(key);
			return m_root;
		}
		else {
			return nullptr;
		}
	}

	if (subTreeRoot->left == nullptr) {
		subTreeRoot->left = new node(key);
		return subTreeRoot->left;
	}
	else if (subTreeRoot->right == nullptr) {
		subTreeRoot->right = new node(key);
		return subTreeRoot->right;
	}
	else {
		if (rand() % 2) {
			return add(subTreeRoot->left, key);
		}
		else {
			return add(subTreeRoot->right, key);
		}
	}
}

binary_tree::node* binary_tree::find_by_key(int key)
{
    return find_by_key(m_root, key);
}

binary_tree::node* binary_tree::find_by_key(node* subTreeRoot, int key)
{
	if (subTreeRoot)
	{
		if (subTreeRoot->data == key)
			return subTreeRoot;
		else
		{
			node* left = find_by_key(subTreeRoot->left, key);
			node* right = find_by_key(subTreeRoot->right, key);
			if (left && left->data == key)
				return left;

			if (right && right->data == key)
				return right;

			return nullptr;
		}
	}

	return nullptr;
}

binary_tree::node* binary_tree::find_by_index(int index)
{
    return find_by_index(m_root, index);
}

binary_tree::node* binary_tree::find_by_index(node* subTreeRoot, int index)
{
	if (index == 0) {
		return subTreeRoot;
	}
	else if (subTreeRoot == nullptr) {
		return nullptr;
	}

	std::vector<node*> currentLevelNodes;
	currentLevelNodes.push_back(subTreeRoot);

	while (currentLevelNodes.size() != 0 && index >= currentLevelNodes.size()) {
		std::vector<node*> nextLevelNodes;
		nextLevelNodes.reserve(currentLevelNodes.size() * 2);

		for (node* node : currentLevelNodes) {
			if (node->left) {
				nextLevelNodes.push_back(node->left);
			}

			if (node->right) {
				nextLevelNodes.push_back(node->right);
			}
		}

		index -= currentLevelNodes.size();
		currentLevelNodes.swap(nextLevelNodes);
	}

	if (currentLevelNodes.size() == 0) {
		return nullptr;
	}
	else {
		return currentLevelNodes[index];
	}
}

binary_tree::node* binary_tree::findParent_by_key(int key)
{
    return findParent_by_key(m_root, key);
}

binary_tree::node* binary_tree::findParent_by_key(node* subTreeRoot, int key)
{
	if (subTreeRoot)
	{
		if (subTreeRoot->left && subTreeRoot->right)
		{
			if (subTreeRoot->left->data == key || subTreeRoot->right->data == key)
				return subTreeRoot;
			else
			{

				node* left = findParent_by_key(subTreeRoot->left, key);
				node* right = findParent_by_key(subTreeRoot->right, key);
				if (left)
					return left;

				if (right)
					return right;
			}
		}
	}

	return nullptr;
}

binary_tree::node* binary_tree::findParent_by_index(int index)
{
    return findParent_by_index(m_root, index);
}

binary_tree::node* binary_tree::findParent_by_index(node* subTreeRoot, int index)
{
	//TO DO
	return nullptr;
}

void binary_tree::find_and_erase_by_key(int key)
{
	find_and_erase_by_key(m_root, key);
}

void binary_tree::find_and_erase_by_key(node* subTreeRoot, int key)
{
	node* to_delete = find_by_key(subTreeRoot, key);
	erase(to_delete);
}

void binary_tree::find_and_erase_by_index(int index)
{
	find_and_erase_by_index(m_root, index);
}

void binary_tree::find_and_erase_by_index(node* subTreeRoot, int index)
{
	node* to_delete = find_by_index(subTreeRoot, index);
	erase(to_delete);
}

void binary_tree::erase(node* toDelete)
{

}

void binary_tree::printHorizontal()
{
	printHorizontal(m_root);
}

void binary_tree::printHorizontal(node* subTreeRoot, const int level)
{
	using std::cout;
	using std::endl;

	if (subTreeRoot == nullptr) {
		if (subTreeRoot == m_root) {
			cout << "Tree is empty" << endl;
		}
		return;
	}

	printHorizontal(subTreeRoot->right, level + 1);

	for (int i = 0; i < level; i++)
		cout << "   ";
	cout << subTreeRoot->data << endl;

	printHorizontal(subTreeRoot->left, level + 1);
}

void binary_tree::printLevel(const int level)
{
	printLevel(m_root, level, 0);
}

void binary_tree::printLevel(node* subTreeRoot, const int level, const int currentLevel)
{
	using std::cout;
	using std::endl;

	if (subTreeRoot == nullptr) {
		if (subTreeRoot == m_root) {
			cout << "Tree is empty" << endl;
		}
		return;
	}

	if (currentLevel == level) {
		cout << subTreeRoot->data << "   ";
	}
	else if (currentLevel < level) {
		printLevel(subTreeRoot->left, level, currentLevel + 1);
		printLevel(subTreeRoot->right, level, currentLevel + 1);
	}
}
