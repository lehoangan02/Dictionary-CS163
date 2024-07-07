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

void insert(trieNode*& pRoot, const std::string& word, const std::string& pos, const std::string& def)
{
	if (word.empty()) return;
	if (!pRoot) {
		pRoot = new trieNode();
	}

	trieNode* cur = pRoot;
	for (auto c : word) {
		if (!cur->childNode[int(c) - 32]) {
			cur->childNode[int(c) - 32] = new trieNode();
		}
		cur->countchildren++;
		cur = cur->childNode[int(c) - 32];
	}
	cur->wordExisted = true;

	bool checkexist = false;
	for (auto& means : cur->definitions) {
		if (means.first == pos && means.second == def) {
			checkexist = true;
			break;
		}
	}

	if (!checkexist) cur->definitions.push_back({ pos, def });
}

std::vector<std::pair<std::string, std::string>> traverseToSearch(trieNode* pRoot, std::string word)
{
	std::vector<std::pair<std::string, std::string>> blankVec;
	if (!pRoot)
	{
		return blankVec;
	}
	// base case
	if (word.length() == 0)
	{
		if (pRoot->wordExisted)
		{
			// std::cout << "Here are the definitions of the word: \n";
			for (int i = 0; i < (int)pRoot->definitions.size(); i++)
			{
				// std::cout << i + 1 << " (" << pRoot->definitions[i].first << ") ";
				// std::cout << pRoot->definitions[i].second << std::endl;
			}
			return pRoot->definitions;
		}
		else
		{
			return pRoot->definitions;
		}
	}

	// letters case
	if (word[0] >= 32 && word[0] <= 127)
	{

		// if the childNode pointer of that letter is not null, continue traversing
		if (pRoot->childNode[word[0] - 32])
		{
			// std::cout << "[DEBUG] going into " << word[0] << std::endl;
			// erase the first letter
			pRoot = pRoot->childNode[word[0] - 32];
			return traverseToSearch(pRoot, word.erase(0, 1));
		}
		else
		{
			return pRoot->definitions;
		}
	}
	return blankVec;
}

std::vector<std::pair<std::string, std::string>> Search(trieNode* pRoot, std::string word) {
	std::vector<std::pair<std::string, std::string>> collectionLast;
	std::vector<std::pair<std::string, std::string>> collection1, collection2;

	if (!pRoot || word.empty()) {
		std::cout << "Word not found\n";
		return collectionLast;
	}

	std::cout << "Here are the definitions of the word: \n";

	//first, updating the word to have characters (lowercase) which locate after blankspace and at first to uppercase 
	int length = word.length();
	for (int i = 0; i < length; ++i) {
		if ((i == 0 || (i - 1 >= 0 && word[i - 1] == ' ')) && std::islower(word[i])) {
			word[i] -= 32;
		}
	}
	// Traverse the trie to find the word (the first letter in capital form)
	collection1 = traverseToSearch(pRoot, word);
	
	// Convert all the letters to lowercase
	Change2Lowercase(word);

	// Traverse the trie to find the word (the first letter in lowercase)
	collection2 = traverseToSearch(pRoot, word);

	// Merge the two collections
	collectionLast.reserve(collection1.size() + collection2.size());  // Pre-allocate memory
	collectionLast.insert(collectionLast.end(), collection1.begin(), collection1.end());
	collectionLast.insert(collectionLast.end(), collection2.begin(), collection2.end());

	return collectionLast;
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

//9. Users can view a random and its definitions
std::pair<trieNode*, std::string> findtheKthword(trieNode* pRoot, int k)
{
	if (!pRoot) return std::pair<trieNode*, std::string>(nullptr, "");
	if (k == 0 && pRoot->wordExisted) return std::pair<trieNode*, std::string>(pRoot, ""); //is this place 0 or 1, I thought if we hit a node when we count 1 then we just... take it???
	std::pair<trieNode*, std::string> here;
	int S = 0, t = 0;
	for (int i = 0; i < 96; i++)
	{
		if (!pRoot->childNode[i]) continue;
		if (pRoot->childNode[i]->wordExisted) t = 1;
		if (k <= S + t + pRoot->childNode[i]->countchildren) 
		{
			std::cout << "[DEBUG]  at k = " << k << " S = " << S << " t = " << t << " children of child = " << pRoot->childNode[i]->countchildren << std::endl;
			std::cout << "[DEBUG] going into node " << i << " k - S - t = " << k - S - t << std::endl;
			here = std::pair<trieNode*, std::string>(findtheKthword(pRoot->childNode[i], k - S - t));
			if (!here.first) here.second = "";
			else here.second = char(i + 32) + here.second;
			return here;
		}
		else
		{
			S += t + pRoot->childNode[i]->countchildren;
			t = 0;
		}
	}
	return std::pair<trieNode*, std::string>(nullptr, "");
}

//9. Users can visit a randomly new word generated by us, return the node and the string
std::pair<trieNode*, std::string> pickarandomword(trieNode* pRoot)
{
	std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> dist(1,pRoot->countchildren);
	return findtheKthword(pRoot, int(dist(rng)));
}

//Utility function for suggesting some existing words based on some first given characters.
bool SuggestingWords(std::string word, trieNode* pRoot)
{
	if (word.empty()) return false;

	trieNode* cur = pRoot;
	bool found = false;
	int wrongAttempts = 0;

	//Loop until reaching the last character of given prefix(word)
	while (!found) {
		found = true;
		cur = pRoot;

		for (char ch : word) {
			int index = ch - 32;
			if (index >= 0 && index < 96 && cur->childNode[index]) {
				cur = cur->childNode[index];
			}
			else { //if any character is not found => found = false
				found = false;
				wrongAttempts++;
				break;
			}
		}
		//After oprating two attemps (1 for all lowercase ans 2 for uppercase at first and after blankspace)
		if (wrongAttempts == 2) {
			std::cout << "Word is not exist!" << std::endl;
			return false;
		}
		//Updating the given prefix with all lowercase character to uppercase at first and after blankspace)
		if (!found) {
			int length = word.length();
			for (int i = 0; i < length; ++i) {
				if ((i == 0 || (i - 1 >= 0 && word[i - 1] == ' ')) && std::islower(word[i])) {
					word[i] -= 32;
				}
			}
		}
		else break; //if found == true
	}

	//Displaying max 10 words whose prefixes are the same with given word
	int count = 0;
	std::vector<std::string> collection;
	SuggestHelper(word, cur, count, collection);
	for (auto& x : collection) { //Displaying the suggestions [DEBUG]
		std::cout << x << std::endl;
	}
	return true;
}

void SuggestHelper(std::string prefix, trieNode* pRoot, int& count, std::vector<std::string>& collection)
{
	if (!pRoot || count == 10) return;
	if (pRoot->wordExisted) {
		collection.push_back(prefix);
		count++;
	}
	for (int i = 0; i < 96; i++) {
		if (pRoot->childNode[i]) {
			prefix += static_cast<char>(i + 32);
			SuggestHelper(prefix, pRoot->childNode[i], count, collection);
			prefix.pop_back();
		}
	}
}