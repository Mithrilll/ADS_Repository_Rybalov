#include <random>
#include <iostream>
#include "tree.h"

binary_tree::node* binary_tree::copy(node* subTreeRoot)
{
	node* root = nullptr;
	if (subTreeRoot)
	{
		root = new node(subTreeRoot->value());
		root->left = copy(subTreeRoot->left);
		root->right = copy(subTreeRoot->right);
	}
	
	return root;
}

binary_tree::node* binary_tree::getFree(node* subTreeRoot)
{
	if (subTreeRoot == nullptr)
		throw "getFree: tree is empty";

	if (subTreeRoot->left == nullptr || subTreeRoot->right == nullptr)
		return subTreeRoot;
	else
	{
		int h1 = height(subTreeRoot->left);
		int h2 = height(subTreeRoot->right);
		if (h1 < h2)
			return getFree(subTreeRoot->left);
		else if(h1 > h2)
			return getFree(subTreeRoot->right);
		else
		{
			int c1 = countNodes(subTreeRoot->left);
			int c2 = countNodes(subTreeRoot->right);
			if(c1 < c2)
				return getFree(subTreeRoot->left);
			else
				return getFree(subTreeRoot->right);
		}
	}
}

void binary_tree::deleteSubTree(node* subTreeRoot)
{
	if (subTreeRoot)
	{
		deleteSubTree(subTreeRoot->left);
		deleteSubTree(subTreeRoot->right);
		delete subTreeRoot;
		if (subTreeRoot == m_root)
			m_root = nullptr;
	}
}

bool binary_tree::isEmpty()
{
	return m_root == nullptr;
}

binary_tree binary_tree::copySubTree(int index)
{
	node* subTreeRoot = find_by_index(index);

	binary_tree nt;
	nt.m_root = copy(subTreeRoot);

	return nt;
}

int binary_tree::height()
{
	return height(0);
}

int binary_tree::height(node* subTreeRoot)
{

	int hei = 0;
	if (subTreeRoot == nullptr)
		return hei;

	std::vector<node*> currentLevelNodes;
	currentLevelNodes.push_back(subTreeRoot);

	while (currentLevelNodes.size() != 0) 
	{
		hei++;
		std::vector<node*> nextLevelNodes;
		nextLevelNodes.reserve(currentLevelNodes.size() * 2);

		for (node* node : currentLevelNodes) 
		{
			if (node->left) 
			{
				nextLevelNodes.push_back(node->left);
			}

			if (node->right) {
				nextLevelNodes.push_back(node->right);
			}
		}

		currentLevelNodes.swap(nextLevelNodes);
	}

	return hei;
}

int binary_tree::height(int index)
{
	node* subTreeRoot = find_by_index(index);

	int hei = 0;
	if (subTreeRoot == nullptr)
		return hei;

	std::vector<node*> currentLevelNodes;
	currentLevelNodes.push_back(subTreeRoot);

	while (currentLevelNodes.size() != 0)
	{
		hei++;
		std::vector<node*> nextLevelNodes;
		nextLevelNodes.reserve(currentLevelNodes.size() * 2);

		for (node* node : currentLevelNodes)
		{
			if (node->left)
			{
				nextLevelNodes.push_back(node->left);
			}

			if (node->right) {
				nextLevelNodes.push_back(node->right);
			}
		}

		currentLevelNodes.swap(nextLevelNodes);
	}

	return hei;
}

int binary_tree::countNodes()
{
	return countNodes(m_root);
}

int binary_tree::countNodesSubTree(int index)
{
	node* subTreeRoot = find_by_index(index);
	return countNodes(subTreeRoot);
}

int binary_tree::countNodes(node* subTreeRoot)
{
	int cnt = 0;
	if (subTreeRoot)
	{
		cnt++;
		cnt += countNodes(subTreeRoot->left);
		cnt += countNodes(subTreeRoot->right);
	}

	return cnt;
}

int binary_tree::max()
{
	return max(m_root)->value();
}

int binary_tree::maxSubTree(int index)
{
	node* subTreeRoot = find_by_index(index);
	return max(subTreeRoot)->value();
}

