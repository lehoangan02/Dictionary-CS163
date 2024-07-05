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
	gameModeDef(loadTexture("assets/images/GameTextDef.png")),
	gameModeHov(loadTexture("assets/images/GameTextHov.png")),
	gameModeButton(gameModeDef, gameModeHov),
	// search button
	searchTexDef(loadTexture("assets/images/SearchTexDef.png")),
	searchTexHov(loadTexture("assets/images/SearchTexHov.png")),
	searchTexClick(loadTexture("assets/images/SearchTexClick.png")),
	searchButton(searchTexDef, searchTexHov, searchTexClick),
	// history button
	historyTexDef(loadTexture("assets/images/HistoryTexDef.png")),
	historyTexHov(loadTexture("assets/images/HistoryTexHov.png")),
	historyTexClick(loadTexture("assets/images/HistoryTexClick.png")),
	historyButton(historyTexDef, historyTexHov, historyTexClick),
	// import button
	importTexDef(loadTexture("assets/images/ImportTexDef.png")),
	importTexHov(loadTexture("assets/images/ImportTexHov.png")),
	importTexClick(loadTexture("assets/images/ImportTexClick.png")),
	importButton(importTexDef, importTexHov, importTexClick),
	// fonts
	PlayfairDisplay(loadFont("assets/font/PlayfairDisplay-VariableFont_wght.ttf")),
	SourceSans3(loadFont("assets/font/SourceSans3-VariableFont_wght.ttf")),
	PatuaOne(loadFont("assets/font/PatuaOne-Regular.ttf")),
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
	deserializeModeDef(loadTexture("assets/images/SerializeDef.png")),
	deserializeModeHov(loadTexture("assets/images/SerializeHov.png")),
	deserializeModeButton(deserializeModeDef, deserializeModeHov),
	// definition background
	definitionBackground(loadTexture("assets/images/DefinitionBackground.png")),
	// searilize button
	serializeTexture(loadTexture("assets/images/SerializeTexture.png")),
	serializeButton(serializeTexture, serializeTexture, SourceSans3, serializeString, 36),
	//switch button
	onSwitch(loadTexture("assets/images/onSwitch.png")),
	offSwitch(loadTexture("assets/images/offSwitch.png")),
	autoSaveButton(onSwitch, offSwitch),
	// next/prev page buttons
	nextPageDef(loadTexture("assets/images/NextPageDef.png")),
	nextPageHov(loadTexture("assets/images/NextPageHov.png")),
	nextPageClick(loadTexture("assets/images/NextPageClick.png")),
	nextPageButton(nextPageDef, nextPageHov, nextPageClick),
	prevPageDef(loadTexture("assets/images/PrevPageDef.png")),
	prevPageHov(loadTexture("assets/images/PrevPageHov.png")),
	prevPageClick(loadTexture("assets/images/PrevPageClick.png")),
	prevPageButton(prevPageDef, prevPageHov, prevPageClick),
	// pageUp/pageDown buttons
	pageUpDef(loadTexture("assets/images/PageUpDef.png")),
	pageUpHov(loadTexture("assets/images/PageUpHov.png")),
	pageUpClick(loadTexture("assets/images/PageUpClick.png")),
	pageUpButton(pageUpDef, pageUpHov, pageUpClick),
	pageDownDef(loadTexture("assets/images/PageDownDef.png")),
	pageDownHov(loadTexture("assets/images/PageDownHov.png")),
	pageDownClick(loadTexture("assets/images/PageDownClick.png")),
	pageDownButton(pageDownDef, pageDownHov, pageDownClick),

	// deserialize button
	deserializeTexture(loadTexture("assets/images/DeserializeTexTure.png")),
	deserializeButton(deserializeTexture, deserializeTexture, SourceSans3, "Deserialize", 36),
	// Game animation
	penguinTexture(loadTexture("assets/images/sprPenguinP.png")),
	penguinAnimation(penguinTexture, sf::Vector2u(8, 3), 0.23f),
	rainbowStarTexture(loadTexture("assets/images/Magicalrainbowstar.png")),
	rainbowStarAnimation(rainbowStarTexture, sf::Vector2u(24, 1), 0.04f),
	scenery(loadTexture("assets/images/scenery.png")),
	sceneryAnimation(scenery, sf::Vector2u(19, 1), 0.15),
	knightTexture(loadTexture("assets/images/_Run.png")),
	knightAnimation(knightTexture, sf::Vector2u(10, 1), 0.1),
	congratulationsTexture(loadTexture("assets/images/Congratulations.png")),
	congratulationsAnimation(congratulationsTexture, sf::Vector2u(1, 30), 0.1f)



