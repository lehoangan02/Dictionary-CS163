#pragma once
#include "button.hpp"
#include "trie.h"
#include <vector>
#include <string>

class desiredsearch
{
private:
	std::vector<std::string> categories = {"a", "b"};
	std::vector<Button> options;
	sf::Texture topdefault, middefault, bottomdefault, solodefault, tophover, midhover, bottomhover, solohover;
	sf::Font f;
	sf::Texture hover;
	int available = 2;
public:
	
	desiredsearch();
	void updateoptions(std::string word, trieNode* pRoot);
	void adjustsuggestions();
	void draw(sf::RenderWindow &w);
	int returnmode(sf::RenderWindow &w);
	std::string getcategory(int i);
	void handlelogic(sf::RenderWindow& w);
};