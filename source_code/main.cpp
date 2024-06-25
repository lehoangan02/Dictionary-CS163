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
	bool serialized = true;
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
				pRoot = nullptr;
				std::string filepath; std::cout << "input filepath: "; std::cin >> filepath;
				readDatasetCSV(filepath, pRoot);
				printf("imported successfully\n");
				imported = true;
			}
			break;
		case 2:
		{
			if (!imported && !serialized)
			{
				printf("please import the dataset first.\n");
				break;
			}
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			printf("search here: "); std::string searchObject; std::getline(std::cin, searchObject);
			traverseToSearch(pRoot, searchObject);
		}
		break;
		case 3:
		{
			if (!imported && ! serialized)
			{
				printf("please import the dataset first.\n");
				break;
			}
			std::ofstream fout; fout.open("serialized.txt");
			serialize(pRoot, fout, "");
		}
		break;
		case 4:
		{
			if (!serialized)
			{
				printf("please import or serialize the dataset first.\n");
				break;
			}
			pRoot = nullptr;
			std::ifstream fin; fin.open("serialized.txt");
			deserialize(pRoot, fin, "");
		}
		default:
			break;
		}
	}
}
