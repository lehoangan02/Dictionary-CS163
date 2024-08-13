#pragma once
#include <string>
#include <utility>
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>

#include "trie.h"
bool readDatasetCSV(std::string filename, TrieNode*& pRoot, std::vector<std::string>& wordFourDef);
bool readDatasetTXT(const std::string& filename, TrieNode*& pRoot, std::vector<std::string>& word4Def);