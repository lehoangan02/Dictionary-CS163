#include <iostream>
#include <vector>
#include <string>
#include <cctype>
#include <algorithm>
#include <random>
#include "trie.h"

void Change2Lowercase(std::string& word)
{
	// Check if the string is empty before transforming
	if (!word.empty()) 
	{
		std::transform(word.begin(), word.end(), word.begin(),
			[](unsigned char c) { return std::tolower(c); });
	}
}

bool checkingExistance(std::string s1, std::string s2)
{
	if (s1.size() != s2.size()) return false;
	for (int i = 0; i < s1.size(); ++i)
	{
		if (s1[i] != s2[i]) return false;
	}
	return true;
}

void insert(trieNode*& pRoot, const std::string& word, const std::string& pos, const std::string& def)
{
	if (word.empty()) return;
	if (!pRoot) {
		pRoot = new trieNode();
	}

	trieNode* cur = pRoot;
	cur->countchildren++;
	for (auto c : word) {
		if (!cur->childNode[int(c) - 32]) {
			cur->childNode[int(c) - 32] = new trieNode();
		}
		cur = cur->childNode[int(c) - 32];
		cur->countchildren++;
	}
	cur->wordExisted = true;

	bool checkexist = false;
	for (auto& means : cur->definitions) {
		if (means.first == pos && means.second == def) {
			checkexist = true;
			break;
		}
	}

	if (!checkexist) cur->definitions.push_back({ pos, def });
}

std::vector<std::pair<std::string, std::string>> traverseToSearch(trieNode* pRoot, std::string word, int& k)
{
	std::vector<std::pair<std::string, std::string>> blankVec;
	if (!pRoot) 
	{
		std::cout << "Word not found1\n";
		return blankVec;
	}
	// base case
	if (word.length() == 0)
	{
		if (pRoot->wordExisted)
		{
			for (int i = 0; i < (int)pRoot->definitions.size(); i++)
			{
				std::cout << k + 1 << " (" << pRoot->definitions[i].first << ") : ";
				std::cout << pRoot->definitions[i].second << std::endl;
				k++;
			}
			return pRoot->definitions;
		}
		else
		{
			std::cout << "Word not found2\n";
			return pRoot->definitions;
		}
	}

	// letters case
	if (word[0] >= 32 && word[0] <= 127)
	{

		// if the childNode pointer of that letter is not null, continue traversing
		if (pRoot->childNode[word[0] - 32])
		{
			//std::cout << "[DEBUG] going into " << word[0] << std::endl;
			// erase the first letter
			pRoot = pRoot->childNode[word[0] - 32];
			return traverseToSearch(pRoot, word.erase(0, 1), k);
		}
		else
		{
			std::cout << "Word not found3\n";
			return pRoot->definitions;
		}
	}
	return blankVec;
}

void search(trieNode* pRoot, std::string word)
{
	if (!pRoot || word.length() == 0)
	{
		std::cout << "Word not found\n";
		return;
	}

	std::cout << "Here are the definitions of the word: \n";
	int i = 0;

	if (word[0] >= 'A' && word[0] <= 'Z') {
		// traverse the trie to find the word (the first letter in Capital form)
		traverseToSearch(pRoot, word, i);
	}

	// convert all the letters to lowercase
	Change2Lowercase(word);

	// traverse the trie to find the word (the first letter in Lowercase)
	traverseToSearch(pRoot, word, i);
}

//checking whether a trieNode a leaf node
bool isLeaf(trieNode* pRoot)
{
	if (!pRoot)
		return false;
	for (int i = 0; i < ascii; ++i)
	{
		if (pRoot->childNode[i])
			return false;
	}
	return true;
}

//7. Users can remove a word from the dictionary.
void RemoveAWord(trieNode*& pRoot, std::string word)
{
	//base case
	if (!pRoot)
		return;
	if (word.size() == 0)  {
		if (pRoot->wordExisted) {
			pRoot->wordExisted = false;
			pRoot->definitions.clear();

			//check whether it is the last node (delete) or prefix for other words.
			if (!isLeaf(pRoot)) {
				delete pRoot;
				pRoot = nullptr;
			}
		}
		return;
	}

	int indexNext = tolower(word[0]) - 32;
	RemoveAWord(pRoot->childNode[indexNext], word.erase(0, 1));
	pRoot->countchildren--;
	if (isLeaf(pRoot) && !pRoot->wordExisted)
	{
		delete pRoot;
		pRoot = nullptr;
	}
}

