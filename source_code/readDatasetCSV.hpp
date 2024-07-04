#pragma once
#include <string>
#include <utility>
#include <fstream>
#include <sstream>
#include <iostream>

#include "trie.h"
bool readDatasetCSV(std::string filename, trieNode*& pRoot);
bool readDatasetTXT(const std::string& filename, trieNode*& pRoot);