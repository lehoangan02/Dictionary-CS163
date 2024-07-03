#pragma once

#include <string>
#include "trie.h"

struct TableBlock // Used for chaining in HashTable
{
    std::string data; 
    TableBlock* pNext = nullptr;
};

struct HashTable // Designed after unordered_set<string>
{
    TableBlock** set = nullptr;
    int size = 127; // May need improvements

    // Ctor

    HashTable();
    HashTable(int x);
    HashTable(const HashTable& source);

    // Dtor

    ~HashTable();

    // Operators

    HashTable& operator=(const HashTable& source);

    // Basic methods

    void insert(std::string& key);
    TableBlock* find(std::string& key);
    void remove(std::string& key);

    // Hashing

    int hash(std::string& key); // May need improvements

    // Helper(s)

    void HashTable::copy(const HashTable& source);
    void HashTable::clear();
    void deleteLL(TableBlock*& pHead);
};

struct MapBlock // Used for chaining in HashMap
{
    std::string key; // Should contain alphabetic letters only
    HashTable data; // Store words containing key in their definition
    MapBlock* pNext = nullptr;
    // May need constructor
};

struct HashMap // Designed after unordered_map<string, unordered_set<string>>
{
    MapBlock** map = nullptr;
    int size = 127; // May need improvements

    // Ctor

    HashMap();
    HashMap(int x);

    // Dtor

    ~HashMap();

    // Basic methods

    void insert(std::string& key, HashTable& data);
    MapBlock* find(std::string& key);
    HashTable& access(std::string& key); // Use this for fast access to existing or non-existing elements
    void remove(std::string& key);

    // Hashing

    int hash(std::string& key); // May need improvements

    // Helper(s)

    void deleteLL(MapBlock*& pHead);
};

// Utility functions

bool isAlphabetic(char c);
std::vector<std::string> tokenize(std::string& line);

// Invert Index the Trie

void invertIndexTrie(trieNode* pRoot, HashMap& map);

// Helper(s)

void invertIndexTrieHelper(trieNode* pRoot, HashMap& map, std::string curWord);