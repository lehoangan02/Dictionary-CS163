#pragma once

struct trienode
{
	bool wordexisted;
	trienode** next;
	trienode(bool here)
	{
		wordexisted = here;
		next = new trienode * [26];
		for (int i = 0; i < 26; i++) next[i] = nullptr;
	}
};

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

