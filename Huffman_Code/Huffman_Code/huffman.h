#pragma once
#include <string>
#include "set.h"

class node
{
public:
	node();
	node(unsigned char symbol, int frequency);
	node(node* left, node* right);
	~node();

	set data();
	int frequency();

	node* left() const;
	node* right() const;

private:
	set m_data;
	int m_frequency;

	node* m_left;
	node* m_right;
};

class huffman
{
public:
	huffman();
	~huffman();

	void build(std::string filenameIn);
	float encode(std::string filenameIn, std::string filenameOut);
	bool decode(std::string filenameIn, std::string filenameOut);

private:
	node* m_root;

	void _delete(node* root);
};