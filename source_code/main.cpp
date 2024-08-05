#include <iostream>
#include <string>
#include <chrono>
#include <unordered_set>

#include "trie.h"
#include "readDataset.hpp"
#include "SerializeDeserialize.h"
#include "maptable.hpp"
#include "instance.h"

using namespace std;

int main()
{
	//std::vector<std::string> word4Def;
	//trieNode* pRoot = nullptr;
	//int mode = -1;
	//HashMap invertedIndex;
	//bool indexed = false;
	//// bool imported = false;
	//// bool serialized = true;
	//while (mode != 0)
	//{
	//	printf("1 for importing the data\n");
	//	printf("2 for searching the library\n");
	//	printf("3 for serialization\n");
	//	printf("4 for deserialization\n");
	//	printf("5 for suggesting words\n");
	//	printf("6 for viewing a random word and its definitions\n");
	//	printf("7 for searching by definitions\n");
	//	printf("8 for editing a definitions\n");
	//	printf("9 for removing a word\n10 for import CSV\n");
	//	printf("11 for a random word with 4 definitions\n");
	//	printf("12 for a random defition with 4 keywords\n");
	//	cout << "mode: ";
	//	cin >> mode;
	//	switch (mode)
	//	{
	//	case 1:
	//	{
	//		deleteWholeTrie(pRoot);
	//		string filename;
	//		cout << "input filename: ";
	//		cin.ignore();
	//		getline(cin, filename);
	//		readDatasetTXT(filename, pRoot, word4Def);
	//		//printf("imported successfully\n");
	//		cout << "[DEBUG] " << pRoot << endl;
	//		if (indexed)
	//		{
	//			invertedIndex.clear();
	//			indexed = false;
	//		}
	//		break;
	//	}
	//	case 2:
	//	{
	//		cin.ignore(numeric_limits<streamsize>::max(), '\n');
	//		cout << "search here: ";
	//		string searchObject;
	//		getline(cin, searchObject);
	//		cout << "searching: " << searchObject << endl;
	//		//cout << "[DEBUG] " << pRoot << endl;
	//		vector<pair<string, string>> test = Search(pRoot, searchObject);
	//		if (test.empty()) {
	//			cout << "Word not found\n";
	//		}
	//		else {
	//			for (auto& x : test)
	//			{
	//				cout << "-    (" << x.first << ") : ";
	//				cout << x.second << endl;
	//			}
	//		}
	//		break;
	//	}
	//	case 3:
	//	{
	//		auto start_time = chrono::high_resolution_clock::now();
	//		fstream f; f.open("serialized.bin", ios::out | ios::trunc | ios::binary);
	//		std::string temp = "";
	//		serializeBinary(pRoot, f, temp);
	//		f.close();
	//		auto end_time = chrono::high_resolution_clock::now();
	//		cout << "Finished" << endl;
	//		chrono::duration<double> elapsed = end_time - start_time;
	//		cout << "Building took " << elapsed.count() << " seconds" << endl;
	//		
	//		break;
	//	}
	//	case 4:
	//	{
	//		auto start_time = chrono::high_resolution_clock::now();
	//		
	//		deleteWholeTrie(pRoot);
	//		fstream f; f.open("serialized.bin", ios::in | ios::binary);
	//		if (f.is_open() == false)
	//		{
	//			cout << "[DEBUG] no file found to deserialize!\n";
	//			break;
	//		}
	//		deserializeBinaryWrapper(pRoot, word4Def);
	//		cout << "[DEBUG] " << pRoot << endl;

	//		auto end_time = chrono::high_resolution_clock::now();
	//		cout << "Finished" << endl;
	//		chrono::duration<double> elapsed = end_time - start_time;
	//		cout << "Building took " << elapsed.count() << " seconds" << endl;
	//		break;
	//	}
	//	case 5:
	//	{
	//		cout << "Please input: "; cin.ignore();
	//		string prefix;
	//		getline(cin, prefix);
	//		cout << prefix << endl;
	//		cout << "Here are some suggestions: " << endl;
	//		vector<string> suggested = SuggestingWords(prefix, pRoot);
	//		if (!suggested.empty())
	//		{
	//			for (auto& x : suggested)
	//			{
	//				cout << x << endl;
	//			}
	//		} else cout << "Trying another!" << endl;
	//		break;
	//	}
	//	case 6:
	//	{
	//		cout << "The random word is: "; cin.ignore();
	//		pair<trieNode*, string> random = pickarandomword(pRoot);
	//		if (random.first) {
	//			cout << random.second << endl;
	//			int i = 0;
	//			for (auto& x : random.first->definitions) {
	//				cout << i + 1 << ". (" << x.first << ") " << x.second << endl;
	//				i++;
	//			}
	//		}
	//		else {
	//			cout << "=> Can't find a random word !" << endl;
	//		}
	//		break;
	//	}
	//	case 7:
	//	{
	//		cin.ignore(numeric_limits<streamsize>::max(), '\n');
	//		if (!indexed)
	//		{
	//			cout << "Creating Inverted Index..." << endl;
	//			
	//			auto start_time = chrono::high_resolution_clock::now();
	//			invertIndexTrie(pRoot, invertedIndex);
	//			
 //   			auto end_time = chrono::high_resolution_clock::now();
	//			cout << "Finished" << endl;
	//			chrono::duration<double> elapsed = end_time - start_time;
	//			cout << "Building took " << elapsed.count() << " seconds" << endl;
	//			cout << "Tokens generated: " << invertedIndex.size << endl;
	//			indexed = true;
	//		}
	//		string userInput;
	//		cout << "Your input: ";
	//		getline(cin, userInput);
	//		vector<string> res = searchByDef(userInput, invertedIndex);
	//		sortByDefLength(res, pRoot);
	//		for (auto& s : res)
	//			cout << s << endl;
	//		break;
	//	}
	//	case 8:
	//	{
	//		cin.ignore(numeric_limits<streamsize>::max(), '\n');
	//		string word;
	//		int defNum;
	//		pair<string, string> newDef;
	//		cout << "Word: ";
	//		getline(cin, word);
	//		cout << "Definition Number: ";
	//		cin >> defNum;
	//		cin.ignore();
	//		cout << "New Definition for " << word << endl;
	//		cout << "POS: ";
	//		getline(cin, newDef.first);
	//		cout << "Definition: ";
	//		getline(cin, newDef.second);

	//		editDefinition(word, defNum, newDef, pRoot, invertedIndex);
	//		break;
	//	}
	//	case 9:
	//	{
	//		cin.ignore(numeric_limits<streamsize>::max(), '\n');
	//		string word;
	//		cout << "You want to delete: ";
	//		getline(cin, word);

	//		removeWord(word, pRoot, invertedIndex, word4Def);
	//		break;
	//	}
	//	case 10:
	//	{
	//		word4Def.reserve(6000);
	//		std::string filepath; printf("input filepath: "); std::cin >> filepath;
	//		auto start_time = chrono::high_resolution_clock::now();
	//		readDatasetCSV(filepath, pRoot, word4Def);
	//		auto end_time = chrono::high_resolution_clock::now();
	//		cout << "Finished" << endl;
	//		chrono::duration<double> elapsed = end_time - start_time;
	//		cout << "Building took " << elapsed.count() << " seconds" << endl;
	//		for (int i = 0; i < static_cast<int>(word4Def.size()); ++i)
	//		{
	//			std::cout << word4Def[i] << std::endl;
	//		}
	//		break;
	//	}
	//	case 11:
	//	{
	//		/*for (auto word : word4Def)
	//		{
	//			std::cout << word << std::endl;
	//		}*/
	//		std::string rdword = randomWord4Def(word4Def);
	//		std::cout << "\n- The random word is: " << rdword << std::endl;
	//		std::cout << "\nHere are 4 definitions for guessing: " << std::endl;
	//		std::vector < std::pair<std::string, std::string>> DefList = traverseToSearch(pRoot, rdword);
	//		for (int i = 0; i < 4; ++i)
	//		{
	//			std::cout << i + 1 << ". (" << DefList[i].first << ") " << DefList[i].second << std::endl;
	//		}
	//		std::cout << "\n- Please enter your word: "; cin.ignore();
	//		std::string guess;
	//		getline(cin, guess);
	//		Change2Lowercase(guess);
	//		if (!CheckWords(rdword, guess)) std::cout << "=> Correct !"; else cout << "=> Incorrect !";
	//		std::cout << endl;
	//	}
	//	case 12:
	//	{
	//		std::pair<trieNode*, std::string> rdword;
	//		std::unordered_set<std::string> WordList;
	//		RandomDef(pRoot, WordList, rdword);
	//		std::cout << "\n- The random definition is: " << rdword.first->definitions[0].second << std::endl;
	//		std::cout << std::endl;
	//		int i = 1;
	//		for (auto it : WordList)
	//		{
	//			cout << i << ") " << it << std::endl;
	//			i++;
	//		}
	//		std::string answer; 
	//		std::cout << "- Choose the correct keywords : "; cin.ignore();  getline(cin, answer);
	//		if (!CheckWords(answer, rdword.second)) std::cout << "=> Correct !"; else cout << "=> Incorrect !";
	//		std::cout << endl;
	//	}
	//	default:
	//		break;
	//	}
	//}
	//deleteWholeTrie(pRoot);
	//return 0;
	instance i;
	i.operate();
}