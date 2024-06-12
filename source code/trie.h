#pragma once
#include <string>
#include <vector>

using namespace std;

struct trienode
{
	bool wordexisted;
	trienode** next;
	vector<pair<string, string>> definitions; //import all meanings to this vector, word form in first string, definition in second
	trienode(bool here)
	{
		wordexisted = here;
		next = new trienode * [26];
		for (int i = 0; i < 26; i++) next[i] = nullptr;
	}
};

void load()
{
	//load a csv line to c++ whatever thing
}

void insert(trienode*& t, string word)
{
	if (t == nullptr)
	{
		if (word.length() == 0) t = new trienode(true);
		else
		{
			t = new trienode(false);
			insert(t->next[word[0] - 97], word.erase(0, 1));
		}
	}
	else
	{
		if (word.length() == 0) t->wordexisted = true;
		else insert(t->next[word[0] - 97], word.erase(0, 1));
	}
}

bool find(trienode* t, string word)
{
	if (!t) return false;
	if (word.length() == 0) return t->wordexisted;
	else return find(t->next[word[0] - 97], word.erase(0, 1));
}

void deleteTrie(trienode*& pRoot)
{
	if (!pRoot)
		return;
	for (int i = 0; i < 29; ++i)
	{
		deleteTrie(pRoot->next[i]);
	}
	delete pRoot;
	pRoot = nullptr;
}