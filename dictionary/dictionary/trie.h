#pragma once
#include <string>
#include <vector>

struct trieNode
{
	bool wordExisted;
	trieNode** next;
	std::vector<std::pair<std::string, std::string>> definitions;
	trieNode(bool wordExisted)
	{
		this->wordExisted = wordExisted;
		next = new trieNode * [29];
		// 0->25: letters
		// 26: space (' ') - 32
		// 27: dash ('-') - 45
		// 28: apostrophe (') - 39

		for (int i = 0; i < 29; i++) next[i] = nullptr;
	}
};

void load();

void lowercase(std::string word);

void insert(trieNode*& pCurrent, std::string word);

bool find(trieNode* pCurrent, std::string word);