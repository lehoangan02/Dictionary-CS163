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
	TXTTextureDef(loadTexture("assets/images/TXT_FormatDefault.png")),
	TXTTextureClick(loadTexture("assets/images/TXT_FormatSelected.png")),
	TXTButton(TXTTextureDef, TXTTextureDef, TXTTextureClick, &CSVButton),
	CSVTextureDef(loadTexture("assets/images/CSV_FormatDefault.png")),
	CSVTextureClick(loadTexture("assets/images/CSV_FormatSelected.png")),
	CSVButton(CSVTextureDef, CSVTextureDef, CSVTextureClick, &TXTButton),
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
	definitionBackground(loadTexture("assets/images/DefinitionBackground.png")),
	// searilize button
	serializeTexture(loadTexture("assets/images/SerializeTexture.png")),
	serializeButton(serializeTexture, serializeTexture, SourceSans3, serializeString, 36),
	//switch button
	onSwitch(loadTexture("assets/images/onSwitch.png")),
	offSwitch(loadTexture("assets/images/offSwitch.png")),
	autoSaveButton(onSwitch, offSwitch),
	// next/prev page
	nextPageDef(loadTexture("assets/images/NextPageDef.png")),
	nextPageHov(loadTexture("assets/images/NextPageHov.png")),
	nextPageClick(loadTexture("assets/images/NextPageClick.png")),
	nextPageButton(nextPageDef, nextPageHov, nextPageClick),
	prevPageDef(loadTexture("assets/images/PrevPageDef.png")),
	prevPageHov(loadTexture("assets/images/PrevPageHov.png")),
	prevPageClick(loadTexture("assets/images/PrevPageClick.png")),
	prevPageButton(prevPageDef, prevPageHov, prevPageClick)
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

	// Set up fonts
	SourceSans3.setSmooth(false);
	PlayfairDisplay.setSmooth(false);

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
	headword.setFont(PlayfairDisplay);
	headword.setCharacterSize(40);
	headword.setFillColor(sf::Color::Black);
	headword.setString(headWordString);
	headword.setPosition(73.0f, 405.0f);
	POS.setFont(PlayfairDisplay);
	POS.setCharacterSize(20);
	POS.setFillColor(sf::Color::Black);
	POS.setString(POSString);
	POS.setPosition(73.0f, 455.0f);
	description.setFont(PlayfairDisplay);
	description.setCharacterSize(24);
	description.setFillColor(sf::Color::Black);
	description.setString(descriptionString);
	description.setPosition(73.0f, 505.0f);

	// Set up serialize, auto-save button and prompt
	serializeButton.setPosition(sf::Vector2u(550 - SHADOWHOR, 125));
	autoSaveButton.setPosition(sf::Vector2u(603, 224));
	toSaveCurrentTexture.loadFromFile("assets/images/ToSaveCurrentState.png");
	toSaveCurrentSprite.setTexture(toSaveCurrentTexture);
	toSaveCurrentSprite.setPosition(105.0f, 125.0f);
	autoSaveTexture.loadFromFile("assets/images/Auto-save.png");
	autoSaveSprite.setTexture(autoSaveTexture);
	autoSaveSprite.setPosition(105.0f, 216.0f);
	nextPageButton.setPosition(sf::Vector2u(855 - SHADOWHOR, 635));
	nextPageButton.setOffset(4.0f, 8.0f);
	prevPageButton.setPosition(sf::Vector2u(40 - SHADOWHOR, 635));
	prevPageButton.setOffset(4.0f, 8.0f);

	// Set up loading page
	loadingTexture.loadFromFile("assets/images/sandclock.png");
	loadingSprite.setTexture(loadingTexture);
	loadingSprite.setPosition(0.0f, 0.0f);

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
		case 7:
		{
			operatePage7();
			drawPage7();
		}
		break;
		default:
			break;
		}
	}
}
void instance::operatePage1()
{
	if (!loadedSave)
	{
		deserializeWrapper(pRoot);
		loadedSave = true;
	}
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
				mouseControl = true;
				if (searchButton.isClicked(windowInstance)) // static function
					{
						resetSearchResult();
						std::string temp = searchBox.getString();
						Change2Lowercase(headWordString);
						std::cout << temp << std::endl;
						searchResult = traverseToSearch(pRoot, temp);
						numberOfResult = (int)searchResult.size();
						if (numberOfResult > 0)
                        {
                            headWordString = temp;
                            std::cout << "[DEBUG] - number of result is " << numberOfResult << std::endl;
                            POSString = searchResult[definitionNum].first;
                            descriptionString = searchResult[definitionNum].second;
                            displayDef = true;
                        }
						else	displayDef = false;
					}
				else if (nextPageButton.isClicked(windowInstance))
				{
					if (definitionNum < searchResult.size() - 1)
					{
						++definitionNum;
						POSString = searchResult[definitionNum].first;
                        descriptionString = searchResult[definitionNum].second;
					}
				}
				else if (prevPageButton.isClicked(windowInstance))
				{
					if (definitionNum > 0)
					{
						--definitionNum;
						POSString = searchResult[definitionNum].first;
                        descriptionString = searchResult[definitionNum].second;
					}
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
	nextPageButton.hoverSwitchTexture(windowInstance);
	prevPageButton.hoverSwitchTexture(windowInstance);
	nextPageButton.click(windowInstance);
	prevPageButton.click(windowInstance);
}
void instance::drawPage1()
{
	windowInstance.clear();
	windowInstance.draw(baseLayerSprite);
	drawSwitchMode();
	searchButton.draw(windowInstance);
	searchBox.draw(windowInstance);
	drawDefinition();
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
					std::string filepath = importBox.getString();
					std::cout << filepath << std::endl;
					deleteWholeTrie(pRoot);
					if (readDatasetCSV(filepath, pRoot))
					{
						std::cout << "[DEBUG] import successful\n";
					}
					else
						std::cout << "[DEBUG] import failed\n";
				}
				mouseControl = true;
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
void instance::operatePage7()
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
			mouseControl = true;
			if (serializeButton.isClicked(windowInstance))
			{
				drawLoadingPage();
				serializeWrapper(pRoot);
			}
		}
		break;
		default:
			break;
		}
	}
	handleSwitchModeLogic();
	hoverSubModes();
	serializeButton.hoverSwitchTexture(windowInstance);
	serializeButton.click(windowInstance);
	autoSaveButton.click(windowInstance, mouseControl);
	saveAutoSaveSetting();
	switchPage();
}
void instance::drawPage7()
{
	windowInstance.clear();
	windowInstance.draw(baseLayerSprite);
	drawSwitchMode();
	drawSubModes();
	serializeButton.draw(windowInstance);
	autoSaveButton.draw(windowInstance);
	windowInstance.draw(toSaveCurrentSprite);
	windowInstance.draw(autoSaveSprite);
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
	if (modeButtonActive)
	{
		if (searchModeButton.isClicked(windowInstance))
		{
			if (page != 1)
			{
				printf("[DEBUG] at page 1\n");
				page = 1;
				modeButtonActive = false;
				pageChange = true;
				numberOfResult = 0;
				displayDef = false;
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
	}
	else
	{
		if (saveModeButton.isClicked(windowInstance) && mouseControl)
		{
			if (page == 2 || (page >= 4 && page <= 6) || page == 8)
			{
				printf("[DEBUG] pressing page 7\n");
				printf("[DEBUG] at page 7\n");
				page = 7;
				pageChange = true;
			}
			mouseControl = false;
		}
		else if (importModeButton.isClicked(windowInstance) && mouseControl)
		{
			if ((page >= 4 && page <= 7))
			{
				printf("[DEBUG] pressing page 2\n");
				printf("[DEBUG] at page 2\n");
				page = 2;
				pageChange = true;
			}
			mouseControl = false;
		}
	}
	if (pageChange)
	{
		printf("[DEBUG] page changed\n");
		searchBox.clear();
		importBox.clear();
		pageChange = false;
		definitionNum = 0;
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
void instance::drawDefinition()
{
	if (!displayDef) return;
	windowInstance.draw(definitionBackgroundSprite);
	headword.setString(headWordString);
	POS.setString(POSString);
	description.setString(descriptionString);
	windowInstance.draw(headword);
	windowInstance.draw(POS);
	windowInstance.draw(description);
	if (definitionNum > 0)	prevPageButton.draw(windowInstance);
	if (definitionNum < searchResult.size() - 1)	nextPageButton.draw(windowInstance);
}
void instance::saveAutoSaveSetting()
{
	bool temp = autoSaveButton.getMode();
	if (temp != autoSave)
	{
		std::ofstream fout;
		fout.open("settings/auto-save.txt", std::ios::trunc);
		fout << temp;
		autoSave = temp;
	}
}
void instance::resetSearchResult()
{
	displayDef = false;
	searchResult.clear();
	definitionNum = 0;
	numberOfResult = 0;
	headWordString = "";
	POSString = "";
	descriptionString = "";
}
void instance::drawLoadingPage()
{
	windowInstance.clear();
	windowInstance.draw(loadingSprite);
	windowInstance.display();
}

