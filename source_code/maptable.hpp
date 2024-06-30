#pragma once
#include <string>

struct TableBlock
{
    std::string data; // Should contain alphabet letters only
    TableBlock* pNext = nullptr;
};

struct HashTable
{
    TableBlock** set = nullptr;
    int size = 127; // May be adjusted

    // Use these
    HashTable();
    HashTable(int x);
    ~HashTable();
    int hash(std::string key); // May be adjusted
    void insert(std::string key);
    TableBlock* find(std::string key);
    void remove(std::string key);

    // Helper(s)
    void deleteLL(TableBlock*& pHead);
};

struct MapBlock
{
    std::string key;
    HashTable data;
    MapBlock* pNext = nullptr;
};

struct HashMap
{
    MapBlock** map = nullptr;
    int size = 127; // May be adjusted

    // Use these
    HashMap();
    HashMap(int x);
    ~HashMap();
    int hash(std::string key); // May be adjusted
    void insert(std::string key, HashTable data);
    MapBlock* find(std::string key);
    HashTable& access(std::string key); // Use this for fast access to existing or non-existing elements
    void remove(std::string key);

    // Helper(s)
    void deleteLL(MapBlock*& pHead);
};