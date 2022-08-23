#pragma once
#include <iostream>

class set
{
public:
	set();
	set(unsigned char symbol);
	set(const set& other);
	~set();

	set operator=(const set& other);
	set operator|(const set& other);
	set operator|=(const set& other);

	bool inSet(unsigned char symbol);

	void add(unsigned char symbol);

	friend std::ostream& operator<<(std::ostream& out, const set& other)
	{
		for (int i = 0; i < 256; i++)
		{
			int index = i / 8;
			int bit = i % 8;
			if ((other.m_arr[index] & (1 << (7 - bit))) != 0)
				out << (unsigned char)i;
		}

		return out;
	}

private:
	const int m_arr_size = 32;
	char m_arr[32];
};