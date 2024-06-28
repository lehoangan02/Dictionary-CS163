#include "instance.h"

instance::instance() : 
	windowInstance(sf::VideoMode(960, 720), "Dictionary, in a nutshell", sf::Style::Close),
	// "mode" buttons
	modeTexDef(loadTexture("assets/images/ModeTexDef.png")),
	modeTexHov(loadTexture("assets/images/ModeTexHov.png")),
	modeTexClick(loadTexture("assets/images/ModeTexClick.png")),
	modeButton(modeTexDef, modeTexHov, modeTexClick),
	searchModeDef(loadTexture("assets/images/SearchModeDef.png")),
	searchModeHov(loadTexture("assets/images/SearchModeHov.png")),
	searchModeButton(searchModeDef, searchModeHov),
	settingModeDef(loadTexture("assets/images/SettingModeDef.png")),
	settingModeHov(loadTexture("assets/images/SettingModeHov.png")),
	settingModeButton(settingModeDef, settingModeHov),
	definitionModeDef(loadTexture("assets/images/DefinitionModeDef.png")),
	definitionModeHov(loadTexture("assets/images/DefinitionModeHov.png")),
	definitionModeButton(definitionModeDef, definitionModeHov),
	// search button
	searchTexDef(loadTexture("assets/images/SearchTexDef.png")),
	searchTexHov(loadTexture("assets/images/SearchTexHov.png")),
	searchTexClick(loadTexture("assets/images/SearchTexClick.png")),
	searchButton(searchTexDef, searchTexHov, searchTexClick),
	// import button
	importTexDef(loadTexture("assets/images/ImportTexDef.png")),
	importTexHov(loadTexture("assets/images/ImportTexHov.png")),
	importTexClick(loadTexture("assets/images/ImportTexClick.png")),
	importButton(importTexDef, importTexHov, importTexClick),
	// fonts
	PlayfairDisplay(loadFont("assets/font/PlayfairDisplay-VariableFont_wght.ttf")),
	SourceSans3(loadFont("assets/font/SourceSans3-VariableFont_wght.ttf")),
	// searchbox
	searchBoxTexture(loadTexture("assets/images/SearchBox.png")),
	searchBox(searchBoxTexture, SourceSans3, 24, 40, sf::Vector2u(145 - SHADOWVER, 40)),
	// importbox
	importBoxTexture(loadTexture("assets/images/ImportBox.png")),
	importBox(importBoxTexture, SourceSans3, 24, 30, sf::Vector2u(145 - SHADOWVER, 125)),
	// "format" buttons
	CSVTextureDef(loadTexture("assets/images/CSV_FormatDefault.png")),
	CSVTextureClick(loadTexture("assets/images/CSV_FormatSelected.png")),
	CSVButton(CSVTextureDef, CSVTextureDef, CSVTextureClick, &TXTButton),
	TXTTextureDef(loadTexture("assets/images/TXT_FormatDefault.png")),
	TXTTextureClick(loadTexture("assets/images/TXT_FormatSelected.png")),
	TXTButton(TXTTextureDef, TXTTextureDef, TXTTextureClick, &CSVButton),
	// Sub-mode button in settings
	importModeDef(loadTexture("assets/images/ImportPageDef.png")),
	importModeHov(loadTexture("assets/images/ImportPageHov.png")),
	importModeButton(importModeDef, importModeHov),
	addModeDef(loadTexture("assets/images/AddWordDef.png")),
	addModeHov(loadTexture("assets/images/AddWordHov.png")),
	addModeButton(addModeDef, addModeHov),
	deleteModeDef(loadTexture("assets/images/DeleteWordDef.png")),
	deleteModeHov(loadTexture("assets/images/DeleteWordHov.png")),
	deleteModeButton(deleteModeDef, deleteModeHov),
	editModeDef(loadTexture("assets/images/EditWordDef.png")),
	editModeHov(loadTexture("assets/images/EditWordHov.png")),
	editModeButton(editModeDef, editModeHov),
	saveModeDef(loadTexture("assets/images/SaveDef.png")),
	saveModeHov(loadTexture("assets/images/SaveHov.png")),
	saveModeButton(saveModeDef, saveModeHov),
	serializeModeDef(loadTexture("assets/images/SerializeDef.png")),
	serializeModeHov(loadTexture("assets/images/SerializeHov.png")),
	serializeModeButton(serializeModeDef, serializeModeHov),
	// definition background
	definitionBackground(loadTexture("assets/images/DefinitionBackground.png"))
{
	std::ifstream fin; fin.open("note.txt");
	if (!fin.is_open()) printf("[DEBUG] no file found\n");
	// Base layer
	baseLayer.loadFromFile("assets/images/Base_Layer.png");
	baseLayerSprite.setTexture(baseLayer);

	// Set each button's position
	modeButton.setPosition(sf::Vector2u(40 - SHADOWHOR, 40));
	searchModeButton.setPosition(sf::Vector2u(40, 40 + 65 + SHADOWVER));
	settingModeButton.setPosition(sf::Vector2u(40, 40 + 65 * 2 + SHADOWVER));
	definitionModeButton.setPosition(sf::Vector2u(40 - SHADOWHOR, 40 + 65 * 3 + SHADOWVER));
	searchButton.setPosition(sf::Vector2u(855 - SHADOWHOR, 40));
	importButton.setPosition(sf::Vector2u(715 - SHADOWHOR, 125));

	// Set up "import file" prompt
	importPromptTexture.loadFromFile("assets/images/InputFilePath.png");
	importPromptSprite.setTexture(importPromptTexture);
	importPromptSprite.setPosition(322.0f, 40.0f);

	// Set up "format" buttons positions;
	CSVButton.setPosition(sf::Vector2u(145 - 8, 332 - 4));
	TXTButton.setPosition(sf::Vector2u(370 - 8, 332 - 4));

	// Set up "select format" prompt
	formatPromptTexture.loadFromFile("assets/images/SelectFileFormat.png");
	formatPromptSprite.setTexture(formatPromptTexture);
	formatPromptSprite.setPosition(145.0f, 282.0f);

	// Set up sub-mode button in setting
	importModeButton.setPosition(sf::Vector2u(0, 620));
	addModeButton.setPosition(sf::Vector2u(160, 620));
	deleteModeButton.setPosition(sf::Vector2u(160 * 2, 620));
	editModeButton.setPosition(sf::Vector2u(160 * 3, 620));
	saveModeButton.setPosition(sf::Vector2u(160 * 4, 620));
	serializeModeButton.setPosition(sf::Vector2u(160 * 5, 620));

	// Set up definition elements
	definitionBackgroundSprite.setTexture(definitionBackground);
	definitionBackgroundSprite.setPosition(0.0f, 360.0f);

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
	handleSwitchModeLogic();
	searchButton.hoverSwitchTexture(windowInstance);
	searchButton.click(windowInstance);
}
void instance::drawPage1()
{
	windowInstance.clear();
	windowInstance.draw(baseLayerSprite);
	drawSwitchMode();
	searchButton.draw(windowInstance);
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
			case sf::Event::MouseButtonPressed:
			{
				if (importButton.isClicked(windowInstance))
				{
					std::cout << importBox.getString() << std::endl;
				}
			}
			break;
			case sf::Event::KeyPressed:
			{
				if (event.key.code == sf::Keyboard::Return)
				{
					printf("[DEBUG] enter pressed\n");
					std::cout << importBox.getString() << std::endl;
				}
			}
			break;
			default:
			break;
		}
		importBox.handleInputLogic(event, windowInstance);
	}
	handleSwitchModeLogic();
	CSVButton.click(windowInstance);
	TXTButton.click(windowInstance);
	CSVButton.hoverSwitchTexture(windowInstance);
	TXTButton.hoverSwitchTexture(windowInstance);
	hoverSubModes();
	importButton.hoverSwitchTexture(windowInstance);
	importButton.click(windowInstance);
}
void instance::drawPage2()
{
	windowInstance.clear();
	windowInstance.draw(baseLayerSprite);
	drawSwitchMode();
	importButton.draw(windowInstance);
	windowInstance.draw(importPromptSprite);
	importBox.draw(windowInstance);
	windowInstance.draw(formatPromptSprite);
	CSVButton.draw(windowInstance);
	TXTButton.draw(windowInstance);
	drawSubModes();
	windowInstance.display();
}
void instance::drawSubModes()
{
	importModeButton.draw(windowInstance);
	addModeButton.draw(windowInstance);
	deleteModeButton.draw(windowInstance);
	editModeButton.draw(windowInstance);
	saveModeButton.draw(windowInstance);
	serializeModeButton.draw(windowInstance);
}
void instance::hoverSubModes()
{
	importModeButton.hoverSwitchTexture(windowInstance);
	addModeButton.hoverSwitchTexture(windowInstance);
	deleteModeButton.hoverSwitchTexture(windowInstance);
	editModeButton.hoverSwitchTexture(windowInstance);
	saveModeButton.hoverSwitchTexture(windowInstance);
	serializeModeButton.hoverSwitchTexture(windowInstance);
}
void instance::switchPage()
{
	if (!modeButtonActive) return;
	if (searchModeButton.isClicked(windowInstance))
	{
		if (page != 1)
		{
			printf("[DEBUG] at page 1\n");
			page = 1;
			modeButtonActive = false;
			pageChange = true;
		}
	}
	else if (settingModeButton.isClicked(windowInstance))
	{
		if (page != 2)
		{
			printf("[DEBUG] at page 2\n");
			page = 2;
			modeButtonActive = false;
			pageChange = true;
		}
	}
	if (pageChange)
	{
		printf("[DEBUG] page changed\n");
		searchBox.clear(); std::cout << searchBox.getString() << std::endl;
		importBox.clear();
		pageChange = false;
	}
}
void instance::drawSwitchMode()
{
	modeButton.draw(windowInstance);
	if (modeButtonActive) {
		searchModeButton.draw(windowInstance);
		settingModeButton.draw(windowInstance);
		definitionModeButton.draw(windowInstance);
	}
}
void instance::handleSwitchModeLogic()
{
	switchPage();
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
		settingModeButton.hoverSwitchTexture(windowInstance);
		definitionModeButton.hoverSwitchTexture(windowInstance);
	}
}

