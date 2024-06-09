#include <iostream>
#include <string>
#include "trie.h"

using namespace std;

int main()
{
	trienode* trie = nullptr;
	string word = "";
	while (1)
	{
		getline(cin, word);
		if (word.length() == 0) break;
		for (int i = 0; i < word.length(); i++)
		{
			if (word[i] >= 65 && word[i] < 91) word[i] += 32;
		}
		insert(trie, word);
	}
	cout << find(trie, "hello");
	return 0;
}

