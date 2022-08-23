#include <fstream>
#include <vector>
#include <algorithm>
#include "huffman.h"
#include <iostream>

node::node()
{
	m_frequency = 0;
	m_left = nullptr;
	m_right = nullptr;
	m_data = set();
}

node::node(unsigned char symbol, int frequency)
{
	m_data = set(symbol);
	m_frequency = frequency;
	m_left = nullptr;
	m_right = nullptr;
}

node::node(node* left, node* right)
{
	m_frequency = left->m_frequency + right->m_frequency;
	m_data = left->m_data | right->m_data;
	m_left = left;
	m_right = right;
}

node::~node()
{
}

set node::data()
{
	return m_data;
}

int node::frequency()
{
	return m_frequency;
}

node* node::left() const
{
	return m_left;
}

node* node::right() const
{
	return m_right;
}

huffman::huffman()
{
	m_root = nullptr;
}

huffman::~huffman()
{
	_delete(m_root);
}

void huffman::build(std::string filenameIn)
{
	_delete(m_root);

	std::ifstream fin;
	fin.open(filenameIn);
	if (!fin.is_open())
	{
		return;
	}

	unsigned char symbols[256];
	for (int i = 0; i < 256; i++)
		symbols[i] = 0;

	char c;
	while (fin.get(c))
	{
		symbols[(unsigned char)c]++;
	}

	fin.close();

	std::vector<node*> nodes;

	for (int i = 0; i < 256; i++)
	{
		if (symbols[i] != 0)
		{
			node* temp = new node((unsigned char)i, symbols[i]);
			nodes.push_back(temp);
		}
	}

	std::sort(nodes.begin(), nodes.end(), 
		[](node* a, node* b) 
		{ 
			return a->frequency() < b->frequency();
		});

	while (nodes.size() > 1)
	{
		node* temp = new node(nodes[0], nodes[1]);
		nodes.erase(nodes.begin());
		nodes.erase(nodes.begin());
		nodes.push_back(temp);
		std::sort(nodes.begin(), nodes.end(),
			[](node* a, node* b)
			{
				return a->frequency() < b->frequency();
			});
	}

	m_root = nodes[0];
}

float huffman::encode(std::string filenameIn, std::string filenameOut)
{
	build(filenameIn);

	if (m_root == nullptr)
		return 0.0f;

	std::ifstream fin;
	fin.open(filenameIn);
	if (!fin.is_open())
	{
		return 0.0f;
	}

	std::ofstream fout;
	fout.open(filenameOut);
	if (!fout.is_open())
	{
		return 0.0f;
	}

	int result_count_of_bits = 0;
	int input_count_of_bits = 0;

	char c;
	while (fin.get(c))
	{
		node* temp = m_root;
		while (temp->left() != nullptr && temp->right() != nullptr)
		{
			if (temp->left()->data().inSet(c))
			{
				temp = temp->left();
				fout << '0';
			}
			else
			{
				temp = temp->right();
				fout << '1';
			}
			result_count_of_bits++;
		}
		input_count_of_bits++;
	}

	if (m_root->left() == nullptr && m_root->right() == nullptr)
	{
		for (int i = 0; i < input_count_of_bits; i++)
			fout << '1';

		result_count_of_bits = input_count_of_bits;
	}

	fin.close();
	fout.close();

	input_count_of_bits *= 8;

	return (float)result_count_of_bits / (double) input_count_of_bits;
}

bool huffman::decode(std::string filenameIn, std::string filenameOut)
{
	if (m_root == nullptr)
		return false;

	std::ifstream fin;
	fin.open(filenameIn);
	if (!fin.is_open())
	{
		return 0.0f;
	}

	std::ofstream fout;
	fout.open(filenameOut);
	if (!fout.is_open())
	{
		return 0.0f;
	}

	char c;
	node* temp = m_root;
	while (fin.get(c))
	{
		switch (c)
		{
		case '0':
			if(temp->left() != nullptr)
				temp = temp->left();
			break;
		case '1':
			if(temp->right() != nullptr)
				temp = temp->right();
			break;
		default:
			return false;
		}

		if (temp->left() == nullptr && temp->right() == nullptr)
		{
			fout << temp->data();
			temp = m_root;
		}
	}

	fin.close();
	fout.close();

	return false;
}

void huffman::_delete(node* root)
{
	if (root != nullptr)
	{
		_delete(root->left());
		_delete(root->right());
		delete root;
	}
}
