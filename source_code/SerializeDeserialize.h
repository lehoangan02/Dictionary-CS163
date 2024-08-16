#pragma once

#include <iostream>
#include <limits>
#include <atomic>
#include "trie.h"

void serializeWrapper(TrieNode* pRoot);
void serialize(TrieNode* pRoot, std::ofstream& fout, std::string word);
void serializeBinaryWrapper(TrieNode* pRoot, const int& fileNum);
void serializeBinary(TrieNode* pRoot, std::fstream& f, std::string& word);

bool deserializeWrapper(TrieNode*& pRoot);
void deserialize(TrieNode*& pRoot, std::ifstream& fin, std::string word);
bool deserializeBinaryWrapper(TrieNode*& pRoot, std::vector<std::string>& word4Def, const int& fileNum);
void deserializeBinary(TrieNode*& pRoot, std::fstream& f, std::string& word, std::vector<std::string>& word4Def);

// For multithreading
bool deserializeBinaryThread(TrieNode*& pRoot, std::vector<std::string>& word4Def, const int& fileNum, std::atomic<bool>& finished);
void serializeBinaryThread(TrieNode* pRoot, const int& fileNum, std::atomic<bool>& finished);