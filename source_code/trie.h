#pragma once
#include <string>
#include <vector>
#include <unordered_set>
#include <fstream>

// #include "wrapping.hpp"

const int ascii = 96; //32-127

struct TrieNode
{
	bool wordExisted = false;
	TrieNode* childNode[96];
	int countchildren = 0;
	std::vector<std::pair<std::string, std::string>> definitions;
	TrieNode()
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
void insert(TrieNode*& pRoot, std::string word, std::vector<std::pair<std::string, std::string>> definitions);
/// @brief the new insert function, you should use this in instance.cpp
void insert(TrieNode*& pRoot, std::string& word, const std::string& pos, const std::string& def, std::vector<std::string>& word4Def);
bool shouldAddToWord4Def(const std::vector<std::string>& word4Def, const std::string& word, TrieNode* pRoot);
void revertCountChildren(TrieNode*& pRoot, std::string word);

std::vector<std::pair<std::string, std::string>> traverseToSearch(TrieNode* pRoot, std::string word);

std::vector<std::pair<std::string, std::string>> Search(TrieNode* pRoot, std::string word);

bool isLeaf(TrieNode* pRoot);

void RemoveAWord(TrieNode*& pRoot, std::string word);

void deleteWholeTrie(TrieNode*& pRoot);

std::pair<TrieNode*, std::string> pickarandomword(TrieNode* pRoot);

std::pair<TrieNode*, std::string> findtheKthword(TrieNode* pRoot, int k);

std::vector <std::string> SuggestingWords(std::string word, TrieNode* pRoot);

void SuggestHelper(std::string prefix, TrieNode* pRoot, int& count, std::vector<std::string>& collection);

int getDefLength(std::string& word, TrieNode*& pRoot);
void sortByDefLength(std::vector<std::string>& keyWords, TrieNode*& pRoot);
void mergeSort(std::vector<std::string>& words, size_t left, size_t right, std::vector<int>& compareVal);
void merge(std::vector<std::string>& words, size_t left, size_t mid, size_t right, std::vector<int>& compareVal);

std::string randomWord4Def(std::vector<std::string>& word4Def);
bool CheckWords(const std::string& word1, const std::string& word2);
void RandomDef(TrieNode* pRoot, std::unordered_set<std::string>& WordList, std::pair<TrieNode*, std::string>& rdword);

bool correction(std::string &correctWord, TrieNode* &pRoot);