#include "doublyLinkedList.hpp"

/// @brief check if the input string exist in the linked list
/// @param pRoot 
/// @param input 
/// @return 
bool existInList(linkedListNode* pRoot, std::string input)
{
    if (!pRoot) return false;
    while (pRoot)
    {
        if (pRoot -> data == input) // two string are equal
        {
            return true;
        }
        pRoot = pRoot -> pNext;
    }
    return false;
}

/// @brief insert a word into the linked list
/// @param pRoot 
/// @param input 
void insertLinkedList(linkedListNode*& pRoot, std::string input)
{
    if (existInList(pRoot, input)) return;
    linkedListNode* newPRoot = new linkedListNode;
    newPRoot -> data = input;
    if (pRoot == nullptr)
    {
        pRoot = newPRoot;
        return;
    }
    pRoot -> pPrev = newPRoot;
    newPRoot -> pNext = pRoot;
    pRoot = newPRoot;
}


/// @brief delete a word from a linked list
/// @param pRoot 
/// @param input 
void deleteNode(linkedListNode*& pRoot, std::string input)
{
    if (!existInList(pRoot, input)) return;
    if (!pRoot) return;
    printf("[DEBUG] delete favourite %s\n", input.c_str());
    linkedListNode* pCur = pRoot;
    while (pCur)
    {
        if (pCur -> data.compare(input) == 0) // two string are equal
        {
            linkedListNode* pPrevTemp = pCur -> pPrev;
            linkedListNode* pNextTemp = pCur -> pNext;
            if (pNextTemp)
            {
                pNextTemp -> pPrev = pPrevTemp;
            }
            if (pPrevTemp)
            {
                pPrevTemp -> pNext = pNextTemp;
            }
            if (pCur == pRoot)
            {
                pRoot = pNextTemp;
            }
            delete pCur;
            pCur = nullptr;
            return;
        }
        else
        {
            pCur = pCur -> pNext;
        }
    }
}


/// @brief read previous favourite words
/// @param pRoot 
void readFavourite(linkedListNode*& pRoot)
{
    std::string temp;
    std::ifstream fin;
    fin.open("settings/favourite.txt");
    while (getline(fin, temp))
    {
        Change2Uppercase(temp);
        if (temp.compare("") != 0)
        {
            insertLinkedList(pRoot, temp);
            printf("[DEBUG] reading favourite: %s\n", temp.c_str());
        }
    }
    fin.close();
}

/// @brief write new favourite to saves
/// @param pRoot 
void writeFavourite(linkedListNode* pRoot)
{
    std::ofstream fout;
    fout.open("settings/favourite.txt", std::ios::trunc);
    while (pRoot)
    {
        printf("[DEBUG] writing %s\n", (pRoot -> data).c_str());
        std::string temp = pRoot -> data;
        Change2Uppercase(temp);
        fout << temp;
        if (pRoot -> pNext)
        {
            fout << std::endl;
        }
        pRoot = pRoot -> pNext;
    }
    fout.close();
}

void deallocateLinkedList(linkedListNode*& pRoot)
{
    if (!pRoot) return;
    linkedListNode* pCur = pRoot;
    linkedListNode* pTemp = pCur -> pNext;
    while (pTemp)
    {
        delete pCur;
        pCur = pTemp;
        pTemp = pTemp -> pNext;
    }
    delete pCur;
    pRoot = nullptr;
}