{
	std::ifstream fin; fin.open("note.txt");
	if (!fin.is_open()) printf("[DEBUG] no file found\n");
	// Base layer
	baseLayer.loadFromFile("assets/images/Base_Layer.png");
	baseLayerSprite.setTexture(baseLayer);

	// Set button's position
	modeButton.setPosition(sf::Vector2u(40 - SHADOWHOR, 40));
	searchModeButton.setPosition(sf::Vector2u(40, 40 + 65 + SHADOWVER));
	settingModeButton.setPosition(sf::Vector2u(40, 40 + 65 * 2 + SHADOWVER));
	definitionModeButton.setPosition(sf::Vector2u(40, 40 + 65 * 3 + SHADOWVER));
	gameModeButton.setPosition(sf::Vector2u(40 - SHADOWHOR, 40 + 65 * 4 + SHADOWVER));
	searchButton.setPosition(sf::Vector2u(855 - SHADOWHOR, 40));
	importButton.setPosition(sf::Vector2u(715 - SHADOWHOR, 125));
	historyButton.setPosition(sf::Vector2u(855 - SHADOWHOR, 125));

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

	// Set up import status message
	importStatus.setFont(SourceSans3);
	importStatus.setCharacterSize(32);
	importStatus.setPosition(145, 207);
	importStatus.setOutlineColor(sf::Color::Black);
	importStatus.setOutlineThickness(1);
	importStatus.setStyle(sf::Text::Style::Bold);

	// Set up sub-mode button in setting
	importModeButton.setPosition(sf::Vector2u(0, 620));
	addModeButton.setPosition(sf::Vector2u(160, 620));
	deleteModeButton.setPosition(sf::Vector2u(160 * 2, 620));
	editModeButton.setPosition(sf::Vector2u(160 * 3, 620));
	saveModeButton.setPosition(sf::Vector2u(160 * 4, 620));
	deserializeModeButton.setPosition(sf::Vector2u(160 * 5, 620));

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

	// Definition's page control buttons
	nextPageButton.setPosition(sf::Vector2u(855 - SHADOWHOR, 635));
	nextPageButton.setOffset(4.0f, 8.0f);
	prevPageButton.setPosition(sf::Vector2u(40 - SHADOWHOR, 635));
	prevPageButton.setOffset(4.0f, 8.0f);
	pageUpButton.setPosition(sf::Vector2u(405 - SHADOWHOR, 635));
	pageUpButton.setOffset(4.0f, 8.0f);
	pageDownButton.setPosition(sf::Vector2u(490 - SHADOWHOR, 635));
	pageDownButton.setOffset(4.0f, 8.0f);

	// Set up loading page
	loadingTexture.loadFromFile("assets/images/sandclock.png");
	loadingSprite.setTexture(loadingTexture);
	loadingSprite.setPosition(0.0f, 0.0f);

	// Deserialize button and prompt
	deserializeButton.setPosition(sf::Vector2u(550 - SHADOWHOR, 125));
	toLoadLastSaveTexture.loadFromFile("assets/images/ToLoadLastSave.png");
	toLoadLastSaveSprite.setTexture(toLoadLastSaveTexture);
	toLoadLastSaveSprite.setPosition(105.0f, 125.0f);

	// Game mode
	penguinAnimation.animationSprite.setScale(3, 3);
	penguinAnimation.setPosition(sf::Vector2u(0, 360 - (penguinAnimation.animationSprite.getGlobalBounds().height) / penguinAnimation.imageCount.y));
	rainbowStarAnimation.animationSprite.setScale(3, 3);
	rainbowStarAnimation.setPosition(sf::Vector2u(960 - (rainbowStarAnimation.animationSprite.getGlobalBounds().width) / rainbowStarAnimation.imageCount.x - 20,
	360 - (rainbowStarAnimation.animationSprite.getGlobalBounds().height) / rainbowStarAnimation.imageCount.y));
	sceneryAnimation.animationSprite.setScale(960 / sceneryAnimation.animationSprite.getGlobalBounds().width * sceneryAnimation.imageCount.x,
	720 / sceneryAnimation.animationSprite.getGlobalBounds().height);
	knightAnimation.animationSprite.setScale(-1.0f, 1.0f);
	knightAnimation.setPosition(sf::Vector2u(1100, 630));
}
void instance::operate()
{
	while (windowInstance.isOpen())
	{
		deltaTime = clock.restart().asSeconds();
		switch (page)
		{
		case 1: // Opening Page
		{
			operatePage1();
			drawPage1();
			break;
		}
		break;
		case 2:
		{
			operatePage2();
			drawPage2();	
			break;
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
			break;
		}
		break;
		case 8:
		{
			operatePage8();
			drawPage8();
			break;
		}
		break;
		case 9:
		{
			operatePage9();
			drawPage9();
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
		deleteWholeTrie(pRoot);
		deserializeBinaryWrapper(pRoot);
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
				// printf("[DEBUG] mouse button pressed\n");
				mouseControl = true;
				if (searchButton.isClicked(windowInstance)) // static function
				{
					displayHistory = false;
					historyIndex = 0;
					std::string temp = searchBox.getString();
					history.push_back(temp);
					writeHistory(temp);
					handleSearchSignal(temp);
				}
				else if (nextPageButton.isClicked(windowInstance))
				{
					if (definitionNum < (int)searchResult.size() - 1)
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
				else if (historyButton.isClicked(windowInstance))
				{
                    if (!loadHistory)
                    {
                        readHistory(history);
                        loadHistory = true;
                    }
					displayHistory = true;
					handleHistory();
				}
				else if (displayHistory && displayDef)
				{
					if (pageUpButton.isClicked(windowInstance))
					{
						if (historyIndex > 0)
							--historyIndex;
					}
					else if (pageDownButton.isClicked(windowInstance))
					{
						if (historyIndex < (int)history.size() - 1)
							++historyIndex;
					}
					handleHistory();
				}
			}
			case sf::Event::KeyPressed:
			{
				if (event.key.code == sf::Keyboard::Return)
				{
					printf("[DEBUG] enter pressed\n");
					displayHistory = false;
					historyIndex = 0;
					std::string temp = searchBox.getString();
					history.push_back(temp);
					writeHistory(temp);
					handleSearchSignal(temp);
				}
			}
			break;
            case sf::Event::LostFocus:
            {
                std::cout << "[DEBUG] lost focus" << std::endl;
            }
            break;
            case sf::Event::GainedFocus:
            {
                std::cout << "[DEBUG] gained focus" << std::endl;
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
	historyButton.hoverSwitchTexture(windowInstance);
	historyButton.click(windowInstance);
	nextPageButton.hoverSwitchTexture(windowInstance);
	prevPageButton.hoverSwitchTexture(windowInstance);
	pageUpButton.hoverSwitchTexture(windowInstance);
	pageDownButton.hoverSwitchTexture(windowInstance);
	nextPageButton.click(windowInstance);
	prevPageButton.click(windowInstance);
	pageUpButton.click(windowInstance);
	pageDownButton.click(windowInstance);
}
void instance::drawPage1()
{
	windowInstance.clear();
	windowInstance.draw(baseLayerSprite);
	drawSwitchMode();
	searchButton.draw(windowInstance);
	historyButton.draw(windowInstance);
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
				mouseControl = true;
				printf("[DEBUG] mouse button pressed\n");
				if (importButton.isClicked(windowInstance))
				{
					displayStatus = true;
					std::string filepath = importBox.getString();
					std::cout << filepath << std::endl;
					deleteWholeTrie(pRoot);
					drawLoadingPage();
					if (readDatasetCSV(filepath, pRoot))
					{
						std::cout << "[DEBUG] import successful\n";
						importStatus.setFillColor(sf::Color(128, 255, 0));
						importStatus.setString("Import Successful\n");
					}
					else
					{
						std::cout << "[DEBUG] import failed\n";
						importStatus.setFillColor(sf::Color(255, 153, 0));
						importStatus.setString("Import Failed\n");
					}
				}
				break;
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
	if (displayStatus) windowInstance.draw(importStatus);
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
				mouseControl = false;
				serializeBinaryWrapper(pRoot);
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
void instance::operatePage8()
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
			if (deserializeButton.isClicked(windowInstance))
			{
				mouseControl = false;
				drawLoadingPage();
				deleteWholeTrie(pRoot);
				deserializeBinaryWrapper(pRoot);
			}
		}
		break;
		default:
			break;
		}
	}
	handleSwitchModeLogic();
	hoverSubModes();
	deserializeButton.hoverSwitchTexture(windowInstance);
	switchPage();
}
void instance::drawPage8()
{
	windowInstance.clear();
	windowInstance.draw(baseLayerSprite);
	drawSwitchMode();
	drawSubModes();
	deserializeButton.draw(windowInstance);
	windowInstance.draw(toLoadLastSaveSprite);
	windowInstance.display();
}
void instance::operatePage9()
{
	while (windowInstance.pollEvent(event))
	{
		switch (event.type)
		{
		case sf::Event::Closed:
		windowInstance.close();
		break;
		case sf::Event::KeyPressed:
		{
			if (event.key.code == sf::Keyboard::Return)
			{
				correctAnswer = !correctAnswer;
				if (correctAnswer) congratulationsAnimation.resetAnimation();
			}
		}
		break;
		default:
			break;
		}
	}
	knightTotalTime += deltaTime;
	if (knightTotalTime >= 0.1)
	{
		knightAnimation.animationSprite.move(-3.0f, 0.0f);
		knightTotalTime -= 0.1;
		if (knightAnimation.animationSprite.getPosition().x <= -20)
		{
			knightAnimation.setPosition(sf::Vector2u(1100, 630));
		}
	}
	knightAnimation.updateAnimation(deltaTime);
	sceneryAnimation.updateAnimation(deltaTime);
	penguinAnimation.updateAnimation(deltaTime);
	rainbowStarAnimation.updateAnimation(deltaTime);
	congratulationsAnimation.updateAnimation(deltaTime);
}
void instance::drawPage9()
{
	windowInstance.clear(sf::Color(150, 150, 150));
	sceneryAnimation.draw(windowInstance);
	knightAnimation.draw(windowInstance);
	penguinAnimation.draw(windowInstance);
	rainbowStarAnimation.draw(windowInstance);
	if (correctAnswer)
	{
		congratulationsAnimation.draw(windowInstance);
	}
	windowInstance.display();
}

/// draw the sub-mode buttons from page 2 and 4 - 7
void instance::drawSubModes()
{
	importModeButton.draw(windowInstance);
	addModeButton.draw(windowInstance);
	deleteModeButton.draw(windowInstance);
	editModeButton.draw(windowInstance);
	saveModeButton.draw(windowInstance);
deserializeModeButton.draw(windowInstance);
}

/// handle the hover effect of the sub-mode buttons from page 2 and 4 - 7
void instance::hoverSubModes()
{
	importModeButton.hoverSwitchTexture(windowInstance);
	addModeButton.hoverSwitchTexture(windowInstance);
	deleteModeButton.hoverSwitchTexture(windowInstance);
	editModeButton.hoverSwitchTexture(windowInstance);
	saveModeButton.hoverSwitchTexture(windowInstance);
deserializeModeButton.hoverSwitchTexture(windowInstance);
}

/// adjust and reset variables when switching pages
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
				displayHistory = false;
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
		else if (gameModeButton.isClicked(windowInstance))
		{
			// printf("[DEBUG] pressing page 9\n");
			if (page == 1)
			{
				printf("[DEBUG] going to page 9\n");
				page = 9;
				pageChange = true;
			}
		}
	}
	else
	{
		if (saveModeButton.isClicked(windowInstance) && mouseControl)
		{
			// printf("[DEBUG] pressing page 7\n");
			if (page == 2 || (page >= 4 && page <= 6) || page == 8)
			{
				printf("[DEBUG] changing to page 7\n");
				page = 7;
				pageChange = true;
			}
		}
		else if (importModeButton.isClicked(windowInstance) && mouseControl)
		{
			// printf("[DEBUG] pressing page 2\n");
			if ((page >= 4 && page <= 8))
			{
				printf("[DEBUG] changing to page 2\n");
				page = 2;
				pageChange = true;
			}
		}
		else if (deserializeModeButton.isClicked(windowInstance) && mouseControl)
		{
			// printf("[DEBUG] pressing page 8\n");
			if (page == 2 || (page >= 4 && page <= 8 && page != 8))
			{
				printf("[DEBUG] changing to page 8\n");
				page = 8;
				pageChange =true;
			}
		}
	}
	if (pageChange)
	{
		// printf("[DEBUG] page changed\n");
		mouseControl = false;
		searchBox.clear();
		importBox.clear();
		pageChange = false;
		definitionNum = 0;
		historyIndex = 0;
	}
}

