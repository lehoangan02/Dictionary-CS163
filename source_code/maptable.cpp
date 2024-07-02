#include "maptable.hpp"

// Initialize empty HashTable, default size
HashTable::HashTable()
{
    set = new TableBlock*[size] {nullptr};
}

// Initialize empty HashTable, arbitary size
HashTable::HashTable(int x) : size(x)
{
    set = new TableBlock*[size] {nullptr};
}

HashTable::~HashTable()
{
    for (int i = 0; i < size; ++i)
    {
        this->deleteLL(set[i]);
    }
    delete[] set;
    set = nullptr;
}

// Hash
int HashTable::hash(std::string key) 
{
    int sum = 0;
    for (int i = 0; i < key.length(); ++i)
        sum += int(key[i]) - 32;
    return sum % size;
}

// Insert an element, do NOT store duplicates
void HashTable::insert(std::string key)
{
    if (this->find(key))
        return;
    int pos = this->hash(key);
    TableBlock* pNew = new TableBlock;
    pNew->data = key;
    pNew->pNext = set[pos];
    set[pos] = pNew; 
}

// Return pointer to TableBlock containing an element
// Return nullptr if not found
TableBlock* HashTable::find(std::string key)
{
    int pos = this->hash(key);
    TableBlock* pCur = set[pos];
    while (pCur && pCur->data != key)
        pCur = pCur->pNext;
    return pCur;
}

// Remove an element, do nothing if not found
void HashTable::remove(std::string key)
{
    int pos = this->hash(key);
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

// Deallocate a bucket (linked list) in table
void HashTable::deleteLL(TableBlock*& pHead)
{
    while (pHead)
    {
        TableBlock* pTemp = pHead->pNext;
        delete pHead;
        pHead = pTemp;
    }
}

// Initialize empty HashMap, default size
HashMap::HashMap()
{
    map = new MapBlock*[size] {nullptr};
}

// Initialize empty HashMap, arbitary size
HashMap::HashMap(int x) : size(x)
{
    map = new MapBlock*[size] {nullptr};
}

HashMap::~HashMap()
{
    for (int i = 0; i < size; ++i)
    {
        this->deleteLL(map[i]);
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

// Maps a HashTable based on associating key, do NOT store duplicate keys
void HashMap::insert(std::string key, HashTable data)
{
    if (this->find(key))
        return;
    int pos = this->hash(key);
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

// Return pointer to MapBlock of given key
// Return nullptr if not found
MapBlock* HashMap::find(std::string key)
{
    int pos = this->hash(key);
    MapBlock* pCur = map[pos];
    while (pCur && pCur->key != key)
        pCur = pCur->pNext;
    return pCur;
}

// Direct access to both existing and non-existing data of given key
// If key not found, create entry of said key with empty data
HashTable& HashMap::access(std::string key)
{
    MapBlock* pFind = this->find(key);
    if (pFind)
        return pFind->data;
    
    // If key doesnt exist, create entry of key with empty data
    int pos = this->hash(key);
    MapBlock* pNew = new MapBlock;
    pNew->key = key;
    pNew->pNext = map[pos];
    map[pos] = pNew;
    return map[pos]->data;
}

// Remove a key and associated data
// Do nothing if not found
void HashMap::remove(std::string key)
{
    int pos = this->hash(key);
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

// Deallocate a bucket (linked list) in map
void HashMap::deleteLL(MapBlock*& pHead)
{
    while (pHead)
    {
        MapBlock* pTemp = pHead->pNext;
        delete pHead;
        pHead = pTemp;
    }
}

bool isAlphabetic(char c)
{
    return ((c > 64 && c < 91) || (c > 96 && c < 123));
}

std::vector<std::string> tokenize(std::string line)
{
    std::vector<std::string> res;
    int head = 0, tail = 0;
    int l = line.length();
    while (tail < l)
    {
        if (isAlphabetic(line[tail]))
            ++tail;
        else
        {
            if (head != tail)
            {
                res.push_back(line.substr(head, tail - head));
                head = tail;
            }
            else
            {
                ++tail;
                ++head;
            }
        }
    }
    if (head != tail)
        res.push_back(line.substr(head, l - head));
    return res;
}

void invertIndexTrie(trieNode* pRoot, HashMap& map)
{
    std::string curWord;
    invertIndexTrieHelper(pRoot, map, curWord);
}

void invertIndexTrieHelper(trieNode* pRoot, HashMap& map, std::string curWord)
{
    if (!pRoot)
        return;
    if (pRoot->wordExisted)
    {
        for (auto s : pRoot->definitions)
        {
            std::vector<std::string> tokens = tokenize(s.second);
            for (auto t : tokens)
            {
                // May need to change t to lowercase
                map.access(t).insert(curWord);
            }
        }
    }
    for (int i = 0; i < ascii; ++i)
        invertIndexTrieHelper(pRoot->childNode[i], map, curWord + char(i + 32));
}