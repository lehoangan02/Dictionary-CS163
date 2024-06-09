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
		next = new trieNode* [69]; // ASCII from 32 to 64 and from 91 to 126
		for (int i = 0; i < 69; i++) next[i] = nullptr;
	}
};

void load();

void insert(trieNode*& pCurrent, std::string word);

bool find(trieNode* pCurrent, std::string word);