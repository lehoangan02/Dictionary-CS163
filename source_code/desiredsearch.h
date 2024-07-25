#pragma once
#include "button.hpp"
#include "trie.h"
#include <vector>
#include <string>

class desiredsearch
{
	std::vector<std::string> categories;
	std::vector<Button> options;
	sf::Texture topdefault, middefault, bottomdefault, solodefault, tophover, midhover, bottomhover, solohover;
	sf::Font f;
	sf::Texture hover;
	int available;
	desiredsearch();
	void updateoptions(std::string word, trieNode* pRoot);
	void adjustsuggestions();
	void draw(sf::RenderWindow &w);
};