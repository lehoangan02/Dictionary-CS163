#include "maptable.hpp"

// Initialize empty HashTable, default number of buckets (linked list)
HashTable::HashTable()
{
    set = new TableBlock*[this->numBucket] {nullptr};
}

// Initialize empty HashTable, arbitary number of buckets (linked list)
HashTable::HashTable(int x) : numBucket(x)
{
    set = new TableBlock*[this->numBucket] {nullptr};
}

// Copy constructor
HashTable::HashTable(const HashTable& source)
{
    if (this != &source)
        this->copy(source);
}

HashTable::~HashTable()
{
    for (int i = 0; i < this->numBucket; ++i)
        this->deleteLL(set[i]);
    delete[] set;
    set = nullptr;
}

// Assign content from source HashTable
HashTable& HashTable::operator=(const HashTable& source)
{
    if (this != &source)
    {
        this->clear();
        delete[] set;
        this->copy(source);
    }
    return *this;
}

// Hash
int HashTable::hash(std::string& key) 
{
    int sum = 0;
    for (int i = 0; i < key.length(); ++i)
        sum += int(key[i]) - 32;
    return sum % this->numBucket;
}

// Insert an element, do NOT store duplicates
void HashTable::insert(std::string& key)
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
TableBlock* HashTable::find(std::string& key)
{
    int pos = this->hash(key);
    TableBlock* pCur = set[pos];
    while (pCur && pCur->data != key)
        pCur = pCur->pNext;
    return pCur;
}

// Remove an element, do nothing if not found
void HashTable::remove(std::string& key)
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

// Copy content of another HashTable
void HashTable::copy(const HashTable& source)
{
    numBucket = source.numBucket;
    set = new TableBlock*[source.numBucket] {nullptr};
    for (int i = 0; i < source.numBucket; ++i)
    {
        if (source.set[i])
        {
            set[i] = new TableBlock;
            set[i]->data = source.set[i]->data;
            TableBlock* pCur = set[i];
            TableBlock* pSource = source.set[i];
            while (pSource->pNext)
            {
                pCur->pNext = new TableBlock;
                pCur->pNext->data = pSource->pNext->data;
                pCur = pCur->pNext;
                pSource = pSource->pNext;
            }
        }
    }
}

// Empty HashTable
void HashTable::clear()
{
    for (int i = 0; i < this->numBucket; ++i)
        this->deleteLL(set[i]);
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

// Initialize empty HashMap, default number of buckets (linked list)
HashMap::HashMap()
{
    map = new MapBlock*[this->numBucket] {nullptr};
}

// Initialize empty HashMap, arbitary number of buckets (linked list)
HashMap::HashMap(int x) : numBucket(x)
{
    map = new MapBlock*[this->numBucket] {nullptr};
}

HashMap::~HashMap()
{
    for (int i = 0; i < this->numBucket; ++i)
    {
        this->deleteLL(map[i]);
    }
    delete[] map;
    map = nullptr;
}

int HashMap::hash(std::string& key) // May be adjusted
{
    int sum = 0;
    for (int i = 0; i < key.length(); ++i)
        sum += int(tolower(key[i])) - 97;
    return sum % this->numBucket;
}

// Maps a HashTable based on associating key, do NOT store duplicate keys
void HashMap::insert(std::string& key, HashTable& data)
{
    if (this->find(key))
        return;
    int pos = this->hash(key);
    MapBlock* pNew = new MapBlock;
    pNew->key = key;
    pNew->data = data;
    pNew->pNext = map[pos];
    map[pos] = pNew; 
}

// Return pointer to MapBlock of given key
// Return nullptr if not found
MapBlock* HashMap::find(std::string& key)
{
    int pos = this->hash(key);
    MapBlock* pCur = map[pos];
    while (pCur && pCur->key != key)
        pCur = pCur->pNext;
    return pCur;
}

// Direct access to both existing and non-existing data of given key
// If key not found, create entry of said key with empty data
HashTable& HashMap::access(std::string& key)
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
void HashMap::remove(std::string& key)
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

// Check if character is alphabetic
bool isAlphabetic(char c)
{
    return ((c > 64 && c < 91) || (c > 96 && c < 123));
}

// Tokenize a long string (tokens are separated by non-alphabetic characters)
std::vector<std::string> tokenize(std::string& input)
{
    std::vector<std::string> res;
    int head = 0, tail = 0;
    int l = input.length();
    while (tail < l)
    {
        if (isAlphabetic(input[tail]))
            ++tail;
        else
        {
            if (head != tail)
            {
                res.push_back(input.substr(head, tail - head));
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
        res.push_back(input.substr(head, l - head));
    return res;
}

// Returns the intersection of 2 HashTables (elements that are in both tables)
HashTable getIntersection(HashTable& t1, HashTable& t2)
{
    HashTable res;
    for (int i = 0; i < t2.numBucket; ++i)
    {
        TableBlock* pCur = t2.set[i];
        while (pCur)
        {
            if (t1.find(pCur->data))
                res.insert(pCur->data);
            pCur = pCur->pNext;
        }
    }
    return res;
}

// Search key words by definition
HashTable searchByDef(std::string& userInput, HashMap& invertedIndex)
{
    // Tokenize user's input
    std::vector<std::string> tokens = tokenize(userInput);

    // Find all words containing tokens in their definition
    HashTable res = invertedIndex.access(tokens[0]);
    for (int i = 1; i < tokens.size(); ++i)
        res = getIntersection(res, invertedIndex.access(tokens[i]));
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