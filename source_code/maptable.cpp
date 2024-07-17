#include "maptable.hpp"

// Initialize empty HashTable, default number of buckets (linked list)
HashTable::HashTable()
{
    buckets = new TableBlock*[this->numBucket] {nullptr};
}

// Initialize empty HashTable, arbitary number of buckets (linked list)
HashTable::HashTable(int x) : numBucket(x)
{
    buckets = new TableBlock*[this->numBucket] {nullptr};
}

// Custom copy constructor (Deep copy) 
HashTable::HashTable(const HashTable& source)
{
    if (this != &source) //for not copying itself
        this->copy(source);
}

//Destruction
HashTable::~HashTable()
{
    this->clear();
    delete[] buckets;
    buckets = nullptr;
}

// Assign content from source HashTable
HashTable& HashTable::operator=(const HashTable& source)
{
    if (this != &source) //self-assignment checking
    {
        this->clear(); //clear the current object's data
        delete[] buckets; //delete the current buckets array
        this->copy(source); //copy data from the source object
    }
    return *this; //return the current object for chaining
}

// Hash (for saving the position for each word in the meaning)
size_t HashTable::hash(const std::string& key) 
{
    return hashFNV_1a(key) % this->numBucket;
}

// FNV-1a hash (non-cryptographic hash function for 32-bit variant)
size_t HashTable::hashFNV_1a(const std::string& s) 
{
    const size_t fnvPrime = 0x1000193;
    size_t hash = 0x811C9DC5;
   
    for (char c : s) 
    {
        hash ^= static_cast<size_t>(c); //XOR operation (hash XOR byte_of_data)
        hash *= fnvPrime;
    }
    return hash;
}

// Insert an element, do NOT store duplicates
void HashTable::insert(const std::string& key) //the actual word
{
    if (this->find(key))
        return;
    auto pos = this->hash(key);
    TableBlock* pNew = new TableBlock;
    pNew->data = key;
    pNew->pNext = buckets[pos];
    buckets[pos] = pNew; 

}

// Return pointer to TableBlock containing element 'key'(word)
// Return nullptr if not found
TableBlock* HashTable::find(const std::string& key)
{
    auto pos = this->hash(key);
    TableBlock* pCur = buckets[pos];
    while (pCur && pCur->data != key)
        pCur = pCur->pNext;
    return pCur;
}

// Remove an element, do nothing if not found
void HashTable::remove(const std::string& key)
{
    auto pos = this->hash(key);
    TableBlock* pDummy = new TableBlock;
    pDummy->pNext = buckets[pos];
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
    buckets[pos] = pDummy->pNext;
    delete pDummy;
}

// Copy content of another HashTable
void HashTable::copy(const HashTable& source)
{
    numBucket = source.numBucket;
    buckets = new TableBlock*[source.numBucket] {nullptr};
    for (int i = 0; i < source.numBucket; ++i)
    {
        if (source.buckets[i])
        {
            buckets[i] = new TableBlock{ source.buckets[i]->data, nullptr };
            TableBlock* pCur = buckets[i];
            TableBlock* pSource = source.buckets[i]->pNext;
            while (pSource)
            {
                pCur->pNext = new TableBlock{ pSource->data, nullptr };
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
        this->deleteLL(buckets[i]);
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
    buckets = new MapBlock*[this->numBucket] {nullptr};
}

// Initialize empty HashMap, arbitary number of buckets (linked list)
HashMap::HashMap(int x) : numBucket(x)
{
    buckets = new MapBlock*[this->numBucket] {nullptr};
}

HashMap::~HashMap()
{
    this->clear();
    delete[] buckets;
    buckets = nullptr;
}

// Hash
size_t HashMap::hash(const std::string& key) 
{
    return hashFNV_1a(key) % this->numBucket;
}

// FNV-1a hash
size_t HashMap::hashFNV_1a(const std::string& s) 
{
    const size_t fnvPrime = 0x1000193;
    size_t hash = 0x811C9DC5;

    for (char c : s) 
    {
        hash ^= static_cast<size_t>(c);
        hash *= fnvPrime;
    }
    return hash;
}

// Maps a HashTable based on associating key, do NOT store duplicate keys
void HashMap::insert(const std::string& key, const HashTable& data) //data is actual word
{
    if (this->find(key))
        return;
    auto pos = this->hash(key);
    MapBlock* pNew = new MapBlock;
    pNew->key = key;
    pNew->data = data;
    pNew->pNext = buckets[pos];
    buckets[pos] = pNew; 
}

// Return pointer to MapBlock of given key
// Return nullptr if not found
MapBlock* HashMap::find(const std::string& key)
{
    auto pos = this->hash(key);
    MapBlock* pCur = buckets[pos];
    while (pCur && pCur->key != key)
        pCur = pCur->pNext;
    return pCur;
}

// Direct access to both existing and non-existing data of given key
// If key not found, create entry of said key with empty data
HashTable& HashMap::access(const std::string& key)
{
    MapBlock* pFind = this->find(key);
    if (pFind)
        return pFind->data;
    
    // If key doesnt exist, create entry of key with empty data
    auto pos = this->hash(key);
    MapBlock* pNew = new MapBlock;
    pNew->key = key;
    pNew->pNext = buckets[pos];
    buckets[pos] = pNew;
    return buckets[pos]->data;
}

// Remove a key and associated data
// Do nothing if not found
void HashMap::remove(const std::string& key)
{
    auto pos = this->hash(key);
    MapBlock* pDummy = new MapBlock;
    pDummy->pNext = buckets[pos];
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
    buckets[pos] = pDummy->pNext;
    delete pDummy;
}

// Empty HashMap
void HashMap::clear()
{
    for (int i = 0; i < this->numBucket; ++i)
        this->deleteLL(buckets[i]);
}

// Deallocate a bucket (linked list) in buckets
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
bool isAlphabetic(const char& c)
{
    return ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z'));
}

// Tokenize a long string (tokens are separated by non-alphabetic characters)
std::vector<std::string> tokenize(std::string& input) 
{
    std::vector<std::string> res;
    res.reserve(1000);  // Reserve space to avoid multiple allocations

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
                res.emplace_back(input.data() + head, tail - head);
                head = tail;
            }
            ++tail;
            ++head;
        }
    }
    if (head != tail) 
        res.emplace_back(input.data() + head, l - head);
    return res;
}

