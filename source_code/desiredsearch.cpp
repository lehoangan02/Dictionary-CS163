#include "desiredsearch.h"

desiredsearch::desiredsearch()
{
	available = 0;
	for (int i = 0; i < 3; i++)
	{
		options.push_back(Button());
	}
}

void desiredsearch::updateoptions(std::string word, trieNode* pRoot)
{
	categories = std::vector<std::string>();
	//re-init the buttons
	int count = 0;
	SuggestHelper(word, pRoot, count, categories);
	if (categories.size() > 3)
	{
		categories.resize(3);
		count = 3;
	}

	for (int i = 0; i < options.size(); ++i) options[i].setPosition(sf::Vector2u(125, 145 + 65 * i));
}

void desiredsearch::draw()
{

}