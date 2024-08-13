#include <limits>
#include "maptable.hpp"

// Initialize empty HashTable, default number of buckets (linked list)
HashTable::HashTable()
{
    buckets = new TableBlock*[this->numBucket] {nullptr};
}

// Initialize empty HashTable, arbitary number of buckets (linked list)
HashTable::HashTable(const size_t& x) : numBucket(x)
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
    if (this->buckets)
    {
        this->clear();
        delete[] buckets;
        buckets = nullptr;
    }
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
    ++this->size;
    if (this->size > this->numBucket)
        this->rehash(2 * this->numBucket);
}

// Return pointer to element 'key'(word) in HashTable
// Return nullptr if not found
const std::string* HashTable::find(const std::string& key)
{
    auto pos = this->hash(key);
    TableBlock* pCur = buckets[pos];
    while (pCur && pCur->data != key)
        pCur = pCur->pNext;
    if (!pCur)
        return nullptr;
    return &(pCur->data);
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
            --this->size;
        }
        else
            pCur = pCur->pNext;
    }
    buckets[pos] = pDummy->pNext;
    delete pDummy;
}

// Check if HashTable is empty
bool HashTable::isEmpty()
{
    return (this->size == 0);
}

// Copy content of another HashTable
void HashTable::copy(const HashTable& source)
{
    this->numBucket = source.numBucket;
    this->size = source.size;
    buckets = new TableBlock*[source.numBucket] {nullptr};
    for (size_t i = 0; i < source.numBucket; ++i)
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
    for (size_t i = 0; i < this->numBucket; ++i)
        this->deleteLL(buckets[i]);
    this->size = 0;
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

// Rehash (resize) HashTable to new numBucket, used when HashTable contains too many elements
void HashTable::rehash(const size_t& newNumBucket)
{
    if (newNumBucket <= this->numBucket)
        return;
    HashTable tempTable(newNumBucket);
    for (size_t i = 0; i < this->numBucket; ++i)
    {
        while (this->buckets[i])
        {
            TableBlock* pCurBlock = this->buckets[i];
            this->buckets[i] = this->buckets[i]->pNext;
            tempTable.insert(pCurBlock);
        }
    }
    delete[] this->buckets;
    this->buckets = tempTable.buckets;
    this->numBucket = newNumBucket;
    tempTable.buckets = nullptr;
}

// Insert a TableBlock into HashTable, only used when rehashing
void HashTable::insert(TableBlock*& block)
{
    auto pos = this->hash(block->data);
    block->pNext = this->buckets[pos];
    this->buckets[pos] = block;
}

// Initialize empty HashMap, default number of buckets (linked list)
HashMap::HashMap()
{
    buckets = new MapBlock*[this->numBucket] {nullptr};
}

// Initialize empty HashMap, arbitary number of buckets (linked list)
HashMap::HashMap(const size_t& x) : numBucket(x)
{
    buckets = new MapBlock*[this->numBucket] {nullptr};
}

HashMap::~HashMap()
{
    if (this->buckets)
    {
        this->clear();
        delete[] buckets;
        buckets = nullptr;
    }
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
    ++this->size;
    if (this->size > this->numBucket)
        this->rehash(2 * this->numBucket);
}

// Return pointer to data of given key
// Return nullptr if not found
HashTable* HashMap::find(const std::string& key)
{
    auto pos = this->hash(key);
    MapBlock* pCur = buckets[pos];
    while (pCur && pCur->key != key)
        pCur = pCur->pNext;
    if (!pCur)
        return nullptr;
    return &(pCur->data);
}

// Direct access to both existing and non-existing data of given key
// If key not found, create entry of said key with empty data
HashTable& HashMap::access(const std::string& key)
{
    HashTable* pFind = this->find(key);
    if (pFind)
        return *pFind;
    
    // If key doesnt exist, create entry of key with empty data
    auto pos = this->hash(key);
    MapBlock* pNew = new MapBlock;
    pNew->key = key;
    pNew->pNext = this->buckets[pos];
    this->buckets[pos] = pNew;
    ++this->size;
    if (this->size > this->numBucket)
        this->rehash(2 * this->numBucket);
    return pNew->data;
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
            --this->size;
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
    for (size_t i = 0; i < this->numBucket; ++i)
        this->deleteLL(buckets[i]);
    this->size = 0;
}

// Check if HashMap is empty
bool HashMap::isEmpty()
{
    return (this->size == 0);
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

// Rehash (resize) HashMap to new numBucket, used when HashMap contains too many elements
//This process involves creating a new hash table with the desired number of buckets, 
// then moving all the elements from the current hash table to the new one.
void HashMap::rehash(const size_t& newNumBucket)
{
    if (newNumBucket <= this->numBucket)
        return;
    HashMap tempMap(newNumBucket);
    for (size_t i = 0; i < this->numBucket; ++i)
    {
        while (this->buckets[i])
        {
            MapBlock* pCurBlock = this->buckets[i];
            this->buckets[i] = this->buckets[i]->pNext;
            tempMap.insert(pCurBlock);
        }
    }
    //Release the old table
    delete[] this->buckets;
    this->buckets = tempMap.buckets;
    this->numBucket = newNumBucket;
    tempMap.buckets = nullptr;
}

// Insert a MapBlock into HashMap, only used when rehashing
void HashMap::insert(MapBlock*& block)
{
    auto pos = this->hash(block->key);
    //Inserting at the head of the linked list
    block->pNext = this->buckets[pos];
    this->buckets[pos] = block;
}

// Insert word and its definition into HashMap (for Inverted Index)
void HashMap::insertWordDef(const std::string& word, const std::string& definition)
{
    std::vector<std::string> tokens = tokenize(definition);

    for (std::string& t : tokens)
    {
        Change2Lowercase(t);
        this->access(t).insert(word);
    }
}

// Remove word and its definition from HashMap (for Inverted Index)
void HashMap::removeWordDef(const std::string& word, const std::string& definition)
{
    std::vector<std::string> tokens = tokenize(definition);

    for (std::string& t : tokens)
    {
        Change2Lowercase(t);
        HashTable* find = this->find(t);
        if (find)
        {
            find->remove(word);
            if (find->isEmpty())
                this->remove(t);
        }
    }
}

// Check if character is alphabetic
bool isAlphabetic(const char& c)
{
    return ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z'));
}

// Tokenize a long string (tokens are separated by non-alphabetic characters)
std::vector<std::string> tokenize(const std::string& input) 
{
    std::vector<std::string> res;
    res.reserve(1000);  // Reserve space to avoid multiple allocations

    size_t head = 0, tail = 0;
    size_t l = input.length();

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
    for (size_t i = 0; i < t1.numBucket; ++i)
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
    for (size_t i = 0; i < table.numBucket; ++i)
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
std::vector<std::string> searchByDef(std::vector<std::string> tokens, HashMap& invertedIndex)
{
    for (size_t i = 0; i < tokens.size(); ++i)
        Change2Lowercase(tokens[i]);

    // Find all words containing tokens in their definition
    HashTable res;
    HashTable* findInit = nullptr;
    size_t i = 0;

    while (!findInit && i < tokens.size())
    {
        findInit = invertedIndex.find(tokens[i]);
        ++i;
    }

    if (findInit)
        res = *findInit;

    for (; i < tokens.size(); ++i)
    {
        HashTable* found = invertedIndex.find(tokens[i]);

        if (found)
        {
            HashTable intersect = getIntersection(res, *found);

            if (!intersect.isEmpty())
                res = intersect;
        }
    }

    return getVector(res);
}

std::string sortBySumPosition(trieNode* pRoot, const std::vector<std::string>& LengthSort, const std::vector<std::string>& InputTokens) {
    int size = LengthSort.size();
    std::string top = LengthSort[0];
    int min = std::numeric_limits<int>::max(); // Use maximum int value for clarity

    for (int i = 0; i < size; ++i) { //for every element in vector after operating lengthsort
        std::vector<std::pair<std::string, std::string>> temp = traverseToSearch(pRoot, LengthSort[i]);
        int minCount = std::numeric_limits<int>::max(); // Use maximum int value for clarity
        bool allTokensPresent = false;

        for (const auto& pair : temp) { //for every definition in defvec of words
            std::vector<std::string> tempVec = tokenize(pair.second);
            int countdist = 0;
            int num = 0;

            // Check if all tokens are present
            for (auto token : InputTokens) { //for every token in InputTokens
                bool found = false; //used for checking existance of each token in temp[i].second
                for (int j = 0; j < tempVec.size(); ++j) {
                    std::string temptoken = token;
                    if (temptoken[0] > 'a' && temptoken[0] < 'z') temptoken[0] -= 32;
                    if (tempVec[j] == token || tempVec[j] == temptoken) {
                        countdist += j;
                        found = true;
                        break; // Stop searching for this token once found
                    }
                }
                if (!found) {
                    countdist = std::numeric_limits<int>::max(); // Invalidate this option
                    break;
                }
            }

            // If all tokens are found, consider this candidate
            if (countdist < minCount) {
                minCount = countdist;
                allTokensPresent = true;
            }
        }

        // Update top if this is the best valid candidate
        if (allTokensPresent && minCount < min) {
            min = minCount;
            top = LengthSort[i];
        }
    }

    return top;
}

void invertIndexTrie(trieNode* pRoot, HashMap& invertedIndex, bool& controlLoaded)
{
    std::string curWord;
    invertIndexTrieRecursive(pRoot, invertedIndex, curWord);
    controlLoaded = true;
}
void invertIndexTrie(trieNode*& pRoot, HashMap& invertedIndex)
{
    std::string curWord;
    invertIndexTrieRecursive(pRoot, invertedIndex, curWord);
}

void invertIndexTrieRecursive(trieNode*& pRoot, HashMap& invertedIndex, std::string& curWord)
{
    if (!pRoot)
        return;

    if (pRoot->wordExisted)
    {
        for (auto& s : pRoot->definitions)
            invertedIndex.insertWordDef(curWord, s.second);
    }

    for (int i = 0; i < ascii; ++i)
    {
        curWord.push_back(static_cast<char>(i + 32));
        invertIndexTrieRecursive(pRoot->childNode[i], invertedIndex, curWord);
        curWord.pop_back();
    }
}

bool editDefinition(std::string& word, size_t definitionNum, std::pair<std::string, std::string>& newDef, trieNode* pRoot, HashMap& invertedIndex)
{
    size_t i = 0;
    while (i < word.length())
    {
        if (!pRoot)
            return false;
        int indexNext = static_cast<int>(word[i]) - 32;
        pRoot = pRoot->childNode[indexNext];
        ++i;
    }
    if (pRoot->wordExisted && definitionNum < pRoot->definitions.size())
    {
        invertedIndex.removeWordDef(word, pRoot->definitions[definitionNum].second);
        invertedIndex.insertWordDef(word, newDef.second);

        pRoot->definitions[definitionNum] = newDef;
    }
    return true;
}

void removeWord(std::string& word, trieNode*& pRoot, HashMap& invertedIndex, std::vector<std::string>& word4Def)
{
	removeWordRecursive(word, 0, pRoot, invertedIndex, word4Def);
}

void removeWordRecursive(std::string& word, size_t curIndex, trieNode*& pRoot, HashMap& invertedIndex, std::vector<std::string>& word4Def)
{
	//base case
	if (!pRoot)
		return;
	if (curIndex == word.size())  
	{
		if (pRoot->wordExisted) 
		{
            // If word has >= 4 definitions, remove it from word4Def
            if (pRoot->definitions.size() >= 4)
            {
                for (auto it = word4Def.begin(); it < word4Def.end(); ++it)
                {
                    if (*it == word)
                    {
                        word4Def.erase(it);
                        break;
                    }
                }
            }

			// Remove word from Inverted Index
			for (auto& def : pRoot->definitions)
                invertedIndex.removeWordDef(word, def.second);

			// Remove word from Trie
			pRoot->wordExisted = false;
			pRoot->definitions.clear();

			//check whether it is the last node (delete) or prefix for other words.
			if (!isLeaf(pRoot)) 
			{
				delete pRoot;
				pRoot = nullptr;
			}
		}
		return;
	}

	int indexNext = int(word[curIndex]) - 32;
	removeWordRecursive(word, curIndex + 1, pRoot->childNode[indexNext], invertedIndex, word4Def);
	pRoot->countchildren--;
	if (isLeaf(pRoot) && !pRoot->wordExisted)
	{
		delete pRoot;
		pRoot = nullptr;
	}
}

/// @brief this is unused, maybe it can be useful later
/// @param word 
/// @param pos 
/// @param definition 
/// @param pRoot 
/// @param invertedIndex 
/// @param word4Def 
void addWord(std::string& word, std::string& pos, std::string& definition, trieNode*& pRoot, HashMap& invertedIndex, std::vector<std::string>& word4Def)
{
    // If this is the 4th definition of word, add it to word4Def
    if (traverseToSearch(pRoot, word).size() == 3)
        word4Def.push_back(word);
    
    // Insert word to trie
    
   insert(pRoot, word, pos, definition, word4Def);

    // Inverted Indexing word
    invertedIndex.insertWordDef(word, definition);
}
void removeAllCase(std::string word, trieNode*& pRoot, std::vector<std::string>& word4Def, HashMap& invertedIndex)
{
	//first, updating the word to have characters (lowercase) which locate after blankspace and at first to uppercase
    printf("removing\n");
    Change2Lowercase(word);
	size_t length = word.length();
	for (size_t i = 0; i < length; ++i) {
		if ((i == 0 || (i - 1 >= 0 && word[i - 1] == ' ')) && std::islower(word[i])) {
			word[i] -= 32;
		}
		if (i == 0) //Traverse to search the for VieEng
		{
            printf("%s\n", word.c_str());
			removeWord(word, pRoot, invertedIndex, word4Def);
		}
	}
	//(the first letter in each syllable in capital form)
    printf("%s\n", word.c_str());
	removeWord(word, pRoot, invertedIndex, word4Def);
	
	// Convert all the letters to lowercase
	Change2Lowercase(word);

	// Traverse the trie to find the word (the first letter in lowercase)
    printf("%s\n", word.c_str());
	removeWord(word, pRoot, invertedIndex, word4Def);
}
