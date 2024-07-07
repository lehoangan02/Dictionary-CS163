#include <iostream>
#include <string>

#include "trie.h"
#include "instance.h"
#include "readDataset.hpp"
#include "SerializeDeserialize.h"
#include "maptable.hpp"

using namespace std;

int main()
{
	trieNode* pRoot = nullptr;
	int mode = -1;
	HashMap invertedIndex;
	bool indexed = false;
	// bool imported = false;
	// bool serialized = true;
	while (mode != 0)
	{
		printf("1 for importing the data\n");
		printf("2 for searching the library\n");
		printf("3 for serialization\n");
		printf("4 for deserialization\n");
		printf("5 for suggesting words\n");
		printf("6 for viewing a random word and its definitions\n");
		printf("7 for searching by definitions\n");
		std::cout << "mode: ";
		std::cin >> mode;
		switch (mode)
		{
		case 1:
		{
			deleteWholeTrie(pRoot);
			std::string filename;
			std::cout << "input filename: ";
			std::cin.ignore();
			std::getline(std::cin, filename);
			readDatasetTXT(filename, pRoot);
			//printf("imported successfully\n");
			std::cout << "[DEBUG] " << pRoot << std::endl;
			if (indexed)
			{
				invertedIndex.clear();
				indexed = false;
			}
			break;
		}
		case 2:
		{
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			std::cout << "search here: ";
			std::string searchObject;
			std::getline(std::cin, searchObject);
			std::cout << "searching: " << searchObject << std::endl;
			//std::cout << "[DEBUG] " << pRoot << std::endl;
			std::vector<std::pair<std::string, std::string>> test = Search(pRoot, searchObject);
			if (test.empty()) {
				std::cout << "Word not found\n";
			}
			else {
				for (auto& x : test)
				{
					std::cout << "-    (" << x.first << ") : ";
					std::cout << x.second << std::endl;
				}
			}
			break;
		}
		case 3:
		{
			std::fstream f; f.open("serialized.bin", std::ios::out | std::ios::trunc | std::ios::binary);
			serializeBinary(pRoot, f, "");
			f.close();
			break;
		}
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
		case 5:
		{
			std::cout << "Please input: "; cin.ignore();
			std::string prefix;
			getline(cin, prefix);
			std::cout << prefix << std::endl;
			std::cout << "Here are some suggestions: " << std::endl;
			if (!SuggestingWords(prefix, pRoot))
			{
				std::cout << "Trying another!" << std::endl;
			}
			break;
		}
		case 6:
		{
			std::cout << "The random word is: "; cin.ignore();
			std::pair<trieNode*, std::string> random = pickarandomword(pRoot);
			if (random.first) {
				std::cout << random.second << std::endl;
				int i = 0;
				for (auto& x : random.first->definitions) {
					std::cout << i + 1 << ". (" << x.first << ") " << x.second << std::endl;
					i++;
				}
			}
			else {
				std::cout << "=> Can't find a random word !" << std::endl;
			}
			break;
		}
		case 7:
		{
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			std::cout << "Creating Inverted Index..." << std::endl;
			invertIndexTrie(pRoot, invertedIndex);
			std::cout << "Finished" << std::endl;
			indexed = true;
			std::string userInput;
			std::cout << "Your input: ";
			getline(cin, userInput);
			HashTable res = searchByDef(userInput, invertedIndex); // May need to convert res to vector<string>
			for (int i = 0; i < res.numBucket; ++i)
			{
				TableBlock* pCur = res.set[i];
				while (pCur)
				{
					std::cout << pCur->data << std::endl;
					pCur = pCur->pNext;
				}
			}
			break;
		}
		default:
			break;
		}
	}
	deleteWholeTrie(pRoot);
	return 0;
}
