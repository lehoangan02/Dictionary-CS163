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
	// bool imported = false;
	// bool serialized = true;
	while (mode != 0)
	{
		printf("1 for importing the data\n");
		printf("2 for searching the library\n");
		printf("3 for serialization\n");
		printf("4 for deserialization\n");
		std::cout << "mode: ";
		std::cin >> mode;
		switch (mode)
		{
		case 1:
			{
				deleteWholeTrie(pRoot);
				pRoot = nullptr;
				std::string filepath; std::cout << "input filepath: "; std::cin >> filepath;
				readDatasetCSV(filepath, pRoot);
				printf("imported successfully\n");
			}
			break;
		case 2:
		{
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			printf("search here: "); std::string searchObject; std::getline(std::cin, searchObject);
			searchObject = "";
			traverseToSearch(pRoot, searchObject);
		}
		break;
		case 3:
		{
			serializeWrapper(pRoot);
		}
		break;
		case 4:
		{
			deserializeWrapper(pRoot);
		}
		default:
		{
			deleteWholeTrie(pRoot);
		}
			break;
		}
	}
}
