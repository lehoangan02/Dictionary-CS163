#pragma once

#include <string>
#include <unordered_set>
#include "trie.h"

struct TableBlock // Used for chaining in HashTable
{
    std::string data; 
    TableBlock* pNext = nullptr;
};

struct HashTable // Designed after unordered_set<string>
{
    TableBlock** buckets = nullptr;
    int numBucket = 499; // May need improvements

    // Ctor
    HashTable();
    HashTable(int x);
    HashTable(const HashTable& source);
    void copy(const HashTable& source);

    // Dtor
    ~HashTable();
    void clear();
    void deleteLL(TableBlock*& pHead);

    // Operators
    HashTable& operator=(const HashTable& source);

    // Basic method
    void insert(const std::string& key);
    TableBlock* find(const std::string& key);
    void remove(const std::string& key);
    
    // Hashing
    size_t hash(const std::string& key);
    size_t hashFNV_1a(const std::string& s);

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
    int numBucket = 499; // May need improvements

    // Ctor
    HashMap();
    HashMap(int x);

    // Dtor
    ~HashMap();
    void clear();
    void deleteLL(MapBlock*& pHead);

    // Basic methods
    void insert(const std::string& key, const HashTable& data);
    MapBlock* find(const std::string& key);
    HashTable& access(const std::string& key); // Use this for fast access to existing or non-existing elements
    void remove(const std::string& key);
    
    
    // Hashing
    size_t hash(const std::string& key);
    size_t hashFNV_1a(const std::string& s);

};

// Utility functions

bool isAlphabetic(const char& c);
std::vector<std::string> tokenize(std::string& input);
HashTable getIntersection(HashTable& t1, HashTable& t2);
std::vector<std::string> getVector(HashTable& table);

// Search by definition

std::vector<std::string> searchByDef(std::string& userInput, HashMap& invertedIndex);

// Invert Index the Trie
// There are 2 overloading functions, the one with an extra boolean
// passed by reference is used in multi-threading executions,
// it provides a mechianism to control other parallel processes (animation)
void invertIndexTrie(trieNode* pRoot, HashMap& invertedIndex, bool& controlLoaded);
void invertIndexTrie(trieNode*& pRoot, HashMap& invertedIndex);


// Helper(s)

void invertIndexTrieHelper(trieNode*& pRoot, HashMap& invertedIndex, std::string& curWord);