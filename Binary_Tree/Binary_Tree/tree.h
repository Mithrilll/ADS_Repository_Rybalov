#pragma once

class binary_tree 
{
	struct node;

private:
	// копирование поддерева
	node* copy(node* subTreeRoot);

	node* getFree(node* subTreeRoot);

public:
	binary_tree() = default;
	binary_tree(const binary_tree& bt);
	~binary_tree();

	// удаление поддерева
	void deleteSubTree(node* subTreeRoot);

	// получение корня
	//node* getRoot();

	bool isEmpty();

	binary_tree copySubTree(node* subTreeRoot);

	int height();
	int height(node* subTreeRoot);

	int countNodes();
	int countNodes(node* subTreeRoot);

	int max();
	int max(node* subTreeRoot);

	int min();
	int min(node* subTreeRoot);

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

	bool find_and_erase_by_key(int key);
	bool find_and_erase_by_key(node* subTreeRoot, int key);
	bool find_and_erase_by_index(int index);
	bool find_and_erase_by_index(node* subTreeRoot, int index);

	bool erase(node* toDelete);

	void printHorizontal();
	void printHorizontal(node *subTreeRoot, const int level = 0);

	// сделаю по другому, тут есть проблеммы с печатью(нельзя пойти в глубь где нет вершин поэтому на след уровне будет косяк)
	void printLevel(const int level);
	void printLevel(node* subTreeRoot, const int level, const int currentLevel = 0, bool left = true);

	// так-то лучше))
	// можно так же реализовать и это с уровнями, работать будет нормально поидее
	void printVertical();
	void printVertical(node* subTreeRoot);

	binary_tree operator=(const binary_tree& other);

private:
	node* m_root = nullptr;
};

struct binary_tree::node
{
private:
	int data;
public:
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

	int value()
	{
		return data;
	}

	int descendants()
	{
		int cnt = 0;
		if (left)
			cnt++;
		if (right)
			cnt++;

		return cnt;
	}
};