//delete the whole tree
void deleteWholeTrie(trieNode*& pRoot)
{
	if (!pRoot)
		return;
	for (int i = 0; i < ascii; ++i)
	{
		deleteWholeTrie(pRoot->childNode[i]);
	} //update
	delete pRoot;
	pRoot = nullptr;
}

// serialization of the existing trie
void serializeWrapper(trieNode* pRoot)
{
	std::ofstream fout; fout.open("serialized.txt");
	serialize(pRoot, fout, "");
}

void serialize(trieNode* pRoot, std::ofstream& fout, std::string word)
{
	if (!pRoot)
	{ 
		fout << "-1\n";
		std::cout << "[DEBUG] -1\n";
		return;
	}
	fout << pRoot -> wordExisted << std::endl;
	fout << "[DEBUG] " << word << std::endl;
	fout << pRoot -> definitions.size() << std::endl;
	for (int i = 0; i < (int)(pRoot -> definitions.size()); ++i)
	{
		fout << pRoot -> definitions[i].first << std::endl;
		fout << pRoot -> definitions[i].second << std::endl;
	}
	for (int i = 0; i < 96; ++i)
	{
		int asciiVal = i + 32;
		std::string newWord = word + (char)asciiVal;
		std::cout << "[DEBUG] new word is " << newWord << std::endl;
		serialize(pRoot -> childNode[i], fout, newWord);
	}
	return;
}

// deserialization of the saved trie
bool deserializeWrapper(trieNode*& pRoot)
{
	deleteWholeTrie(pRoot);
	std::ifstream fin; fin.open("serialized.txt");
	if (fin.is_open() == false)
	{
		std::cout << "[DEBUG] no file found to deserialize!\n";
		return false;
	}
	deserialize(pRoot, fin, "");
    return true;
}

void deserialize(trieNode*& pRoot, std::ifstream& fin, std::string word)
{
	int temp = 0;
	fin >> temp;
	fin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	if (temp == -1)
	{
		std::cout << "[DEBUG] empty node\n";
		pRoot = nullptr;
		return;
	}
	pRoot = new trieNode;
	pRoot -> wordExisted = temp;
	std::string tempString = "";
	std::getline(fin, tempString);
	std::cout << "[DEBUG] word is: " << tempString << std::endl;
	int size = 0;
	fin >> size;
	fin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	std::vector<std::pair<std::string, std::string>> definitionVec;
	for (int i = 0; i < size; ++i)
	{
		std::string POS = "";
		std::string description = "";
		std::getline(fin, POS);
		std::getline(fin, description);
		definitionVec.push_back(std::pair<std::string, std::string>{POS, description});
		std::cout << "[DEBUG] POS: " << POS << " - definition: " << description << std::endl;
	}
	pRoot -> definitions = definitionVec;
	for (int i = 0; i < 96; ++i)
	{
		std::string newWord = word + (char)(i + 32);
		std::cout << "[DEBUG] probing " << newWord << std::endl;
		deserialize(pRoot -> childNode[i], fin, newWord);
	}
}

void serializeBinary(trieNode*& pRoot, std::fstream& f, std::string word)
{
	int temp = 0;
	if (!pRoot)
	{
		temp = -1;
		f.write((char*)&temp, sizeof(int));
		return;
	}
	temp = 0;
	f.write((char*)&temp, sizeof(int));
	bool wordExisted = pRoot -> wordExisted;
	f.write((char*)&wordExisted, sizeof(bool));
	int size = (int)(pRoot -> definitions.size());
	f.write((char*)&size, sizeof(int));
	for (int i = 0; i < size; ++i)
	{
		size_t stringSize = pRoot -> definitions[i].first.size();
		f.write((char*)&stringSize, sizeof(int));
		f.write(pRoot -> definitions[i].first.c_str(), pRoot -> definitions[i].first.size());
		// std::cout << pRoot -> definitions[i].first.c_str() << std::endl;
		stringSize = pRoot -> definitions[i].second.size();
		f.write((char*)&stringSize, sizeof(int));
		f.write(pRoot -> definitions[i].second.c_str(), pRoot -> definitions[i].second.size());
		// std::cout << pRoot -> definitions[i].second.c_str() << std::endl;
	}
	for (int i = 0; i < 96; ++i)
	{
		int asciiVal = i + 32;
		std::string newWord = word + (char)asciiVal;
		// std::cout << "[DEBUG] new word is " << newWord << std::endl;
		serializeBinary(pRoot -> childNode[i], f, newWord);
	}
	return;
}

