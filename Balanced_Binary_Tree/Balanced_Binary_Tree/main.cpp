#include <iostream>
#include <random>
#include <ctime>
#include "balanced_search_tree.h"

int testBalancedSearchTree(balanced_search_tree& tree, const int size)
{
	if (tree.countNodes() != size) 
	{
		std::cout << "Wrong size!" << std::endl;
		return -1;
	}

	std::vector<int> nodesKeys = tree.round();

	for (int i = size - 1; i >= 0; --i) 
	{
		binary_tree subTree = tree.copySubTree(i);
		int subTreeSize = subTree.countNodes();
		if (subTreeSize > 1) 
		{
			int rootKey = subTree.key_by_index(0);
			int rootLevel = subTree.level(rootKey);

			int firstChildKey = subTree.key_by_index(1);
			int childsLevel = subTree.level(firstChildKey);

			int secondChildKey = -1;
			if (subTreeSize > 2) 
			{
				secondChildKey = subTree.key_by_index(2);
				if (subTree.level(secondChildKey) != childsLevel) 
				{
					secondChildKey = -1;
				}
			}

			if (secondChildKey >= 0 && !(firstChildKey <= rootKey && rootKey <= secondChildKey)) 
			{
				std::cout << "Not search tree!" << std::endl;
				std::cout << std::endl;

				return -2;
			}

			if (!subTree.isBalanced()) 
			{
				std::cout << "Not balanced!" << std::endl;
				std::cout << std::endl;

				return -3;
			}
		}
	}

	std::cout << "Test passed!" << std::endl;
	return 0;
}

int testBalancedSearchTree(int size)
{
	int failedCase = 0;
	balanced_search_tree balancedTree;
	std::vector<int> nodesKeys;

	for (int i = 0; i < size; ++i) 
	{
		int key = rand() % 10;
		balancedTree.add(key);
		nodesKeys.push_back(key);
	}
	
	int index, key;

	while (nodesKeys.size()) 
	{
		/*index = rand() % nodesKeys.size();
		nodesKeys.erase(nodesKeys.begin() + index);
		std::cout << "index: " << index << std::endl;
		balancedTree.printVertical();
		if (!balancedTree.find_and_erase_by_index(index)) 
		{
			failedCase = 1;
			break;
		}

		if (testBalancedSearchTree(balancedTree, nodesKeys.size())) 
		{
			failedCase = 2;
			break;
		}*/

		if (nodesKeys.size()) 
		{
			index = rand() % nodesKeys.size();
			key = nodesKeys[index];
			nodesKeys.erase(nodesKeys.begin() + index);
			std::cout << "key: " << key << std::endl;
			balancedTree.printVertical();
			if (!balancedTree.find_and_erase_by_key(key)) 
			{
				failedCase = 3;
				break;
			}

			if (testBalancedSearchTree(balancedTree, nodesKeys.size())) 
			{
				failedCase = 4;
				break;
			}
		}
	}

	if (failedCase || !balancedTree.isEmpty()) 
	{
		if (!failedCase) 
		{
			failedCase = -1;
		}

		std::cout << size << " " << balancedTree.countNodes() << std::endl;
		balancedTree.printVertical();
		std::cout << std::endl;
		std::cout << std::endl;
	}

	return failedCase;
}

int testBalancedAsSearchTree(search_tree& tree, const int size)
{
	if (tree.countNodes() != size)
	{
		std::cout << "Wrong size!" << std::endl;
		return -1;
	}

	std::vector<int> nodesKeys = tree.round();

	for (int i = size - 1; i >= 0; --i)
	{
		binary_tree subTree = tree.copySubTree(i);
		int subTreeSize = subTree.countNodes();
		if (subTreeSize > 1)
		{
			int rootKey = subTree.key_by_index(0);
			int rootLevel = subTree.level(rootKey);

			int firstChildKey = subTree.key_by_index(1);
			int childsLevel = subTree.level(firstChildKey);

			int secondChildKey = -1;
			if (subTreeSize > 2)
			{
				secondChildKey = subTree.key_by_index(2);
				if (subTree.level(secondChildKey) != childsLevel)
				{
					secondChildKey = -1;
				}
			}

			if (secondChildKey >= 0 && !(firstChildKey <= rootKey && rootKey <= secondChildKey))
			{
				std::cout << "Not search tree!" << std::endl;
				std::cout << std::endl;

				return -2;
			}

			if (!subTree.isBalanced())
			{
				std::cout << "Not balanced!" << std::endl;
				std::cout << std::endl;

				return -3;
			}
		}
	}

	std::cout << "Test passed!" << std::endl;
	return 0;
}

