#include <iostream>
#include <vector>
#include <string>
#include "trie.h"

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