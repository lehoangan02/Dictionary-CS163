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
				std::string filepath; std::cout << "input filepath: "; std::cin >> filepath;
				readDatasetCSV(filepath, pRoot);
				printf("imported successfully\n");
				std::cout << "[DEBUG] " << pRoot << std::endl;
			}
			break;
		case 2:
		{
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			printf("search here: "); std::string searchObject; std::getline(std::cin, searchObject);
			std::cout << "searching: " << searchObject << std::endl;
			std::cout << "[DEBUG] " << pRoot << std::endl;
			traverseToSearch(pRoot, searchObject);
		}
		break;
		case 3:
		{
			std::fstream f; f.open("serialized.bin", std::ios::out | std::ios::trunc | std::ios::binary);
			serializeBinary(pRoot, f, "");
			f.close();
		}
		break;
		case 4:
		{
			deleteWholeTrie(pRoot);
			std::fstream f; f.open("serialized.bin", std::ios::in | std::ios::binary);
			if (f.is_open() == false)
			{
				std::cout << "[DEBUG] no file found to deserialize!\n";
				return false;
			}
			deserializeBinary(pRoot, f, "");
			std::cout << "[DEBUG] " << pRoot << std::endl;
			break;
		}
		break;
		default:
		break;
		}
	}
}
