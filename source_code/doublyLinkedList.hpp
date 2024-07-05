#pragma once

#include <string>

struct linkedListNode
{
    std::string data;
    linkedListNode* pNext = nullptr;
    linkedListNode* pPrev = nullptr;
};

/// @brief check if the input string exist in the linked list
/// @param pRoot 
/// @param input 
/// @return 
bool existInList(linkedListNode* pRoot, std::string input)
{
    if (!pRoot) return false;
    while (pRoot)
    {
        if (pRoot -> data.compare(input) == 0) // two string are equal
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
void deleteLinkedList(linkedListNode*& pRoot, std::string input)
{
    if (!existInList(pRoot, input)) return;
    if (!pRoot) return;
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