binary_tree::node* binary_tree::max(node* subTreeRoot)
{
	if (subTreeRoot == nullptr)
		throw "max: subtree is empty";

	node* m = subTreeRoot;
	if (subTreeRoot->left)
	{
		node* m1 = max(subTreeRoot->left);
		if (m->value() < m1->value())
			m = m1;
	}

	if (subTreeRoot->right)
	{
		node* m1 = max(subTreeRoot->right);
		if (m->value() < m1->value())
			m = m1;
	}
		
	return m;
}

int binary_tree::min()
{
	return min(m_root)->value();
}

int binary_tree::minSubTree(int index)
{
	node* subTreeRoot = find_by_index(index);
	return min(subTreeRoot)->value();
}

binary_tree::node* binary_tree::min(node* subTreeRoot)
{
	if (subTreeRoot == nullptr)
		throw "min: subtree is empty";

	node* m = subTreeRoot;
	if (subTreeRoot->left)
	{
		node* m1 = min(subTreeRoot->left);
		if (m->value() > m1->value())
			m = m1;
	}

	if (subTreeRoot->right)
	{
		node* m1 = min(subTreeRoot->right);
		if (m->value() > m1->value())
			m = m1;
	}

	return m;
}

binary_tree::binary_tree(const binary_tree& bt)
{
	m_root = copy(bt.m_root);
}

binary_tree::~binary_tree()
{
	deleteSubTree(m_root);
}

void binary_tree::deleteTree()
{
	deleteSubTree(m_root);
}

void binary_tree::deleteSubTree(int index)
{
	node* subTreeRoot = find_by_index(index);
	deleteSubTree(subTreeRoot);
}

//binary_tree::node* binary_tree::getRoot()
//{
//    return m_root;
//}

bool binary_tree::add(const int key)
{
    return add(m_root, key) != nullptr;
}

int binary_tree::index_by_key(int key)
{
	return index_by_key(m_root, key);
}

int binary_tree::index_by_keySubTree(int index, int key)
{
	node* subTreeRoot = find_by_index(index);

	return index_by_key(subTreeRoot, key);
}

int binary_tree::index_by_key(node* subTreeRoot, int key)
{
	node* Node = find_by_key(key);
	int index = 0;

	if (Node == nullptr)
		return -1;

	if (Node == subTreeRoot)
		return index;

	std::vector<node*> currentLevelNodes;
	currentLevelNodes.push_back(subTreeRoot);

	while (currentLevelNodes.size() != 0)
	{
		std::vector<node*> nextLevelNodes;
		nextLevelNodes.reserve(currentLevelNodes.size() * 2);

		for (node* node : currentLevelNodes)
		{
			if (node->left)
			{
				index++;

				if (node->left == Node)
					return index;

				nextLevelNodes.push_back(node->left);
			}

			if (node->right)
			{
				index++;

				if (node->right == Node)
					return index;

				nextLevelNodes.push_back(node->right);
			}
		}

		currentLevelNodes.swap(nextLevelNodes);
	}

	return -1;
}

int binary_tree::key_by_index(int index)
{
	return key_by_index(m_root, index);
}

int binary_tree::key_by_indexSubTree(int indexsubtree, int index)
{
	node* subTreeRoot = find_by_index(indexsubtree);

	return key_by_index(subTreeRoot, index);
}

int binary_tree::key_by_index(node* subTreeRoot, int index)
{
	if (index == 0) {
		return subTreeRoot->value();
	}
	else if (subTreeRoot == nullptr) {
		return -1;
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
		return -1;
	}
	else {
		return currentLevelNodes[index]->value();
	}
}

int binary_tree::indexParent_by_key(int key)
{
	return indexParent_by_key(m_root, key);
}

int binary_tree::indexParent_by_keySubTree(int index, int key)
{
	node* subTreeRoot = find_by_index(index);

	return indexParent_by_key(subTreeRoot, key);
}

int binary_tree::indexParent_by_key(node* subTreeRoot, int key)
{
	node* Node = findParent_by_key(key);
	int index = 0;

	if (Node == nullptr)
		return -1;

	if (Node == m_root)
		return index;

	std::vector<node*> currentLevelNodes;
	currentLevelNodes.push_back(m_root);

	while (currentLevelNodes.size() != 0)
	{
		std::vector<node*> nextLevelNodes;
		nextLevelNodes.reserve(currentLevelNodes.size() * 2);

		for (node* node : currentLevelNodes)
		{
			if (node->left)
			{
				index++;

				if (node->left == Node)
					return index;

				nextLevelNodes.push_back(node->left);
			}

			if (node->right)
			{
				index++;

				if (node->right == Node)
					return index;

				nextLevelNodes.push_back(node->right);
			}
		}

		currentLevelNodes.swap(nextLevelNodes);
	}

	return -1;
}