bool testBalancedAsSearchTree(int size)
{
	int failedCase = 0;
	balanced_search_tree balancedTree;
	search_tree& balancedTreeRef = balancedTree;
	std::vector<int> nodesKeys;

	for (int i = 0; i < size; ++i)
	{
		int key = rand() % 10;
		balancedTreeRef.add(key);
		nodesKeys.push_back(key);
	}

	int index, key;

	while (nodesKeys.size())
	{
		/*index = rand() % nodesKeys.size();
		nodesKeys.erase(nodesKeys.begin() + index);
		std::cout << "index: " << index << std::endl;
		balancedTree.printVertical();
		if (!balancedTree.find_and_erase_by_index(index))
		{
			failedCase = 1;
			break;
		}

		if (testBalancedSearchTree(balancedTree, nodesKeys.size()))
		{
			failedCase = 2;
			break;
		}*/

		if (nodesKeys.size())
		{
			index = rand() % nodesKeys.size();
			key = nodesKeys[index];
			nodesKeys.erase(nodesKeys.begin() + index);
			std::cout << "key: " << key << std::endl;
			balancedTreeRef.printVertical();
			if (!balancedTreeRef.find_and_erase_by_key(key))
			{
				failedCase = 3;
				break;
			}

			if (testBalancedAsSearchTree(balancedTreeRef, nodesKeys.size()))
			{
				failedCase = 4;
				break;
			}
		}
	}

	if (failedCase || !balancedTree.isEmpty())
	{
		if (!failedCase)
		{
			failedCase = -1;
		}

		std::cout << size << " " << balancedTree.countNodes() << std::endl;
		balancedTree.printVertical();
		std::cout << std::endl;
		std::cout << std::endl;
	}

	return failedCase;
}

int testBalancedAsBinaryTree(binary_tree& tree, const int size)
{
	if (tree.countNodes() != size)
	{
		std::cout << "Wrong size!" << std::endl;
		return -1;
	}

	std::vector<int> nodesKeys = tree.round();

	for (int i = size - 1; i >= 0; --i)
	{
		binary_tree subTree = tree.copySubTree(i);
		int subTreeSize = subTree.countNodes();
		if (subTreeSize > 1)
		{
			int rootKey = subTree.key_by_index(0);
			int rootLevel = subTree.level(rootKey);

			int firstChildKey = subTree.key_by_index(1);
			int childsLevel = subTree.level(firstChildKey);

			int secondChildKey = -1;
			if (subTreeSize > 2)
			{
				secondChildKey = subTree.key_by_index(2);
				if (subTree.level(secondChildKey) != childsLevel)
				{
					secondChildKey = -1;
				}
			}

			if (secondChildKey >= 0 && !(firstChildKey <= rootKey && rootKey <= secondChildKey))
			{
				std::cout << "Not search tree!" << std::endl;
				std::cout << std::endl;

				return -2;
			}

			if (!subTree.isBalanced())
			{
				std::cout << "Not balanced!" << std::endl;
				std::cout << std::endl;

				return -3;
			}
		}
	}

	std::cout << "Test passed!" << std::endl;
	return 0;
}

bool testBalancedAsBinaryTree(int size)
{
	int failedCase = 0;
	balanced_search_tree balancedTree;
	binary_tree& balancedTreeRef = balancedTree;
	std::vector<int> nodesKeys;

	for (int i = 0; i < size; ++i)
	{
		int key = rand() % 10;
		balancedTreeRef.add(key);
		nodesKeys.push_back(key);
	}

	int index, key;

	while (nodesKeys.size())
	{
		/*index = rand() % nodesKeys.size();
		nodesKeys.erase(nodesKeys.begin() + index);
		std::cout << "index: " << index << std::endl;
		balancedTree.printVertical();
		if (!balancedTree.find_and_erase_by_index(index))
		{
			failedCase = 1;
			break;
		}

		if (testBalancedSearchTree(balancedTree, nodesKeys.size()))
		{
			failedCase = 2;
			break;
		}*/

		if (nodesKeys.size())
		{
			index = rand() % nodesKeys.size();
			key = nodesKeys[index];
			nodesKeys.erase(nodesKeys.begin() + index);
			std::cout << "key: " << key << std::endl;
			balancedTreeRef.printVertical();
			if (!balancedTreeRef.find_and_erase_by_key(key))
			{
				failedCase = 3;
				break;
			}

			if (testBalancedAsBinaryTree(balancedTreeRef, nodesKeys.size()))
			{
				failedCase = 4;
				break;
			}
		}
	}

	if (failedCase || !balancedTree.isEmpty())
	{
		if (!failedCase)
		{
			failedCase = -1;
		}

		std::cout << size << " " << balancedTree.countNodes() << std::endl;
		balancedTree.printVertical();
		std::cout << std::endl;
		std::cout << std::endl;
	}

	return failedCase;
}

int main()
{
	srand(time(0));

	std::cout << "----BALANCED_SEARCH_TREE----" << std::endl;
	if (testBalancedSearchTree(30) == 0)
	{
		std::cout << "SUCCESS!" << std::endl;
	}
	else
		std::cout << "OOPS HAVE SOME ERRORS!" << std::endl;
	
	std::cout << "\n\n\n----AS_SEARCH_TREE----" << std::endl;
	if (testBalancedAsSearchTree(30) == 0)
	{
		std::cout << "SUCCESS!" << std::endl;
	}
	else
		std::cout << "OOPS HAVE SOME ERRORS!" << std::endl;
	
	std::cout << "\n\n\n----AS_BINARY_TREE----" << std::endl;
	if (testBalancedAsBinaryTree(30) == 0)
	{
		std::cout << "SUCCESS!" << std::endl;
	}
	else
		std::cout << "OOPS HAVE SOME ERRORS!" << std::endl;

	return 0;
}