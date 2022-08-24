#include <iostream>
#include "hash_table.h"

int main()
{
	hash_table table(5);

	table.add(101, "hello");
	table.add(32, "world");
	table.add(12, "mir");
	table.add(15, "privet");
	table.add(13, "test");

	std::cout << table;

	table.erase(32);
	std::cout << "--------\n";

	std::cout << table;

	table.change_function(&function2);
	table.add(32, "world");

	std::cout << "--------\n";

	std::cout << table;

	return 0;
}