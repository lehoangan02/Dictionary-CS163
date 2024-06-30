#include "maptable.hpp"

HashTable::HashTable()
{
    set = new TableBlock*[size] {nullptr};
}

HashTable::HashTable(int x) : size(x)
{
    set = new TableBlock*[size] {nullptr};
}

HashTable::~HashTable()
{
    for (int i = 0; i < size; ++i)
    {
        deleteLL(set[i]);
    }
    delete[] set;
    set = nullptr;
}

int HashTable::hash(std::string key) // May be adjusted
{
    int sum = 0;
    for (int i = 0; i < key.length(); ++i)
        sum += int(tolower(key[i])) - 97;
    return sum % size;
}

void HashTable::insert(std::string key)
{
    if (find(key))
        return;
    int pos = hash(key);
    TableBlock* pNew = new TableBlock;
    pNew->data = key;
    pNew->pNext = set[pos];
    set[pos] = pNew; 
}

TableBlock* HashTable::find(std::string key)
{
    int pos = hash(key);
    TableBlock* pCur = set[pos];
    while (pCur && pCur->data != key)
        pCur = pCur->pNext;
    return pCur;
}

void HashTable::remove(std::string key)
{
    int pos = hash(key);
    TableBlock* pDummy = new TableBlock;
    pDummy->pNext = set[pos];
    TableBlock* pCur = pDummy;
    while (pCur->pNext)
    {
        if (pCur->pNext->data == key)
        {
            TableBlock* pTemp = pCur->pNext->pNext;
            delete pCur->pNext;
            pCur->pNext = pTemp;
        }
        else
            pCur = pCur->pNext;
    }
    set[pos] = pDummy->pNext;
    delete pDummy;
}

void HashTable::deleteLL(TableBlock*& pHead)
{
    while (pHead)
    {
        TableBlock* pTemp = pHead->pNext;
        delete pHead;
        pHead = pTemp;
    }
}

HashMap::HashMap()
{
    map = new MapBlock*[size] {nullptr};
}

HashMap::HashMap(int x) : size(x)
{
    map = new MapBlock*[size] {nullptr};
}

HashMap::~HashMap()
{
    for (int i = 0; i < size; ++i)
    {
        deleteLL(map[i]);
    }
    delete[] map;
    map = nullptr;
}

int HashMap::hash(std::string key) // May be adjusted
{
    int sum = 0;
    for (int i = 0; i < key.length(); ++i)
        sum += int(tolower(key[i])) - 97;
    return sum % size;
}

void HashMap::insert(std::string key, HashTable data)
{
    if (find(key))
        return;
    int pos = hash(key);
    MapBlock* pNew = new MapBlock;
    pNew->key = key;
    for (int i = 0; i < data.size; ++i)
    {
        TableBlock* pCur = data.set[i];
        while (pCur)
        {
            pNew->data.insert(pCur->data);
            pCur = pCur->pNext;
        }
    }
    pNew->pNext = map[pos];
    map[pos] = pNew; 
}

MapBlock* HashMap::find(std::string key)
{
    int pos = hash(key);
    MapBlock* pCur = map[pos];
    while (pCur && pCur->key != key)
        pCur = pCur->pNext;
    return pCur;
}

HashTable& HashMap::access(std::string key) // Use this for fast access to existing or non-existing elements
{
    MapBlock* pFind = find(key);
    if (pFind)
        return pFind->data;
    
    // If key doesnt exist, create entry of key with empty data
    int pos = hash(key);
    MapBlock* pNew = new MapBlock;
    pNew->key = key;
    pNew->pNext = map[pos];
    map[pos] = pNew;
    return map[pos]->data;
}

void HashMap::remove(std::string key)
{
    int pos = hash(key);
    MapBlock* pDummy = new MapBlock;
    pDummy->pNext = map[pos];
    MapBlock* pCur = pDummy;
    while (pCur->pNext)
    {
        if (pCur->pNext->key == key)
        {
            MapBlock* pTemp = pCur->pNext->pNext;
            delete pCur->pNext;
            pCur->pNext = pTemp;
        }
        else
            pCur = pCur->pNext;
    }
    map[pos] = pDummy->pNext;
    delete pDummy;
}

void HashMap::deleteLL(MapBlock*& pHead)
{
    while (pHead)
    {
        MapBlock* pTemp = pHead->pNext;
        delete pHead;
        pHead = pTemp;
    }
}