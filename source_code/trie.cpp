#include <iostream>
#include <vector>
#include <string>
#include <cctype>
#include <algorithm>
#include <random>
#include "trie.h"

void Change2Lowercase(std::string& word)
{
	// Check if the string is empty before transforming
	if (!word.empty()) 
	{
		std::transform(word.begin(), word.end(), word.begin(),
			[](unsigned char c) { return std::tolower(c); });
	}
}

bool checkingExistance(std::string s1, std::string s2)
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
	cur->countchildren++;
	for (auto c : word)
	{
		if (!cur->childNode[int(c) - 32])
		{
			trieNode* newNode = new trieNode();
			cur->childNode[int(c) - 32] = newNode;
		}
		cur->countchildren++;
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
			if (checkingExistance(x.first, mean.first) && checkingExistance(x.second, mean.second))
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

std::vector<std::pair<std::string, std::string>> traverseToSearch(trieNode* pRoot, std::string word)
{
	std::vector<std::pair<std::string, std::string>> blankVec;
	if (!pRoot) 
	{
		std::cout << "Word not found\n";
		return blankVec;
	}
	// base case
	if (word.length() == 0)
	{
		if (pRoot->wordExisted)
		{
			std::cout << "Here are the definitions of the word: \n";
			for (int i = 0; i < (int)pRoot->definitions.size(); i++)
			{
				std::cout << i + 1 << " (" << pRoot->definitions[i].first << ") ";
				std::cout << pRoot->definitions[i].second << std::endl;
			}
			return pRoot->definitions;
		}
		else
		{
			std::cout << "Word not found\n";
			return blankVec;
		}
	}

	// letters case
	if (word[0] >= 32 && word[0] <= 127)
	{

		// if the childNode pointer of that letter is not null, continue traversing
		if (pRoot->childNode[word[0] - 32])
		{

			// erase the first letter
			return traverseToSearch(pRoot->childNode[word[0] - 32], word.erase(0, 1));
		}
		else
		{
			std::cout << "Word not found\n";
			return blankVec;
		}
	}
	return blankVec;
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

//checking whether a trieNode a leaf node
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

//7. Users can remove a word from the dictionary.
void RemoveAWord(trieNode*& pRoot, std::string word)
{
	//base case
	if (!pRoot)
		return;
	if (word.size() == 0)  {
		if (pRoot->wordExisted) {
			pRoot->wordExisted = false;
			pRoot->definitions.clear();

			//check whether it is the last node (delete) or prefix for other words.
			if (!isLeaf(pRoot)) {
				delete pRoot;
				pRoot = nullptr;
			}
		}
		return;
	}

	int indexNext = tolower(word[0]) - 32;
	RemoveAWord(pRoot->childNode[indexNext], word.erase(0, 1));
	pRoot->countchildren--;
	if (isLeaf(pRoot) && !pRoot->wordExisted)
	{
		delete pRoot;
		pRoot = nullptr;
	}
}

//delete the whole tree
void deleteWholeTrie(trieNode*& pRoot)
{
	if (!pRoot)
		return;
	for (int i = 0; i < ascii; ++i)
	{
		deleteWholeTrie(pRoot->childNode[i]);
	} //update
	delete pRoot;
	pRoot = nullptr;
}

// serialization of the existing trie
void serializeWrapper(trieNode* pRoot)
{
	std::ofstream fout; fout.open("serialized.txt");
	serialize(pRoot, fout, "");
}
void serialize(trieNode* pRoot, std::ofstream& fout, std::string word)
{
	if (!pRoot)
	{ 
		fout << "-1\n";
		std::cout << "[DEBUG] -1\n";
		return;
	}
	fout << pRoot -> wordExisted << std::endl;
	fout << "[DEBUG] " << word << std::endl;
	fout << pRoot -> definitions.size() << std::endl;
	for (int i = 0; i < (int)(pRoot -> definitions.size()); ++i)
	{
		fout << pRoot -> definitions[i].first << std::endl;
		fout << pRoot -> definitions[i].second << std::endl;
	}
	for (int i = 0; i < 96; ++i)
	{
		int asciiVal = i + 32;
		std::string newWord = word + (char)asciiVal;
		std::cout << "[DEBUG] new word is " << newWord << std::endl;
		serialize(pRoot -> childNode[i], fout, newWord);
	}
	return;
}

// deserialization of the saved trie
bool deserializeWrapper(trieNode*& pRoot)
{
	deleteWholeTrie(pRoot);
	std::ifstream fin; fin.open("serialized.txt");
    if (fin.is_open() == false)
    {
        std::cout << "[DEBUG] no file found to deserialize!\n";
        return false;
    }
	deserialize(pRoot, fin, "");
    return true;
}
void deserialize(trieNode*& pRoot, std::ifstream& fin, std::string word)
{
	int temp = 0;
	fin >> temp;
	fin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	if (temp == -1)
	{
		std::cout << "[DEBUG] empty node\n";
		pRoot = nullptr;
		return;
	}
	pRoot = new trieNode;
	pRoot -> wordExisted = temp;
	std::string tempString = "";
	std::getline(fin, tempString);
	std::cout << "[DEBUG] word is: " << tempString << std::endl;
	int size = 0;
	fin >> size;
	fin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	std::vector<std::pair<std::string, std::string>> definitionVec;
	for (int i = 0; i < size; ++i)
	{
		std::string POS = "";
		std::string description = "";
		std::getline(fin, POS);
		std::getline(fin, description);
		definitionVec.push_back(std::pair<std::string, std::string>{POS, description});
		std::cout << "[DEBUG] POS: " << POS << " - definition: " << description << std::endl;
	}
	pRoot -> definitions = definitionVec;
	for (int i = 0; i < 96; ++i)
	{
		std::string newWord = word + (char)(i + 32);
		std::cout << "[DEBUG] probing " << newWord << std::endl;
		deserialize(pRoot -> childNode[i], fin, newWord);
	}
}

//9. Users can visit a randomly new word generated by us
trieNode* findtheKthword(trieNode* pRoot, int k)
{
	if (k == 1)
	{
		if (pRoot->wordExisted) return pRoot;
	}
	int S = 0;
	for (trieNode* c: pRoot->childNode)
	{
		if (!c) continue;
		if (S + c->countchildren + 1 < k) S += c->countchildren + 1;
		else return findtheKthword(c, k - S - 1);
	}
    return nullptr;
}

trieNode* pickarandomword(trieNode* pRoot)
{
	std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> dist(1,pRoot->countchildren);
	return findtheKthword(pRoot, int(dist(rng)));
}
