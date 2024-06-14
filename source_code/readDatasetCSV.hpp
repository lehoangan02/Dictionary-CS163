#pragma once
#include <string>
#include <utility>
#include <fstream>
#include <sstream>

#include "trie.h"
bool readDatasetCSV(std::string filename, trieNode*& pRoot);