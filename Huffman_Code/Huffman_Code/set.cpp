#include "set.h"

set::set()
{
	for (int i = 0; i < m_arr_size; i++)
		m_arr[i] = (char)0;
}

set::set(unsigned char symbol)
{
	for (int i = 0; i < m_arr_size; i++)
		m_arr[i] = (unsigned char)0;

	int index = (int)symbol / 8;
	int bit = (int)symbol % 8;
	m_arr[index] |= 1 << (7 - bit);
}

set::set(const set& other)
{
	for (int i = 0; i < m_arr_size; i++)
		m_arr[i] = other.m_arr[i];
}

set::~set()
{
}

set set::operator=(const set& other)
{
	if (this == &other)
		return *this;

	for (int i = 0; i < m_arr_size; i++)
		m_arr[i] = other.m_arr[i];

	return *this;
}

set set::operator|(const set& other)
{
	set ans(*this);
	ans |= other;
	return ans;
}

set set::operator|=(const set& other)
{
	for (int i = 0; i < m_arr_size; i++)
		m_arr[i] |= other.m_arr[i];

	return *this;
}

bool set::inSet(unsigned char symbol)
{
	int index = (int)symbol / 8;
	int bit = (int)symbol % 8;

	return (m_arr[index] & (1 << (7 - bit))) != 0;
}

void set::add(unsigned char symbol)
{
	if (!inSet(symbol))
	{
		int index = (int)symbol / 8;
		int bit = (int)symbol % 8;
		m_arr[index] |= 1 << (7 - bit);
	}
}
