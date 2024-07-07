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
    int numBucket = 251; // May need improvements

    // Ctor

    HashTable();
    HashTable(int x);
    HashTable(const HashTable& source);

    // Dtor

    ~HashTable();

    // Operators

    HashTable& operator=(const HashTable& source);

    // Basic methods

    void insert(const std::string& key);
    TableBlock* find(const std::string& key);
    void remove(const std::string& key);
    void clear();

    // Hashing

    size_t hash(const std::string& key);
    size_t hashFNV_1a(const std::string& s);

    // Helper(s)

    void copy(const HashTable& source);
    void deleteLL(TableBlock*& pHead);
};

struct MapBlock // Used for chaining in HashMap
{
    std::string key; // Should contain alphabetic letters only
    HashTable data; // Store words containing key in their definition
    MapBlock* pNext = nullptr;
};

struct HashMap // Designed after unordered_map<string, unordered_set<string>>
{
    MapBlock** map = nullptr;
    int numBucket = 251; // May need improvements

    // Ctor

    HashMap();
    HashMap(int x);

    // Dtor

    ~HashMap();

    // Basic methods

    void insert(const std::string& key, const HashTable& data);
    MapBlock* find(const std::string& key);
    HashTable& access(const std::string& key); // Use this for fast access to existing or non-existing elements
    void remove(const std::string& key);
    void clear();

    // Hashing

    size_t hash(const std::string& key);
    size_t hashFNV_1a(const std::string& s);

    // Helper(s)

    void deleteLL(MapBlock*& pHead);
};

// Utility functions

bool isAlphabetic(char c);
std::vector<std::string> tokenize(std::string& input);
HashTable getIntersection(HashTable& t1, HashTable& t2);
HashTable searchByDef(std::string& userInput, HashMap& invertedIndex);

// Invert Index the Trie

void invertIndexTrie(trieNode* pRoot, HashMap& map);

// Helper(s)

void invertIndexTrieHelper(trieNode* pRoot, HashMap& map, std::string curWord);