int binary_tree::keyParent_by_index(int index)
{
	return keyParent_by_index(m_root, index);
}

int binary_tree::keyParent_by_indexSubTree(int indexsubtree, int index)
{
	node* subTreeRoot = find_by_index(indexsubtree);

	return keyParent_by_index(subTreeRoot, index);
}

int binary_tree::keyParent_by_index(node* subTreeRoot, int index)
{
	if (index == 0) {
		return -1;
	}
	else if (subTreeRoot == nullptr) {
		return -1;
	}

	std::vector<node*> prevLevelNodes;
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
		prevLevelNodes = currentLevelNodes;
		currentLevelNodes.swap(nextLevelNodes);
	}

	if (currentLevelNodes.size() == 0) {
		return -1;
	}
	else {
		for (node* i : prevLevelNodes)
			if (i->left == currentLevelNodes[index] || i->right == currentLevelNodes[index])
				return i->value();
		return -1;
	}
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
		if (subTreeRoot->value() == key)
			return subTreeRoot;
		else
		{
			node* left = find_by_key(subTreeRoot->left, key);
			node* right = find_by_key(subTreeRoot->right, key);
			if (left && left->value() == key)
				return left;

			if (right && right->value() == key)
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
	if (m_root && (m_root->value() == key))
		return nullptr;

	if (subTreeRoot)
	{
		if (subTreeRoot->left || subTreeRoot->right)
		{
			if ((subTreeRoot->left && subTreeRoot->left->value() == key) || (subTreeRoot->right && subTreeRoot->right->value() == key))
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
	if (index == 0) {
		return nullptr;
	}
	else if (subTreeRoot == nullptr) {
		return nullptr;
	}

	std::vector<node*> prevLevelNodes;
	std::vector<node*> currentLevelNodes;
	currentLevelNodes.push_back(subTreeRoot);


	while (currentLevelNodes.size() != 0 && index >= currentLevelNodes.size()) 
	{
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
		prevLevelNodes = currentLevelNodes;
		currentLevelNodes.swap(nextLevelNodes);
	}

	if (currentLevelNodes.size() == 0) {
		return nullptr;
	}
	else {
		for (node* i : prevLevelNodes)
			if (i->left == currentLevelNodes[index] || i->right == currentLevelNodes[index])
				return i;
		return nullptr;
	}
}

bool binary_tree::find_and_erase_by_key(int key)
{
	return find_and_erase_by_key(m_root, key);
}

bool binary_tree::find_and_erase_by_keySubTree(int index, int key)
{
	node* subTreeRoot = find_by_index(index);

	return find_and_erase_by_key(subTreeRoot, key);
}

bool binary_tree::find_and_erase_by_key(node* subTreeRoot, int key)
{
	node* to_delete = find_by_key(subTreeRoot, key);
	node* parent = findParent_by_key(subTreeRoot, key);
	return erase(to_delete, parent);
}

bool binary_tree::find_and_erase_by_index(int index)
{
	return find_and_erase_by_index(m_root, index);
}

bool binary_tree::find_and_erase_by_indexSubTree(int indexsubtree, int index)
{
	node* subTreeRoot = find_by_index(indexsubtree);

	return find_and_erase_by_index(subTreeRoot, index);
}

bool binary_tree::find_and_erase_by_index(node* subTreeRoot, int index)
{
	node* to_delete = find_by_index(subTreeRoot, index);
	node* parent = findParent_by_index(subTreeRoot, index);
	return erase(to_delete, parent);
}

bool binary_tree::erase(node* toDelete, node* parent)
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
		if (parent)
		{
			if (parent->left == toDelete)
			{
				parent->left = toDelete->left;
				node* toAdd = getFree(parent);
				if (toAdd->right == nullptr)
					toAdd->right = toDelete->right;
				else
					toAdd->left = toDelete->right;
			}

			if (parent->right == toDelete)
			{
				parent->right = toDelete->right;
				node* toAdd = getFree(parent);
				if (toAdd->left == nullptr)
					toAdd->left = toDelete->left;
				else
					toAdd->right = toDelete->left;
			}
		}
		else
		{
			m_root = toDelete->left;
			node* toAdd = getFree(m_root);
			if (toAdd->right == nullptr)
				toAdd->right = toDelete->right;
			else
				toAdd->left = toDelete->right;
		}

		delete toDelete;

		return true;
	}
}

