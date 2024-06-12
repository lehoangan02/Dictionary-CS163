#pragma once
#include <string>
#include <vector>

const int ascii = 96; //32-127

struct trieNode
{
	bool wordExisted = false;
	trieNode* childNode[96];
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
bool Checkingexistance(std::string s1, std::string s2);
void insert(trieNode*& pCurrent, std::string word, std::vector<std::pair<std::string, std::string>> definitions);

void traverseToSearch(trieNode* pRoot, std::string word);

void search(trieNode* pRoot, std::string word);

void remove(trieNode*& pRoot, std::string word);

void deleteTrie(trieNode*& pRoot);

bool isLeaf(trieNode* pRoot);