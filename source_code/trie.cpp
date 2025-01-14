#include <iostream>
#include <vector>
#include <string>
#include <cctype>
#include <algorithm>
#include <random>
#include <ctime>
#include <unordered_set>
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

void Change2Uppercase(std::string& word)
{
	// Check if the string is empty before transforming
	if (!word.empty()) 
	{
		std::transform(word.begin(), word.end(), word.begin(),
			[](unsigned char c) { return std::toupper(c); });
	}
}

bool checkingExistance(std::string s1, std::string s2)
{
	if (s1.size() != s2.size()) return false;
	for (int i = 0; i < (int)s1.size(); ++i)
	{
		if (s1[i] != s2[i]) return false;
	}
	return true;
}

/// @brief the original insert function (it's still needed), you should not use this in instance.cpp
/// @param pRoot 
/// @param word 
/// @param definitions 
void insert(TrieNode*& pRoot, std::string word, std::vector<std::pair<std::string, std::string>> definitions)
{
	if (word.empty()) return;
	if (!pRoot)
	{
		pRoot = new TrieNode();
	}
	TrieNode* cur = pRoot;
	for (auto c : word)
	{
		cur->countchildren++;

		if (!cur->childNode[int(c) - 32])
		{
			TrieNode* newNode = new TrieNode();
			cur->childNode[int(c) - 32] = newNode;
		}
		
		cur = cur->childNode[int(c) - 32];
	}

	if (cur->wordExisted) revertCountChildren(pRoot, word);
	else cur->wordExisted = true;

	for (auto mean : definitions)
	{
		// Change2Lowercase(mean.first);
		// Change2Lowercase(mean.second);
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
/// @brief the new insert function, you should use this in instance.cpp
void insert(TrieNode*& pRoot, std::string& word, const std::string& pos, const std::string& def, std::vector<std::string>& word4Def)
{
	if (word.empty()) return;
	if (!pRoot) {
		pRoot = new TrieNode();
	}

	TrieNode* cur = pRoot;
	for (auto c : word) {
		cur->countchildren++;

		if (!cur->childNode[int(c) - 32]) {
			cur->childNode[int(c) - 32] = new TrieNode();
		}
		
		cur = cur->childNode[int(c) - 32];
	}

	if (cur->wordExisted) revertCountChildren(pRoot, word);
	else cur->wordExisted = true;

	bool checkexist = false;
	for (auto& means : cur->definitions) {
		if (means.first == pos && means.second == def) {
			checkexist = true;
			break;
		}
	}

	if (!checkexist) cur->definitions.push_back({ pos, def });

	if (shouldAddToWord4Def(word4Def, word, pRoot)) {
		word4Def.push_back(word);
	}
}

bool shouldAddToWord4Def(const std::vector<std::string>& word4Def, const std::string& word, TrieNode* pRoot) {
	return traverseToSearch(pRoot, word).size() >= 4 && (word4Def.empty() || word4Def.back() != word);
}

void revertCountChildren(TrieNode*& pRoot, std::string word)
{
	TrieNode* cur = pRoot;
	for (auto c : word) {
		cur->countchildren--;
		cur = cur->childNode[int(c) - 32];
	}
}

std::vector<std::pair<std::string, std::string>> traverseToSearch(TrieNode* pRoot, std::string word)
{
	std::vector<std::pair<std::string, std::string>> blankVec;
	if (!pRoot)
	{
		return blankVec;
	}
	// base case
	if (word.length() == 0 && pRoot->wordExisted)
	{
		return pRoot->definitions;
	}

	// letters case
	if (word[0] >= 32 && word[0] <= 127 && pRoot->childNode[word[0] - 32])
	{
		// if the childNode pointer of that letter is not null, continue traversing
		pRoot = pRoot->childNode[word[0] - 32];
		return traverseToSearch(pRoot, word.erase(0, 1));
	}
	return blankVec;
}

std::vector<std::pair<std::string, std::string>> Search(TrieNode* pRoot, std::string word) {
	std::vector<std::pair<std::string, std::string>> collectionLast;
	std::vector<std::pair<std::string, std::string>> collection1, collection2, collection3;
	if (!pRoot || word.empty()) {
		// std::cout << "Word not found\n";
		return collectionLast;
	}
	return traverseToSearch(pRoot, word);
	{
	}

	return collectionLast;
}

//checking whether a TrieNode a leaf node
bool isLeaf(TrieNode* pRoot)
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
void RemoveAWord(TrieNode*& pRoot, std::string word)
{
	//base case
	if (!pRoot)
		return;
	if (word.size() == 0)  
	{
		if (pRoot->wordExisted) 
		{
			pRoot->wordExisted = false;
			pRoot->definitions.clear();

			//check whether it is the last node (delete) or prefix for other words.
			if (!isLeaf(pRoot))
			{
				delete pRoot;
				pRoot = nullptr;
			}
		}
		return;
	}

	int indexNext = int(word[0]) - 32;
	RemoveAWord(pRoot->childNode[indexNext], word.erase(0, 1));
	pRoot->countchildren--;
	if (isLeaf(pRoot) && !pRoot->wordExisted)
	{
		delete pRoot;
		pRoot = nullptr;
	}
}

//delete the whole tree
void deleteWholeTrie(TrieNode*& pRoot)
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
std::pair<TrieNode*, std::string> findtheKthword(TrieNode* pRoot, int k)
{
	if (!pRoot) return std::pair<TrieNode*, std::string>(nullptr, "");

	// If k == 0 and current node has a word, return the current node
	if (k == 0 && pRoot->wordExisted) return std::pair<TrieNode*, std::string>(pRoot, "");

	std::pair<TrieNode*, std::string> here;
	int S = 0, t = 0;

	for (int i = 0; i < 96; i++) // Assuming 96 possible characters (e.g., from space to tilde in ASCII)
	{
		if (!pRoot->childNode[i]) continue;

		// If child node exists and it represents a word, set t to 1
		t = pRoot->childNode[i]->wordExisted ? 1 : 0;

		// Check if k is within the range of this child node's subtree
		if (k <= S + t + pRoot->childNode[i]->countchildren)
		{
			// Recursively find the k-th word in the child node
			here = findtheKthword(pRoot->childNode[i], k - S - t);

			if (here.first)
			{
				// Prepend the character corresponding to the current child node to the result
				here.second = char(i + 32) + here.second;
				return here;
			}
		}
		else
		{
			// Move to the next child node and adjust S accordingly
			S += t + pRoot->childNode[i]->countchildren;
		}
	}

	return std::pair<TrieNode*, std::string>(nullptr, "");
}

//9. Users can visit a randomly new word generated by us, return the node and the string
std::pair<TrieNode*, std::string> pickarandomword(TrieNode* pRoot)
{
    if (!pRoot) return std::pair<TrieNode*, std::string> {nullptr, ""};
	std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> dist(1,pRoot->countchildren);
	int k = int(dist(rng)); printf("%d\n", k);
	return findtheKthword(pRoot, k);
}

//Utility function for suggesting some existing words based on some first given characters.
std::vector <std::string> SuggestingWords(std::string word, TrieNode* pRoot)
{
	// std::vector<std::string> collection{ "" };
	std::vector<std::string> collection;
	collection.clear();
	if (word.empty() || !pRoot) return collection;

	TrieNode* cur = pRoot;
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
			std::cout << "Word does not exist!" << std::endl;
			return collection;
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
	SuggestHelper(word, cur, count, collection);
	for (auto& x : collection) { //Displaying the suggestions [DEBUG]
		std::cout << x << std::endl;
	}
	return collection;
}

void SuggestHelper(std::string prefix, TrieNode* pRoot, int& count, std::vector<std::string>& collection)
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

int getDefLength(std::string& word, TrieNode*& pRoot)
{
	std::vector<std::pair<std::string, std::string>> defVec = traverseToSearch(pRoot, word);
	
	if (defVec.size() == 0)
		return -1;

	size_t sumLength = 0;

	for (size_t i = 0; i < defVec.size(); ++i)
		sumLength += defVec[i].second.length();

	return sumLength / defVec.size();
}

void sortByDefLength(std::vector<std::string>& keyWords, TrieNode*& pRoot)
{
	if (keyWords.size() > 0)
	{
		size_t size = keyWords.size();
		std::vector<int> defLength(size);

		for (size_t i = 0; i < size; ++i)
			defLength[i] = getDefLength(keyWords[i], pRoot);

		mergeSort(keyWords, 0, size - 1, defLength);
	}
}

void mergeSort(std::vector<std::string>& words, size_t left, size_t right, std::vector<int>& compareVal) 
{
    if (left < right) 
	{
        size_t mid = (left + right) / 2;
		
        mergeSort(words, left, mid, compareVal);
        mergeSort(words, mid + 1, right, compareVal);

        merge(words, left, mid, right, compareVal);
    }
}

void merge(std::vector<std::string>& words, size_t left, size_t mid, size_t right, std::vector<int>& compareVal) 
{
	size_t sizeLeft = mid - left + 1;
	size_t sizeRight = right - mid;

	std::vector<std::string> leftVec(sizeLeft);
	std::vector<std::string> rightVec(sizeRight);

	std::vector<int> compareValLeft(sizeLeft);
	std::vector<int> compareValRight(sizeRight);

	for (size_t i = 0; i < sizeLeft; ++i)
	{
		leftVec[i] = words[left + i];
		compareValLeft[i] = compareVal[left + i];
	}
	for (size_t i = 0; i < sizeRight; ++i)
	{
		rightVec[i] = words[mid + 1 + i];
		compareValRight[i] = compareVal[mid + 1 + i];
	}

	size_t curPosLeft = 0, curPosRight = 0;
	size_t curPos = left;

	while (curPosLeft < sizeLeft && curPosRight < sizeRight) 
	{
		if (compareValLeft[curPosLeft] < compareValRight[curPosRight])
		{
			words[curPos] = leftVec[curPosLeft];
			compareVal[curPos] = compareValLeft[curPosLeft];
			++curPosLeft;
		} 
		else 
		{
			words[curPos] = rightVec[curPosRight];
			compareVal[curPos] = compareValRight[curPosRight];
			++curPosRight;
		}
		++curPos;
	}

	while (curPosLeft < sizeLeft) 
	{
		words[curPos] = leftVec[curPosLeft];
		compareVal[curPos] = compareValLeft[curPosLeft];
		++curPosLeft;
		++curPos;
	}

	while (curPosRight < sizeRight) 
	{
		words[curPos] = rightVec[curPosRight];
		compareVal[curPos] = compareValRight[curPosRight];
		++curPosRight;
		++curPos;
	}
}

std::string randomWord4Def(std::vector<std::string> &word4Def)
{
    if (word4Def.size() == 0)
        return "NO WORD";
	// generate a random number
	std::random_device dev;
	std::mt19937 rng(dev());
	std::uniform_int_distribution<std::mt19937::result_type> dist(0, word4Def.size() - 1);
	int random_number = dist(rng);
    std::cout << "[DEBUG] word number:" << random_number << std::endl;
	std::string word = word4Def[random_number];
	// will return the vector of definitions if found, or else return a blank vector (maybe the word has been deleted)
	return word;
}

bool CheckWords(const std::string& word1, const std::string& word2)
{
	return word1.compare(word2); //if correct return 0
}

//The app can provide a random definition with four keywords, and users choose the correct word.
void RandomDef(TrieNode* pRoot, std::unordered_set<std::string>& WordList, std::pair<TrieNode*, std::string>& rdword) 
{
	rdword = pickarandomword(pRoot);
	WordList.insert(rdword.second);
	while (WordList.size() != 4)
	{
		std::random_device dev;
		std::mt19937 rng(dev());
		std::uniform_int_distribution<std::mt19937::result_type> dist(1, pRoot->countchildren);
		if (int(dist(rng)) != rdword.first->countchildren)
		{
			WordList.insert(findtheKthword(pRoot, int(dist(rng))).second);
		}
	}
}

bool correction(std::string& correctWord, TrieNode*& pRoot)
{
	if (correctWord.empty()) return false;

	// case 1: all lowercase
	Change2Lowercase(correctWord);

	if (traverseToSearch(pRoot, correctWord).size() > 0) // has definitions
		return true;

	// case 2: first capital letter
	correctWord[0] = toupper(correctWord[0]);
	if (traverseToSearch(pRoot, correctWord).size() > 0) // has definitions
		return true;

	// case 3: camel case
	for (unsigned long i = 0; i < correctWord.size() - 1; i++)
	{
		if (correctWord[i] == ' ')
		{
			correctWord[i + 1] = toupper(correctWord[i + 1]);
		}
	}

	if (traverseToSearch(pRoot, correctWord).size() > 0) // has definitions
		return true;

	return false;
}