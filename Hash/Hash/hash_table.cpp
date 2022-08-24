#include "hash_table.h"

hash_table::hash_table()
{
	m_size = 1;
	m_table = new table_element[1];
	m_function = &function1;
}

hash_table::hash_table(int n)
{
	m_size = n;
	m_table = new table_element[m_size];
	m_function = &function1;
}

hash_table::hash_table(const hash_table& other)
{
	m_size = other.m_size;
	m_table = new table_element[m_size];
	for (int i = 0; i < m_size; i++)
		add(other.m_table[i].key, other.m_table[i].data);
	m_function = other.m_function;
}

hash_table::~hash_table()
{
	if (m_table != nullptr)
		delete[] m_table;
	if (m_function != nullptr)
		delete m_function;
}

hash_table hash_table::operator=(const hash_table& other)
{
	if (m_table != nullptr)
		delete m_table;

	m_size = other.m_size;
	m_table = new table_element[m_size];
	for (int i = 0; i < m_size; i++)
		add(other.m_table[i].key, other.m_table[i].data);
	m_function = other.m_function;

	return *this;
}

bool hash_table::add(int _key, std::string _str)
{
	int index = (*m_function)(_key, m_size, 1);
	if (!m_table[index].hasValue)
	{
		m_table[index].key = _key;
		m_table[index].data = _str;
		m_table[index].hasValue = true;
	}
	else
	{
		int i = 0;
		while (i < m_size && m_table[i].hasValue)
			i++;

		if (i >= m_size)
			return false;

		m_table[index].next = &m_table[i];
		m_table[i].key = _key;
		m_table[i].data = _str;
		m_table[i].hasValue = true;
	}

	return true;
}

bool hash_table::erase(int _key)
{
	int index = (*m_function)(_key, m_size, 1);

	if (!m_table[index].hasValue)
	{
		return false;
	}

	table_element* temp = &m_table[index];
	while (temp && temp->key != _key && temp->hasValue)
		temp = temp->next;

	if (temp == nullptr)
		return false;
	else if(temp->hasValue && temp->key == _key)
	{
		while (temp->next != nullptr)
		{
			temp->key = temp->next->key;
			temp->data = temp->next->data;
			temp = temp->next;
		}
		temp->hasValue = false;

		return true;
	}

	return false;
}

bool hash_table::inTable(int _key)
{
	int index = (*m_function)(_key, m_size, 1);

	table_element* temp = &m_table[index];
	while (temp && temp->key != _key && temp->hasValue)
		temp = temp->next;

	if (temp == nullptr)
		return false;
	else if(temp->hasValue && temp->key == _key)
		return true;
}

void hash_table::change_function(IHashFunction* newFunction)
{
	m_function = newFunction;

	table_element* newTable = new table_element[m_size];

	for (int i = 0; i < m_size; i++)
	{
		if (m_table[i].hasValue)
		{
			int index = (*m_function)(m_table[i].key, m_size, 1);
			if (!newTable[index].hasValue)
			{
				newTable[index].key = m_table[i].key;
				newTable[index].data = m_table[i].data;
				newTable[index].hasValue = true;
			}
			else
			{
				int i = 0;
				while (i < m_size && newTable[i].hasValue)
					i++;

				newTable[index].next = &newTable[i];
				newTable[i].key = m_table[i].key;
				newTable[i].data = m_table[i].data;
				newTable[i].hasValue = true;
			}
		}
	}

	delete[] m_table;
	m_table = newTable;
}

std::ostream& operator<<(std::ostream& out, const hash_table& other)
{
	for (int i = 0; i < other.m_size; i++)
	{
		out << i << "\t" << &other.m_table[i] << "\t" << other.m_table[i].next << "\t" << other.m_table[i].key << "\t" << other.m_table[i].data << "\n";
	}

	return out;
}