void deserializeBinary(trieNode*& pRoot, std::fstream& f, std::string word)
{
	int temp = 0;
	f.read((char*)&temp, sizeof(int));
	if (temp == -1)
	{
		// std::cout << "[DEBUG] empty node\n";
		pRoot = nullptr;
		return;
	}
	pRoot = new trieNode;
	bool wordExisted = false;
	f.read((char*)&wordExisted, sizeof(bool));
	pRoot -> wordExisted = wordExisted;
	int sizeDef = 0;
	f.read((char*)&sizeDef, sizeof(int));
	int sizeString = 0;
	std::vector<std::pair<std::string, std::string>> definitionVec;
	for (int i = 0; i < sizeDef; ++i)
	{
		std::string POS = "";
		std::string description = "";
		f.read((char*)&sizeString, sizeof(int)); // read the size of POS
		char* buffer = new char[sizeString]; // allocate a char array buffer
		f.read(buffer, sizeString);
		POS.assign(buffer, sizeString);
		delete [] buffer;
		f.read((char*)&sizeString, sizeof(int)); // read the size of description
		buffer = new char[sizeString]; // allocate a char array buffer
		f.read(buffer, sizeString);
		description.assign(buffer, sizeString);
		delete [] buffer;
		definitionVec.push_back(std::pair<std::string, std::string>{POS, description});
		// std::cout << "[DEBUG] POS: " << POS << " - definition: " << description << std::endl;
	}
	pRoot -> definitions = definitionVec;
	for (int i = 0; i < 96; ++i)
	{
		std::string newWord = word + (char)(i + 32);
		// std::cout << "[DEBUG] probing " << newWord << std::endl;
		deserializeBinary(pRoot -> childNode[i], f, newWord);
	}
}

//9. Users can view a random and its definitions.
trieNode* FindKthWord(trieNode* pRoot, int k, std::string prefix)
{
	if (!pRoot) return nullptr;
	if (pRoot->wordExisted)
	{
		k--;
		if (k == 0)
		{
			std::cout << prefix << std::endl;
			int i = 1;
			std::cout << "POS | DEFINITION" << std::endl;
			for (auto& x : pRoot->definitions)
			{
				std::cout << i << ". (" << x.first << ") " << x.second << std::endl;
				i++;
			}
			return pRoot;
		}
	}

	for (int i = 0; i < 96; ++i)
	{
		trieNode* c = pRoot->childNode[i];
		if (!c) continue;
		if (c->countchildren < k) {
			k -= c->countchildren;
		}
		else {
			prefix += static_cast<char>(i + 32);
			return FindKthWord(c, k, prefix);
		}
	}
	return nullptr;
}

bool PickRandomWord(trieNode* pRoot)
{
	if (!pRoot) return false;
	std::random_device dev;
    std::mt19937 random(dev());
    std::uniform_int_distribution<std::mt19937::result_type> dist(1,pRoot->countchildren);
	trieNode* RandomWord = FindKthWord(pRoot, dist(random), "");
	if (!RandomWord) return false;
	return true;
}

//Utility function for suggesting some existing words based on some first given characters.
bool SuggestingWords(std::string word, trieNode* pRoot)
{
	if (word.empty()) return false;
	
	trieNode* cur = pRoot;
	for (auto& c : word) {
		if (!cur->childNode[c - 32]) {
			std::cout << "Word is not exist!" << std::endl;
			return false;
		}
		cur = cur->childNode[c - 32];
	}

	//Displaying max 10 words whose prefixes are the same with given word
	int count = 0;
	std::vector<std::string> collection;
	SuggestHelper(word, cur, count, collection);
	for (auto& x : collection) {
		std::cout << x << std::endl;
	}
	return true;
}

void SuggestHelper(std::string prefix, trieNode* pRoot, int& count, std::vector<std::string>& collection)
{
	if (!pRoot || count == 10) return;
	if (pRoot->wordExisted) {
		collection.push_back(prefix);
		count++;
	}
	for (int i = 0; i < 96; i++) {
		if (pRoot->childNode[i]) {
			prefix += static_cast<char>(i + 32);
			SuggestHelper(prefix, pRoot->childNode[i], count, collection);
			prefix.pop_back();
		}
	}
}