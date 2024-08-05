#include "desiredsearch.h"

desiredsearch::desiredsearch()
{
	topdefault.loadFromFile("assets/images/TopResultNone.png");
	tophover.loadFromFile("assets/images/TopResultHover.png");
	middefault.loadFromFile("assets/images/MiddleResultNone.png");
	midhover.loadFromFile("assets/images/MiddleResultHover.png");
	bottomdefault.loadFromFile("assets/images/BottomResultNone.png");
	bottomhover.loadFromFile("assets/images/BottomResultHover.png");
	solodefault.loadFromFile("assets/images/SoloResultNone.png");
	solohover.loadFromFile("assets/images/SoloResultHover.png");
	f.loadFromFile("assets/font/SourceSans3-VariableFont_wght.ttf");
}

//clear the old suggest buttons and create new ones
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

//update the suggested words, and then the suggested buttons
void desiredsearch::updateoptions(std::string word, trieNode* pRoot)
{
	categories = std::vector<std::string>();
	options.clear();
	//re-init the buttons
	if (!word.length()) return;
	std::cout << word << "\n";
	categories = std::vector<std::string>(SuggestingWords(word, pRoot));
	categories.erase(categories.begin());
	if (categories.size() > 3)
	{
		categories.erase(categories.begin() + 3, categories.end());
	}
	available = categories.size();
	for (std::string s : categories) std::cout << s << "\n";
	this->adjustsuggestions();
}

void desiredsearch::draw(sf::RenderWindow &w)
{
	for (Button b : options)
	{
		b.draw(w);
	}
}

//suggested search "mode", i.e. which button is pressed, -1 if none. the function also changes the word in the search box
int desiredsearch::returnmode(sf::RenderWindow &w)
{
	for (int i = 0; i < options.size(); i++)
		if (options[i].isClicked(w))
		{
			available = 0;
			categories.clear();
			return i;
		}
	return -1;
}

std::string desiredsearch::getcategory(int i)
{
	return categories[i];
}

void desiredsearch::handlelogic(sf::RenderWindow& w)
{
	for (Button b : options)
	{
		b.hoverSwitchTexture(w);
		b.click(w);
	}
}