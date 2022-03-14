#pragma once

class binary_tree 
{
	struct node;

public:
	binary_tree() = default;

	node* getRoot();

	node* add(const int key);
	node* add(node* subTreeRoot, const int key);

	node* find_by_key(const int key);
	node* find_by_key(node* subTreeRoot, int key);
	node* find_by_index(const int index);
	node* find_by_index(node* subTreeRoot, int index);

	node* findParent_by_key(const int key);
	node* findParent_by_key(node* subTreeRoot, int key);
	node* findParent_by_index(const int index);
	node* findParent_by_index(node* subTreeRoot, int index);

	void find_and_erase_by_key(int key);
	void find_and_erase_by_key(node* subTreeRoot, int key);
	void find_and_erase_by_index(int index);
	void find_and_erase_by_index(node* subTreeRoot, int index);

	void erase(node* toDelete);

	void printHorizontal();
	void printHorizontal(node *subTreeRoot, const int level = 0);

	void printLevel(const int level);
	void printLevel(node* subTreeRoot, const int level, const int currentLevel = 0);

private:
	node* m_root = nullptr;
};

struct binary_tree::node
{
	int data;
	node* left;
	node* right;

	node()
	{
		data = 0;
		left = nullptr;
		right = nullptr;
	}

	node(int value, node* leftChild = nullptr, node* rightChild = nullptr)
	{
		data = value;
		left = leftChild;
		right = rightChild;
	}

	~node()
	{

	}
};