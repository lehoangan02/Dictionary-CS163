#include <iostream>
#include <vector>
#include <string>
#include <cctype>
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

void traverseToSearch(trieNode* pRoot, std::string word)
{
	// base case
	if (word.length() == 0)
	{
		if (pRoot->wordExisted)
		{
			std::cout << "Here are the definitions of the word: \n";

			for (int i = 0; i < (int)pRoot->definitions.size(); i++)
			{
				std::cout << i + 1 << " (" << pRoot->definitions[i].first << ") ";
				std::cout << pRoot->definitions[i].second;
			}
			return;
		}
		else
		{
			std::cout << "Word not found\n";
			return;
		}
	}

	// letters case
	if (word[0] >= 'a' && word[0] <= 'z')
	{

		// if the next pointer of that letter is not null, continue traversing
		if (pRoot->next[word[0] - 97])
		{

			// erase the first letter
			traverseToSearch(pRoot->next[word[0] - 97], word.erase(0, 1));
		}
		else
		{
			std::cout << "Word not found\n";
			return;
		}
	}
	// blank space case
	else if (word[0] == ' ')
	{
		// 26 is index for blank space
		if (pRoot->next[26])
		{

			// erase the first letter
			return traverseToSearch(pRoot->next[26], word.erase(0, 1));
		}
		else
		{
			std::cout << "Word not found\n";
			return;
		}
	}
	// dash case
	else if (word[0] == '-')
	{
		// 26 is index for blank space
		if (pRoot->next[27])
		{

			// erase the first letter
			return traverseToSearch(pRoot->next[27], word.erase(0, 1));
		}
		else
		{
			std::cout << "Word not found\n";
			return;
		}
	}
	// apostrophe case
	else if (word[0] == '\'')
	{
		// 26 is index for blank space
		if (pRoot->next[28])
		{

			// erase the first letter
		    traverseToSearch(pRoot->next[28], word.erase(0, 1));
		}
		else
		{
			std::cout << "Word not found\n";
			return;
		}
	}
	else
	{
		std::cout << "Word not found\n";
		return;
	}
}

void search(trieNode* pRoot, std::string word)
{
	if (!pRoot || word.length() == 0)
	{
		std::cout << "Word not found\n";
		return;
	}

	// convert all the letters to lowercase
	for (int i = 0; i < (int)word.length(); i++)
	{
		word[i] = tolower(word[i]);
	}

	// traverse the trie to find the word
	traverseToSearch(pRoot, word);
}

void deleteTrie(trieNode*& pRoot)
{
	if (!pRoot)
		return;
	for (int i = 0; i < 29; ++i)
	{
		deleteTrie(pRoot->next[i]);
	}
	delete pRoot;
	pRoot = nullptr;
}