#pragma once
#include "trie.h"

// serialization of the existing trie
void serializeWrapper(trieNode* pRoot);

void serialize(trieNode* pRoot, std::ofstream& fout, std::string word);

// deserialization of the saved trie
bool deserializeWrapper(trieNode*& pRoot);

void deserialize(trieNode*& pRoot, std::ifstream& fin, std::string word);

void serializeBinary(trieNode*& pRoot, std::fstream& f, std::string word);

void deserializeBinary(trieNode*& pRoot, std::fstream& f, std::string word);