#pragma once

#include <string>
#include <fstream>

#include "trie.h"

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
bool existInList(linkedListNode* pRoot, std::string input);

/// @brief insert a word into the linked list
/// @param pRoot 
/// @param input 
void insertLinkedList(linkedListNode*& pRoot, std::string input);

/// @brief delete a word from a linked list
/// @param pRoot 
/// @param input 
void deleteLinkedList(linkedListNode*& pRoot, std::string input);

/// @brief read previous favourite words
/// @param pRoot 
void readFavourite(linkedListNode*& pRoot);

/// @brief write new favourite to saves
/// @param pRoot 
void writeFavourite(linkedListNode* pRoot);

void deallocateLinkedList(linkedListNode*& pRoot);  