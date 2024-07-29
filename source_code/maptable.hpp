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
    TableBlock** buckets = nullptr;
    size_t numBucket = 16; // Default bucket count
    size_t size = 0; // Number of elements

    // Ctor
    HashTable();
    HashTable(const size_t& x);
    HashTable(const HashTable& source);

    // Dtor
    ~HashTable();
    void deleteLL(TableBlock*& pHead);

    // Operators
    HashTable& operator=(const HashTable& source);
    void copy(const HashTable& source);

    // Basic methods
    void insert(const std::string& key);
    std::string* find(const std::string& key);
    void remove(const std::string& key);
    void clear();
    bool isEmpty();
    
    // Hashing
    size_t hash(const std::string& key);
    size_t hashFNV_1a(const std::string& s);

    // Resizing
    void rehash(const size_t& newNumBucket);
    void insert(TableBlock*& block);
};

struct MapBlock // Used for chaining in HashMap (traversing through the definitions)
{
    std::string key; // Should contain alphabetic letters only
    HashTable data; // Store words containing key in their definitions
    MapBlock* pNext = nullptr;
};

struct HashMap // Designed after unordered_map<string, unordered_set<string>>
{
    MapBlock** buckets = nullptr;
    size_t numBucket = 16; // Default bucket count
    size_t size = 0; // Number of elements

    // Ctor
    HashMap();
    HashMap(const size_t& x);

    // Dtor
    ~HashMap();
    void deleteLL(MapBlock*& pHead);

    // Basic methods
    void insert(const std::string& key, const HashTable& data);
    HashTable* find(const std::string& key);
    HashTable& access(const std::string& key); // Use this for fast access to existing or non-existing elements
    void remove(const std::string& key);
    void clear();
    bool isEmpty();
    
    // Hashing
    size_t hash(const std::string& key);
    size_t hashFNV_1a(const std::string& s);

    // Resizing
    void rehash(const size_t& newNumBucket);
    void insert(MapBlock*& block);
};

// Utility functions

bool isAlphabetic(const char& c);
std::vector<std::string> tokenize(std::string& input);
HashTable getIntersection(HashTable& t1, HashTable& t2);
std::vector<std::string> getVector(HashTable& table);
void editDefinition(std::string& word, size_t definitionNum, std::pair<std::string, std::string>& newDef, trieNode* pRoot, HashMap& invertedIndex);
void removeWord(std::string& word, trieNode*& pRoot, HashMap& invertedIndex);

// Search by definition

std::vector<std::string> searchByDef(std::string& userInput, HashMap& invertedIndex);

// Invert Index the Trie
// There are 2 overloading functions, the one with an extra boolean
// passed by reference is used in multi-threading executions,
// it provides a mechianism to control other parallel processes (animation)
void invertIndexTrie(trieNode* pRoot, HashMap& invertedIndex, bool& controlLoaded);
void invertIndexTrie(trieNode*& pRoot, HashMap& invertedIndex);


// Helper(s)

void invertIndexTrieRecursive(trieNode*& pRoot, HashMap& invertedIndex, std::string& curWord);
void removeWordRecursive(std::string& word, size_t curIndex, trieNode*& pRoot, HashMap& invertedIndex);