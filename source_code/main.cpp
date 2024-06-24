#include <iostream>
#include <string>

#include "trie.h"
#include "instance.h"
#include "readDatasetCSV.hpp"

using namespace std;

int main()
{
	trieNode* pRoot = nullptr;
	int mode = -1;
	bool imported = false;
	while (mode != 0)
	{
		printf("1 for importing the data\n");
		printf("2 for searching the library\n");
		std::cout << "mode: ";
		std::cin >> mode;
		switch (mode)
		{
		case 1:
			{
				std::string filepath; std::cout << "input filepath: "; std::cin >> filepath;
				readDatasetCSV(filepath, pRoot);
				printf("imported successfully\n");
				imported = true;
			}
			break;
		case 2:
		{
			if (!imported)
			{
				printf("please import the dataset first.\n");
				break;
			}

		}
		default:
			break;
		}
	}
}
