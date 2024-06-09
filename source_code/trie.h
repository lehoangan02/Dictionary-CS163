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

void load()
{
	
}

void insert(trieNode*& pCurrent, std::string word)
{
	if (pCurrent == nullptr)
	{
		if (word.length() == 0) pCurrent = new trieNode(true);
		else
		{
			pCurrent = new trieNode(false);
			insert(pCurrent->next[word[0] - 97], word.erase(0, 1));
		}
	}
	else
	{
		if (word.length() == 0) pCurrent->wordExisted = true;
		else insert(pCurrent->next[word[0] - 97], word.erase(0, 1));
	}
}
bool find(trieNode* pCurrent, std::string word)
{
	if (!pCurrent) return false;
	if (word.length() == 0) return pCurrent->wordExisted;
	else return find(pCurrent->next[word[0] - 97], word.erase(0, 1));
}