#include "instance.h"

instance::instance() : 
	windowInstance(sf::VideoMode(960, 720), "Dictionary, in a nutshell", sf::Style::Close),
	modeTexDef(loadTexture("assets/images/ModeTexDef.png")),
	modeTexHov(loadTexture("assets/images/ModeTexHov.png")),
	modeTexClick(loadTexture("assets/images/ModeTexClick.png")),
	modeButton(modeTexDef, modeTexHov, modeTexClick),
	searchModeDef(loadTexture("assets/images/SearchModeDef.png")),
	searchModeHov(loadTexture("assets/images/SearchModeHov.png")),
	searchModeButton(searchModeDef, searchModeHov),
	importModeDef(loadTexture("assets/images/ImportModeDef.png")),
	importModeHov(loadTexture("assets/images/ImportModeHov.png")),
	importModeButton(importModeDef, importModeHov),
	definitionModeDef(loadTexture("assets/images/DefinitionModeDef.png")),
	definitionModeHov(loadTexture("assets/images/DefinitionModeHov.png")),
	definitionModeButton(definitionModeDef, definitionModeHov),
	searchTexDef(loadTexture("assets/images/SearchTexDef.png")),
	searchTexHov(loadTexture("assets/images/SearchTexHov.png")),
	searchTexClick(loadTexture("assets/images/SearchTexClick.png")),
	searchButton(searchTexDef, searchTexHov, searchTexClick),
	importTexDef(loadTexture("assets/images/ImportTexDef.png")),
	importTexHov(loadTexture("assets/images/ImportTexHov.png")),
	importTexClick(loadTexture("assets/images/ImportTexClick.png")),
	importButton(importTexDef, importTexHov, importTexClick),
	searchBoxTexture(loadTexture("/Users/lehoangan/Documents/GitHub/weirdmultilingualdictionary/assets/images/SearchBox.png")),
	PlayfairDisplay(loadFont("assets/font/PlayfairDisplay-VariableFont_wght.ttf")),
	SourceSans3(loadFont("assets/font/SourceSans3-VariableFont_wght.ttf")),
	searchBox(searchBoxTexture, SourceSans3, 24, 40, sf::Vector2u(145 - SHADOWVER, 40))
{
	std::ifstream fin; fin.open("note.txt");
	if (!fin.is_open()) printf("[DEBUG] no file found\n");
	// Base layer
	baseLayer.loadFromFile("assets/images/Base_Layer.png");
	baseLayerSprite.setTexture(baseLayer);

	// Set each button's position
	modeButton.setPosition(sf::Vector2u(40 - SHADOWHOR, 40));
	searchModeButton.setPosition(sf::Vector2u(40, 40 + 65));
	importModeButton.setPosition(sf::Vector2u(40, 40 + 65 * 2));
	definitionModeButton.setPosition(sf::Vector2u(40 - SHADOWHOR, 40 + 65 * 3));
	searchButton.setPosition(sf::Vector2u(855 - SHADOWHOR, 40));
	importButton.setPosition(sf::Vector2u(715 - SHADOWHOR, 125));

	// Set up "import file" prompt
	importPromptTexture.loadFromFile("assets/images/InputFilePath.png");
	importPromptSprite.setTexture(importPromptTexture);
	importPromptSprite.setPosition(322.0f, 40.0f);

	
}
void instance::operate()
{
	while (windowInstance.isOpen())
	{
		switch (page)
		{
		case 1: // Opening Page
		{
			operatePage1();
			drawPage1();
		}
		break;
		case 2:
		{
			operatePage2();
			drawPage2();	
		}
		break;
		case 3:
		{

		}
		break;
		default:
			break;
		}
	}
}
void instance::switchPage()
{
	if (searchModeButton.isClicked(windowInstance))
	{
		if (page != 1)
		{
			printf("[DEBUG] at page 1\n");
			page = 1;
			modeButtonActive = false;
			return;
		}
	}
	if (importModeButton.isClicked(windowInstance))
	{
		if (page != 2)
		{
			printf("[DEBUG] at page 2\n");
			page = 2;
			modeButtonActive = false;
			return;
		}
	}
}
void instance::operatePage1()
{
	while (windowInstance.pollEvent(event))
	{
		switch (event.type)
		{
			case sf::Event::Closed:
			{
				windowInstance.close();
			}
			case sf::Event::MouseButtonPressed:
			{
				if (searchButton.isClicked(windowInstance)) // static function
					{
						std::cout << searchBox.getString() << std::endl;
					}
			}
			case sf::Event::KeyPressed:
			{
				if (event.key.code == sf::Keyboard::Return)
				{
					printf("[DEBUG] enter pressed\n");
					std::cout << searchBox.getString() << std::endl;
				}
			}
			break;
			default:
			break;
		}
		searchBox.handleInputLogic(event, windowInstance);
	}
	if (modeButton.isClicked(windowInstance)) {
		modeButton.select(true);
		modeButtonActive = true; }
	if (!modeButton.isHovering(windowInstance)
	&& sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
		modeButton.select(false);
		modeButtonActive = false; }
	modeButton.hoverSwitchTexture(windowInstance);
	if (modeButtonActive) {
		searchModeButton.hoverSwitchTexture(windowInstance);
		importModeButton.hoverSwitchTexture(windowInstance);
		definitionModeButton.hoverSwitchTexture(windowInstance);
	}
	searchButton.hoverSwitchTexture(windowInstance);
	searchButton.click(windowInstance);
	switchPage();
}
void instance::drawPage1()
{
	windowInstance.clear();
	windowInstance.draw(baseLayerSprite);
	modeButton.draw(windowInstance);
	searchButton.draw(windowInstance);
	if (modeButtonActive) {
		searchModeButton.draw(windowInstance);
		importModeButton.draw(windowInstance);
		definitionModeButton.draw(windowInstance);
	}
	searchBox.draw(windowInstance);
	windowInstance.display();
}
void instance::operatePage2()
{
	while (windowInstance.pollEvent(event))
	{
		switch (event.type)
		{
			case sf::Event::Closed:
			{
				windowInstance.close();
			}
			break;
			default:
			break;
		}
	}
	if (modeButton.isClicked(windowInstance)) {
		modeButton.select(true);
		modeButtonActive = true; }
	if (!modeButton.isHovering(windowInstance)
	&& sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
		modeButton.select(false);
		modeButtonActive = false; }
	modeButton.hoverSwitchTexture(windowInstance);
	if (modeButtonActive) {
		searchModeButton.hoverSwitchTexture(windowInstance);
		importModeButton.hoverSwitchTexture(windowInstance);
		definitionModeButton.hoverSwitchTexture(windowInstance);
	}
	if (importButton.isClicked(windowInstance))
	{
		importButton.select(true);
	}
	else
	{
		importButton.select(false);
	}
	importButton.hoverSwitchTexture(windowInstance);
	switchPage();
}
void instance::drawPage2()
{
	windowInstance.clear();
	windowInstance.draw(baseLayerSprite);
	modeButton.draw(windowInstance);
	if (modeButtonActive) {
		searchModeButton.draw(windowInstance);
		importModeButton.draw(windowInstance);
		definitionModeButton.draw(windowInstance);
	}
	importButton.draw(windowInstance);
	windowInstance.draw(importPromptSprite);
	windowInstance.display();
}