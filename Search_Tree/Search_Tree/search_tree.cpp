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

	node* temp = subTreeRoot;
	while (temp->right && temp->right->right)
	{
		temp = temp->right;
	}

	return temp;
}

binary_tree::node* search_tree::minParent(node* subTreeRoot)
{
	if (subTreeRoot == nullptr || subTreeRoot->left == nullptr)
		return nullptr;

	node* temp = subTreeRoot;
	while (temp->left && temp->left->left)
	{
		temp = temp->left;
	}

	return temp;
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

bool search_tree::erase_by_key(int key)
{
	node* to_delete = find_by_key(key);
	node* parent = findParent_by_key(m_root, key);

	if (to_delete == nullptr)
		return false;

	if (to_delete->left == nullptr && to_delete->right == nullptr)
	{
		if (parent && parent->left == to_delete)
			parent->left = nullptr;

		if (parent && parent->right == to_delete)
			parent->right = nullptr;

		if (!parent)
			m_root = nullptr;

		delete to_delete;

		return true;
	}

	if (to_delete->left == nullptr && to_delete->right != nullptr)
	{
		if (parent && parent->left == to_delete)
			parent->left = to_delete->right;

		if (parent && parent->right == to_delete)
			parent->right = to_delete->right;

		if (!parent)
			m_root = to_delete->right;

		delete to_delete;

		return true;
	}

	if (to_delete->left != nullptr && to_delete->right == nullptr)
	{
		if (parent && parent->left == to_delete)
			parent->left = to_delete->left;

		if (parent && parent->right == to_delete)
			parent->right = to_delete->left;

		if (!parent)
			m_root = to_delete->left;

		delete to_delete;

		return true;
	}

	if (to_delete->left && to_delete->right)
	{
		node* to_insert = min(to_delete->right);
		node* parent_insert = minParent(to_delete->right);

		if (parent_insert)
		{
			parent_insert->left = to_insert->right;
			to_insert->left = to_delete->left;
			to_insert->right = to_delete->right;
		}
		else
		{
			to_insert->left = to_delete->left;
			to_insert->right = nullptr;
		}

		if (parent && parent->left == to_delete)
			parent->left = to_insert;

		if (parent && parent->right == to_delete)
			parent->right = to_insert;

		if (!parent)
			m_root = to_insert;

		delete to_delete;

		return true;
	}
}

bool search_tree::erase_by_index(int index)
{
	node* to_delete = find_by_index(index);
	node* parent = findParent_by_index(m_root, index);

	if (to_delete == nullptr)
		return false;

	if (to_delete->left == nullptr && to_delete->right == nullptr)
	{
		if (parent && parent->left == to_delete)
			parent->left = nullptr;

		if (parent && parent->right == to_delete)
			parent->right = nullptr;

		if (!parent)
			m_root = nullptr;

		delete to_delete;

		return true;
	}

	if (to_delete->left == nullptr && to_delete->right != nullptr)
	{
		if (parent && parent->left == to_delete)
			parent->left = to_delete->right;

		if (parent && parent->right == to_delete)
			parent->right = to_delete->right;

		if (!parent)
			m_root = to_delete->right;

		delete to_delete;

		return true;
	}

	if (to_delete->left != nullptr && to_delete->right == nullptr)
	{
		if (parent && parent->left == to_delete)
			parent->left = to_delete->left;

		if (parent && parent->right == to_delete)
			parent->right = to_delete->left;

		if (!parent)
			m_root = to_delete->left;

		delete to_delete;

		return true;
	}

	if (to_delete->left && to_delete->right)
	{
		node* to_insert = min(to_delete->right);
		node* parent_insert = minParent(to_delete->right);

		if (parent_insert)
		{
			parent_insert->left = to_insert->right;
			to_insert->left = to_delete->left;
			to_insert->right = to_delete->right;
		}
		else
		{
			to_insert->left = to_delete->left;
			to_insert->right = nullptr;
		}

		if (parent && parent->left == to_delete)
			parent->left = to_insert;

		if (parent && parent->right == to_delete)
			parent->right = to_insert;

		if (!parent)
			m_root = to_insert;

		delete to_delete;

		return true;
	}
}

int search_tree::index_by_key(int key)
{
	node* to_find = find_by_key(key);
	
	if (m_root == nullptr || to_find == nullptr) 
		return -1;

	if (m_root == to_find)
		return 0;

	int index = 0;
	std::vector<node*> currentLevelNodes;
	currentLevelNodes.push_back(m_root);

	while (currentLevelNodes.size() != 0) {
		std::vector<node*> nextLevelNodes;
		nextLevelNodes.reserve(currentLevelNodes.size() * 2);

		for (node* node : currentLevelNodes) 
		{
			if (node->left) 
			{
				nextLevelNodes.push_back(node->left);
				++index;
				if (node->left == to_find)
					return index;
			}

			if (node->right) 
			{
				nextLevelNodes.push_back(node->right);
				++index;
				if(node->right == to_find)
					return index;
			}
		}
		currentLevelNodes.swap(nextLevelNodes);
	}

	return -1;
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

search_tree search_tree::operator=(const search_tree& other)
{
	if (&other == this)
		return *this;

	deleteSubTree(m_root);

	m_root = binary_tree::copy(other.m_root);

	return *this;
}