// Returns the intersection of 2 HashTables (elements that are in both tables)
HashTable getIntersection(HashTable& t1, HashTable& t2)
{
    HashTable res;
    for (int i = 0; i < t1.numBucket; ++i)
    {
        TableBlock* pCur = t1.buckets[i];
        while (pCur)
        {
            if (t2.find(pCur->data))
                res.insert(pCur->data);
            pCur = pCur->pNext;
        }
    }
    return res;
}

// Return vector containing all elements of HashTable 
std::vector<std::string> getVector(HashTable& table)
{
    std::vector<std::string> res;
    for (int i = 0; i < table.numBucket; ++i)
    {
        TableBlock* pCur = table.buckets[i];
        while (pCur)
        {
            res.push_back(pCur->data);
            pCur = pCur->pNext;
        }
    }
    return res;
}

// Search key words by definition
std::vector<std::string> searchByDef(std::string& userInput, HashMap& invertedIndex)
{
    // Tokenize user's input
    std::vector<std::string> tokens = tokenize(userInput);

    for (size_t i = 0; i < tokens.size(); ++i)
        Change2Lowercase(tokens[i]);

    // Find all words containing tokens in their definition
    HashTable res;
    size_t i = 0;
    MapBlock* findInit = nullptr;
    while (!findInit && i < tokens.size())
    {
        findInit = invertedIndex.find(tokens[i]);
        ++i;
    }
    if (findInit)
        res = findInit->data;
    for (; i < tokens.size(); ++i)
    {
        MapBlock* found = invertedIndex.find(tokens[i]);
        if (found)
            res = getIntersection(res, found->data);
    }
    return getVector(res);
}

void invertIndexTrie(trieNode* pRoot, HashMap& invertedIndex, bool& controlLoaded)
{
    std::string curWord;
    invertIndexTrieHelper(pRoot, invertedIndex, curWord);
    controlLoaded = true;
}
void invertIndexTrie(trieNode*& pRoot, HashMap& invertedIndex)
{
    std::string curWord;
    invertIndexTrieHelper(pRoot, invertedIndex, curWord);
}

void invertIndexTrieHelper(trieNode*& pRoot, HashMap& invertedIndex, std::string& curWord)
{
    if (!pRoot)
        return;
    if (pRoot->wordExisted)
    {
        for (auto& s : pRoot->definitions)
        {
            std::vector<std::string> tokens = tokenize(s.second);
            for (auto& t : tokens)
            {
                Change2Lowercase(t);
                invertedIndex.access(t).insert(curWord);
            }
        }
    }
    for (int i = 0; i < ascii; ++i)
    {
        curWord.push_back(static_cast<char>(i + 32));
        invertIndexTrieHelper(pRoot->childNode[i], invertedIndex, curWord);
        curWord.pop_back();
    }
}