/// draw the main mode switching buttons (top left)
void instance::drawSwitchMode()
{
	modeButton.draw(windowInstance);
	if (modeButtonActive) {
		searchModeButton.draw(windowInstance);
		settingModeButton.draw(windowInstance);
		definitionModeButton.draw(windowInstance);
		gameModeButton.draw(windowInstance);
	}
}

/// handle activation of the main mode switching button
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
	if (!modeButton.isHovering(windowInstance)
	&& sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
		modeButton.select(false);
		modeButtonActive = false; }
	if (modeButtonActive) {
		searchModeButton.hoverSwitchTexture(windowInstance);
		settingModeButton.hoverSwitchTexture(windowInstance);
		definitionModeButton.hoverSwitchTexture(windowInstance);
		gameModeButton.hoverSwitchTexture(windowInstance);
	}
}

/// draw the definition of the searched word
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
	if (definitionNum < (int)searchResult.size() - 1)	nextPageButton.draw(windowInstance);
	if (displayHistory)
	{
		if (historyIndex > 0)
		{
			pageUpButton.draw(windowInstance);
		}
		if (historyIndex < (int)history.size() - 1)
		{
			pageDownButton.draw(windowInstance);
		}
	}
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

/// use this before potential heavy loading functions
void instance::drawLoadingPage()
{
	windowInstance.clear();
	windowInstance.draw(loadingSprite);
	windowInstance.display();
}

void instance::handleSearchSignal(std::string input)
{
	resetSearchResult();
	Change2Lowercase(input);
	std::cout << input << std::endl;
	searchResult = traverseToSearch(pRoot, input);
	numberOfResult = (int)searchResult.size();
	if (numberOfResult > 0)
	{
		headWordString = input;
		std::cout << "[DEBUG] - number of result is " << numberOfResult << std::endl;
		POSString = searchResult[definitionNum].first;
		descriptionString = searchResult[definitionNum].second;
		displayDef = true;
	}
	else	displayDef = false;
}

void instance::handleHistory()
{
	resetSearchResult();
	if (history.size() > 0)
	{
		std::string temp = history[history.size() - historyIndex - 1];
		printf("[DEBUG] current history word is: %s\n", temp.c_str());
		handleSearchSignal(temp);
	}
}
