#include <iostream>
#include <vector>
#include <string>
#include <cctype>
#include <algorithm>
#include "trie.h"

void Change2Lowercase(std::string& word)
{
	// Check if the string is empty before transforming
	if (!word.empty()) {
		std::transform(word.begin(), word.end(), word.begin(),
			[](unsigned char c) { return std::tolower(c); });
	}
}

bool Checkingexistance(std::string s1, std::string s2)
{
	if (s1.size() != s2.size()) return false;
	for (int i = 0; i < s1.size(); ++i)
	{
		if (s1[i] != s2[i]) return false;
	}
	return true;
}

void insert(trieNode*& pRoot, std::string word, std::vector<std::pair<std::string, std::string>> definitions)
{
	if (word.empty()) return;

	if (!pRoot)
	{
		pRoot = new trieNode();
	}
	Change2Lowercase(word);
	trieNode* cur = pRoot;
	for (auto c : word)
	{
		if (!cur->childNode[int(c) - 32])
		{
			trieNode* newNode = new trieNode();
			cur->childNode[int(c) - 32] = newNode;
		}
		cur = cur->childNode[int(c) - 32];
	}
	cur->wordExisted = true;

	for (auto mean : definitions)
	{
		Change2Lowercase(mean.first);
		Change2Lowercase(mean.second);
		bool check = false;
		for (auto x : cur->definitions)
		{
			//first checking whether they are the same parts of speech, and then the meaning.
			if (Checkingexistance(x.first, mean.first) && Checkingexistance(x.second, mean.second))
			{
				check = true;
				break;
			}
		}
		if (!check)
		{
			cur->definitions.push_back(mean);
		}
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

		// if the childNode pointer of that letter is not null, continue traversing
		if (pRoot->childNode[word[0] - 97])
		{

			// erase the first letter
			traverseToSearch(pRoot->childNode[word[0] - 97], word.erase(0, 1));
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
		if (pRoot->childNode[26])
		{

			// erase the first letter
			return traverseToSearch(pRoot->childNode[26], word.erase(0, 1));
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
		if (pRoot->childNode[27])
		{

			// erase the first letter
			return traverseToSearch(pRoot->childNode[27], word.erase(0, 1));
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
		if (pRoot->childNode[28])
		{

			// erase the first letter
		    traverseToSearch(pRoot->childNode[28], word.erase(0, 1));
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
	Change2Lowercase(word);

	// traverse the trie to find the word
	traverseToSearch(pRoot, word);
}

void remove(trieNode*& pRoot, std::string word)
{
	if (!pRoot)
		return;
	if (word.size() == 0)
	{
		if (pRoot->wordExisted)
		{
			if (!isLeaf(pRoot))
			{
				pRoot->wordExisted = false;
				pRoot->definitions.clear();
			}
			else
			{
				delete pRoot;
				pRoot = nullptr;
			}
		}
		return;
	}
	char head = tolower(word[0]);
	int indexNext = 0;
	if (head >= 'a' && head <= 'z')
		indexNext = head - 97;
	else if (head == ' ')
		indexNext = 26;
	else if (head == '-')
		indexNext = 27;
	else
		indexNext = 28;
	remove(pRoot->childNode[indexNext], word.erase(0, 1));
	if (isLeaf(pRoot) && !pRoot->wordExisted)
	{
		delete pRoot;
		pRoot = nullptr;
	}
}

void deleteTrie(trieNode*& pRoot)
{
	if (!pRoot)
		return;
	for (int i = 0; i < ascii; ++i)
	{
		deleteTrie(pRoot->childNode[i]);
	} //update
	delete pRoot;
	pRoot = nullptr;
}

bool isLeaf(trieNode* pRoot)
{
	if (!pRoot)
		return false;
	for (int i = 0; i < ascii; ++i)
	{
		if (pRoot->childNode[i])
			return false;
	}
	return true;
}
