#include <iostream>
#include <string>
#include "trie.h"

using namespace std;

int main()
{
	trieNode* trie = nullptr;
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
	
	return 0;
}

