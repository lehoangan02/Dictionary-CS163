#pragma once
#include <string>
#include <utility>
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>
#include <atomic>

#include "trie.h"

bool readDatasetCSV(const std::string& filename, TrieNode*& pRoot, std::vector<std::string>& wordFourDef);
bool readDatasetTXT(const std::string& filename, TrieNode*& pRoot, std::vector<std::string>& word4Def);

// For multithreading
bool readDatasetCSVThread(const std::string& filename, TrieNode*& pRoot, std::vector<std::string>& wordFourDef, std::atomic<bool>& finished);
bool readDatasetTXTThread(const std::string& filename, TrieNode*& pRoot, std::vector<std::string>& word4Def, std::atomic<bool>& finished);