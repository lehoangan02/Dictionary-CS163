#pragma once

#include <iostream>
#include <limits>
#include "trie.h"

void serializeWrapper(trieNode* pRoot);
void serialize(trieNode* pRoot, std::ofstream& fout, std::string word);
void serializeBinaryWrapper(trieNode* pRoot);
void serializeBinary(trieNode* pRoot, std::fstream& f, std::string& word);

bool deserializeWrapper(trieNode*& pRoot);
void deserialize(trieNode*& pRoot, std::ifstream& fin, std::string word);
bool deserializeBinaryWrapper(trieNode*& pRoot, std::vector<std::string>& word4Def);
void deserializeBinary(trieNode*& pRoot, std::fstream& f, std::string& word, std::vector<std::string>& word4Def);