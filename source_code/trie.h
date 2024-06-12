#pragma once
#include <string>
#include <vector>

struct trieNode
{
	bool wordExisted;
	trieNode** next;
	std::vector<std::pair<std::string, std::string>> definitions;
	trieNode(bool wordExisted)
	{
		this -> wordExisted = wordExisted;
		next = new trieNode* [29]; 
		// 0->25: letters
		// 26: space (' ')
		// 27: dash ('-')
		// 28: apostrophe (')

		for (int i = 0; i < 29; i++) next[i] = nullptr;
	}
};

void load();

void insert(trieNode*& pCurrent, std::string word);

void traverseToSearch(trieNode* pRoot, std::string word);

void search(trieNode* pRoot, std::string word);

void remove(trieNode*& pRoot, std::string word);

void deleteTrie(trieNode*& pRoot);

bool isLeaf(trieNode* pRoot);