#include "desiredsearch.h"

desiredsearch::desiredsearch()
{
	topdefault.loadFromFile("assets/image/TopResultNone.png");
	tophover.loadFromFile("assets/image/TopResultHover.png");
	middefault.loadFromFile("assets/image/MiddleResultNone.png");
	midhover.loadFromFile("assets/image/MiddleResultHover.png");
	bottomdefault.loadFromFile("assets/image/BottomResultNone.png");
	bottomhover.loadFromFile("assets/image/BottomResultHover.png");
	solodefault.loadFromFile("assets/image/SoloResultNone.png");
	solohover.loadFromFile("assets/image/SoloResultHover.png");
	f.loadFromFile("assets/fomt/SourceSans3-VariableFont_wght.ttf");
	available = 0;
}

void desiredsearch::adjustsuggestions()
{
	options.clear();
	switch (available)
	{
		case 0:
		{
			break;
		}
		case 1:
		{
			options.push_back(Button(solodefault, solohover, f, categories[0], 24));
			break;
		}
		case 2:
		{
			options.push_back(Button(topdefault, tophover, f, categories[0], 24));
			options.push_back(Button(bottomdefault, bottomhover, f, categories[1], 24));
			break;
		}
		case 3:
		{
			options.push_back(Button(topdefault, tophover, f, categories[0], 24));
			options.push_back(Button(middefault, midhover, f, categories[1], 24));
			options.push_back(Button(bottomdefault, bottomhover, f, categories[2], 24));
			break;
		}
	}
	for (int i = 0; i < options.size(); ++i) options[i].setPosition(sf::Vector2u(125, 145 + 65 * i));
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
	available = count;
	adjustsuggestions();
}

void desiredsearch::draw(sf::RenderWindow &w)
{
	for (Button b: options) b.draw(w);
}