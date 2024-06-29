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
bool checkingExistance(std::string s1, std::string s2);
void insert(trieNode*& pCurrent, std::string word, std::vector<std::pair<std::string, std::string>> definitions);

std::vector<std::pair<std::string, std::string>> traverseToSearch(trieNode* pRoot, std::string word);

void search(trieNode* pRoot, std::string word);

bool isLeaf(trieNode* pRoot);

void RemoveAWord(trieNode*& pRoot, std::string word);

void deleteWholeTrie(trieNode*& pRoot);

void serializeWrapper(trieNode* pRoot);
void serialize(trieNode* pRoot, std::ofstream& fout, std::string word);

bool deserializeWrapper(trieNode*& pRoot);
void deserialize(trieNode*& pRoot, std::ifstream& fin, std::string word);
trieNode* pickarandomword(trieNode* pRoot);

trieNode* findtheKthword(trieNode* pRoot, int k);