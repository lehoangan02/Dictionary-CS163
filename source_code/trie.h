#pragma once
#include <string>
#include <vector>
#include <fstream>

const int ascii = 96; //32-127

struct trieNode
{
	bool wordExisted = false;
	trieNode* childNode[96];
	int countchildren = 0;
	std::vector<std::pair<std::string, std::string>> definitions;
	trieNode()
	{
		// 0->25: letters
		// 26: space (' ')
		// 27: dash ('-')
		// 28: apostrophe (')

		for (int i = 0; i < ascii; ++i) this->childNode[i] = nullptr;
		this->definitions.resize(0);
		
	}
};

//for favorite list and searched words.
struct Node
{
	std::string word;
	Node* next;

	Node(std::string key) : word(key), next(nullptr) {};
};

void Change2Lowercase(std::string& word);

void Change2Uppercase(std::string& word);

bool checkingExistance(std::string s1, std::string s2);

void insert(trieNode*& pRoot, std::string word, std::vector<std::pair<std::string, std::string>> definitions);
void insert(trieNode*& pRoot, const std::string& word, const std::string& pos, const std::string& def);

std::vector<std::pair<std::string, std::string>> traverseToSearch(trieNode* pRoot, std::string word);

std::vector<std::pair<std::string, std::string>> Search(trieNode* pRoot, std::string word);

bool isLeaf(trieNode* pRoot);

void RemoveAWord(trieNode*& pRoot, std::string word);

void deleteWholeTrie(trieNode*& pRoot);

std::pair<trieNode*, std::string> pickarandomword(trieNode* pRoot);

std::pair<trieNode*, std::string> findtheKthword(trieNode* pRoot, int k);

bool SuggestingWords(std::string word, trieNode* pRoot);

void SuggestHelper(std::string prefix, trieNode* pRoot, int& count, std::vector<std::string>& collection);

bool compareDefLength(std::string& s1, std::string& s2, trieNode*& pRoot);
void sortByDefLength(std::vector<std::string>& keyWords, trieNode*& pRoot);
void mergeSort(std::vector<std::string>& words, size_t left, size_t right, trieNode*& pRoot);
void merge(std::vector<std::string>& words, size_t left, size_t mid, size_t right, trieNode*& pRoot);