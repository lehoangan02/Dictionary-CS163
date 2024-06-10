#include <iostream>
#include <vector>
#include <string>
#include "trie.h"

void lowercase(std::string word)
{
	for (int i = 0; i < word.length(); i++)
	{
		if (word[i] >= 65 && word[i] < 91) word[i] += 32;
	}
}

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
			if (word[0] == 32) insert(pCurrent->next[26], word.erase(0, 1));
			else if (word[0] == 45) insert(pCurrent->next[27], word.erase(0, 1));
			else if (word[0] == 39) insert(pCurrent->next[28], word.erase(0, 1));
			else insert(pCurrent->next[word[0] - 97], word.erase(0, 1));
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