void binary_tree::printHorizontal()
{
	printHorizontal(m_root);
}

void binary_tree::printHorizontalSubTree(int index, const int level)
{
	node* subTreeRoot = find_by_index(index);
	printHorizontal(subTreeRoot);
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
	cout << subTreeRoot->value() << endl;

	printHorizontal(subTreeRoot->left, level + 1);
}

void binary_tree::printLevel(const int level)
{
	printLevel(m_root, level, 0, true);
}

void binary_tree::printLevelSubTree(int index, const int level, const int currentLevel, bool left)
{
	node* subTreeRoot = find_by_index(index);
	printLevel(subTreeRoot, level, 0, true);
}

void binary_tree::printLevel(node* subTreeRoot, const int level, const int currentLevel, bool left)
{
	using std::cout;
	using std::endl;
	int h = height(m_root);

	if (subTreeRoot == nullptr) {
		if (subTreeRoot == m_root) {
			cout << "Tree is empty" << endl;
		}
		for (int i = 0; i < pow(2, (h - level-1)); i++)
			cout << " ";
		if(!left)
			for(int i =0; i < pow(2, (h - level - 1))-1; i++)
				cout << " ";
		cout << "X";
		return;
	}

	if (currentLevel == level) {
		for (int i = 0; i < pow(2, (h - level-1)); i++)
			cout << " ";
		if (!left)
			for (int i = 0; i < pow(2, (h - level - 1)) - 1; i++)
				cout << " ";
		cout << subTreeRoot->value();
	}
	else if (currentLevel < level) {
		if (left)
		{
			printLevel(subTreeRoot->left, level, currentLevel + 1, true);
			printLevel(subTreeRoot->right, level, currentLevel + 1, false);
		}
		else
		{
			printLevel(subTreeRoot->left, level, currentLevel + 1, false);
			printLevel(subTreeRoot->right, level, currentLevel + 1, false);
		}
	}
}

bool binary_tree::isBalanced()
{
	return isBalanced(m_root);
}

bool binary_tree::isBalancedSubTree(int index)
{
	node* subTreeRoot = find_by_index(index);
	return isBalanced(subTreeRoot);
}

bool binary_tree::isBalanced(node* subTreeRoot)
{
	if (subTreeRoot == nullptr)
		return true;

	if (abs(height(subTreeRoot->left) - height(subTreeRoot->right)) <= 1 && isBalanced(subTreeRoot->left) && isBalanced(subTreeRoot->right))
		return true;
	else
		return false;
}

int binary_tree::sum()
{
	return sum(m_root);
}

int binary_tree::sumSubTree(int index)
{
	node* subTreeRoot = find_by_index(index);
	return sum(subTreeRoot);
}

int binary_tree::sum(node* subTreeRoot)
{
	if (subTreeRoot == nullptr) {
		return 0;
	}

	int summa = 0;
	std::vector<node*> currentLevelNodes;
	currentLevelNodes.push_back(subTreeRoot);
	summa += subTreeRoot->value();

	while (currentLevelNodes.size() != 0) 
	{
		std::vector<node*> nextLevelNodes;
		nextLevelNodes.reserve(currentLevelNodes.size() * 2);

		for (node* node : currentLevelNodes) {
			if (node->left) {
				nextLevelNodes.push_back(node->left);
				summa += node->left->value();
			}

			if (node->right) {
				nextLevelNodes.push_back(node->right);
				summa += node->right->value();
			}
		}

		currentLevelNodes.swap(nextLevelNodes);
	}

	return summa;
}

int binary_tree::level(int key)
{
	return level(m_root, key);
}

int binary_tree::levelSubTree(int index, int key)
{
	node* subTreeRoot = find_by_index(index);
	return level(subTreeRoot, key);
}

