#include "desiredsearch.h"

desiredsearch::desiredsearch()
{

}

void desiredsearch::updateoptions(std::string word)
{
	categories = std::vector<std::string>();
	//re-init the buttons

	for (int i = 0; i < options.size(); ++i) options[i].setPosition(sf::Vector2u(125, 145 + 65 * i));
}

void desiredsearch::draw()
{

}