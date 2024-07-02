#pragma once

#include <string>
#include "trie.h"

struct TableBlock
{
    std::string data; 
    TableBlock* pNext = nullptr;
};

struct HashTable // Designed after unordered_set<string>
{
    TableBlock** set = nullptr;
    int size = 127; // May be adjusted

    // Use these
    HashTable();
    HashTable(int x);
    ~HashTable();
    void insert(std::string key);
    TableBlock* find(std::string key);
    void remove(std::string key);

    // Hashing
    int hash(std::string key); // May be adjusted

    // Helper(s)
    void deleteLL(TableBlock*& pHead);
};

struct MapBlock
{
    std::string key; // Should contain alphabetic letters only
    HashTable data;
    MapBlock* pNext = nullptr;
    // May need constructor
};

struct HashMap // Designed after unordered_map<string, unordered_set<string>>
{
    MapBlock** map = nullptr;
    int size = 127; // May be adjusted

    // Use these
    HashMap();
    HashMap(int x);
    ~HashMap();
    void insert(std::string key, HashTable data);
    MapBlock* find(std::string key);
    HashTable& access(std::string key); // Use this for fast access to existing or non-existing elements
    void remove(std::string key);

    // Hashing
    int hash(std::string key); // May be adjusted

    // Helper(s)
    void deleteLL(MapBlock*& pHead);
};

// Utility functions
bool isAlphabetic(char c);
std::vector<std::string> tokenize(std::string line);

// Invert Index the Trie
void invertIndexTrie(trieNode* pRoot, HashMap& map);

//Helper(s)
void invertIndexTrieHelper(trieNode* pRoot, HashMap& map, std::string curWord);