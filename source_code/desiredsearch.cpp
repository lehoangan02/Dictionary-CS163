#include "desiredsearch.h"

desiredsearch::desiredsearch()
{

}

void desiredsearch::updateoptions(std::string word, trieNode* pRoot)
{
	//re-init the buttons
	SuggestingWords(word, pRoot, categories);
	if (categories.size() > 3) categories.erase(categories.begin() + 3, categories.end());
	for (int i = 0; i < 3; i++)
	{
		if (categories.size() > i);
		else options.erase(options.begin() + i, options.end());
	}
	for (int i = 0; i < options.size(); ++i) options[i].setPosition(sf::Vector2u(125, 145 + 65 * i));
}

void desiredsearch::draw(sf::RenderWindow& w)
{
	for (Button b: options) b.draw(w);
}