int binary_tree::level(node* subTreeRoot, int key)
{
	if (subTreeRoot == nullptr) {
		return -1;
	}

	if (subTreeRoot->value() == key)
		return 0;

	int h = height(subTreeRoot);
	std::vector<node*> currentLevelNodes;
	currentLevelNodes.push_back(subTreeRoot);

	for (int i = 0; i < h; i++)
	{
		std::vector<node*> nextLevelNodes;
		nextLevelNodes.reserve(currentLevelNodes.size() * 2);

		for (node* node : currentLevelNodes) {
			if (node->left) {
				nextLevelNodes.push_back(node->left);
				if (node->left->value() == key)
					return i + 1;
			}

			if (node->right) {
				nextLevelNodes.push_back(node->right);
				if (node->right->value() == key)
					return i + 1;
			}
		}

		currentLevelNodes.swap(nextLevelNodes);
	}
	
	return -1;
}

std::vector<int> binary_tree::round()
{
	return round(m_root);
}

std::vector<int> binary_tree::roundSubTree(int index)
{
	node* subTreeRoot = find_by_index(index);
	return round(subTreeRoot);
}

std::vector<int> binary_tree::round(node* subTreeRoot)
{
	if (subTreeRoot == nullptr)
		return std::vector<int>();

	std::vector<int> keys;
	std::vector<node*> currentLevelNodes;
	currentLevelNodes.push_back(subTreeRoot);
	keys.push_back(subTreeRoot->value());

	while (currentLevelNodes.size() != 0) 
	{
		std::vector<node*> nextLevelNodes;
		nextLevelNodes.reserve(currentLevelNodes.size() * 2);

		for (node* node : currentLevelNodes) {
			if (node->left) {
				nextLevelNodes.push_back(node->left);
				keys.push_back(node->left->value());
			}

			if (node->right) {
				nextLevelNodes.push_back(node->right);
				keys.push_back(node->right->value());
			}
		}

		currentLevelNodes.swap(nextLevelNodes);
	}

	return keys;
}

void binary_tree::printVertical()
{
	printVertical(m_root);
}

void binary_tree::printVerticalSubTree(int index)
{
	node* subTreeRoot = find_by_index(index);
	printVertical(subTreeRoot);
}

void binary_tree::printVertical(node* subTreeRoot)
{
	if (subTreeRoot == nullptr)
	{
		std::cout << "Tree is empty" << std::endl;
		return;
	}

	std::vector<node*> currentLevelNodes;
	currentLevelNodes.push_back(subTreeRoot);
	int significant = 1;
	int level = 1;
	int h = height(subTreeRoot);

	while (significant != 0) 
	{
		for (int i = 0; i < currentLevelNodes.size(); i++)
		{
			if (i == 0)
				for (int j = 0; j < pow(2, h - level); j++)
					std::cout << " ";
			else
				for (int j = 0; j < pow(2, h - level) + pow(2, h - level) - 1; j++)
					std::cout << " ";

			if (currentLevelNodes[i])
				std::cout << currentLevelNodes[i]->value();
			else
				std::cout << "X";
		}
		std::cout << std::endl;

		significant = 0;
		std::vector<node*> nextLevelNodes;
		nextLevelNodes.reserve(currentLevelNodes.size() * 2);

		for (node* node : currentLevelNodes) {
			if (node)
			{
				if (node->left)
					significant++;
				if (node->right)
					significant++;

				nextLevelNodes.push_back(node->left);
				nextLevelNodes.push_back(node->right);
			}
			else
			{
				nextLevelNodes.push_back(nullptr);
				nextLevelNodes.push_back(nullptr);
			}
		}

		currentLevelNodes.swap(nextLevelNodes);
		level++;
	}
}

void binary_tree::printLeafs()
{
	printLeafs(m_root);
}

void binary_tree::printLeafsSubTree(int index)
{
	node* subTreeRoot = find_by_index(index);
	printLeafs(subTreeRoot);
}

void binary_tree::printLeafs(node* subTreeRoot)
{
	if (subTreeRoot == nullptr)
		return;
	if (subTreeRoot->left == nullptr && subTreeRoot->right == nullptr)
		std::cout << subTreeRoot->value() << " ";
	else
	{
		printLeafs(subTreeRoot->left);
		printLeafs(subTreeRoot->right);
	}
}

binary_tree binary_tree::operator=(const binary_tree& other)
{
	if (&other == this)
		return *this;

	deleteSubTree(m_root);

	m_root = copy(other.m_root);

	return *this;
}
