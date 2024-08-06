#pragma once
#include <string>
#include <vector>
#include <unordered_set>
#include <fstream>

#include "wrapping.hpp"

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

// for tracking the original word and the number of definitions
// this is necessary for similar word with different (upper/lower) cases
// std::vector<std::pair<std::string, int>> originalList;
void Change2Lowercase(std::string& word);

void Change2Uppercase(std::string& word);

bool checkingExistance(std::string s1, std::string s2);

// these functions should be overloaded
/// @brief the original insert function (it's still needed), you should not use this in instance.cpp
/// @param pRoot 
/// @param word 
/// @param definitions 
void insert(trieNode*& pRoot, std::string word, std::vector<std::pair<std::string, std::string>> definitions);
/// @brief the new insert function, you should use this in instance.cpp
void insert(trieNode*& pRoot, std::string& word, const std::string& pos, const std::string& def, std::vector<std::string>& word4Def);
bool shouldAddWord(const std::vector<std::string>& word4Def, const std::string& word, trieNode* pRoot);
void ChangeCountChild(trieNode*& pRoot, std::string word);

std::vector<std::pair<std::string, std::string>> traverseToSearch(trieNode* pRoot, std::string word);

std::vector<std::pair<std::string, std::string>> Search(trieNode* pRoot, std::string word);

bool isLeaf(trieNode* pRoot);

void RemoveAWord(trieNode*& pRoot, std::string word);

void deleteWholeTrie(trieNode*& pRoot);

std::pair<trieNode*, std::string> pickarandomword(trieNode* pRoot);

std::pair<trieNode*, std::string> findtheKthword(trieNode* pRoot, int k);

std::vector <std::string> SuggestingWords(std::string word, trieNode* pRoot);

void SuggestHelper(std::string prefix, trieNode* pRoot, int& count, std::vector<std::string>& collection);

bool compareDefLength(std::string& s1, std::string& s2, trieNode*& pRoot);
void sortByDefLength(std::vector<std::string>& keyWords, trieNode*& pRoot);
void mergeSort(std::vector<std::string>& words, size_t left, size_t right, trieNode*& pRoot);
void merge(std::vector<std::string>& words, size_t left, size_t mid, size_t right, trieNode*& pRoot);

std::string randomWord4Def(std::vector<std::string>& word4Def);
bool CheckWords(const std::string& word1, const std::string& word2);
void RandomDef(trieNode* pRoot, std::unordered_set<std::string>& WordList, std::pair<trieNode*, std::string>& rdword);

bool correction(std::string &correctWord, trieNode* &pRoot);