#include "instance.h"
//line 286
//line 501
//line 548
//Please identify the correct form of serialize and deserialize

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
	// favourite button
	favouriteTexDef(loadTexture("assets/images/FavouriteTexDef.png")),
	favouriteTexHov(loadTexture("assets/images/FavouriteTexHov.png")),
	favouriteTexClick(loadTexture("assets/images/FavouriteTexClick.png")),
	favouriteButton(favouriteTexDef, favouriteTexHov, favouriteTexClick),
	// import button
	importTexDef(loadTexture("assets/images/ImportTexDef.png")),
	importTexHov(loadTexture("assets/images/ImportTexHov.png")),
	importTexClick(loadTexture("assets/images/ImportTexClick.png")),
	importButton(importTexDef, importTexHov, importTexClick),
	// fonts
	PlayfairDisplay(loadFont("assets/font/PlayfairDisplay-VariableFont_wght.ttf")),
	SourceSans3(loadFont("assets/font/SourceSans3-VariableFont_wght.ttf")),
	micross(loadFont("assets/font/micross.ttf")),
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
	autoSaveButton(offSwitch, onSwitch),
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
	
	// bookmark button
	bookmarkTextureDef(loadTexture("assets/images/BookmarkDef.png")),
	bookmarkTextureClick(loadTexture("assets/images/BookmarkClick.png")),
	bookmarkButton(bookmarkTextureDef, bookmarkTextureClick),

	// delete this word button
	deleteThisWordDef(loadTexture("assets/images/DeleteThisWordDef.png")),
	deleteThisWordHov(loadTexture("assets/images/DeleteThisWordHov.png")),
	deleteThisWordButton(deleteThisWordDef, deleteThisWordHov, SourceSans3, "DELETE THIS WORD", 36),

	// description box
	modifyTextboxTexture(loadTexture("assets/images/modifyTextbox.png")),
	headwordBox(modifyTextboxTexture, SourceSans3, 24, 32, sf::Vector2u(205, 73)),
	POSBox(modifyTextboxTexture, SourceSans3, 24, 32, sf::Vector2u(205, 153)),
	descriptionBoxTexture(loadTexture("assets/images/largeTextbox.png")),
	descriptionBox(descriptionBoxTexture, SourceSans3, 24, 6, 550 - (20 * 2), sf::Vector2u(205, 233)),
	cancelTexDef(loadTexture("assets/images/CancelTexDef.png")),
	cancelTexHov(loadTexture("assets/images/CancelTexHov.png")),
	cancelButton(cancelTexDef, cancelTexHov),
	addTexDef(loadTexture("assets/images/AddTexDef.png")),
	addTexHov(loadTexture("assets/images/AddTexHov.png")),
	addButton(addTexDef, addTexHov)








{
	// reserve word4Def for faster insert at the beginning
	word4Def.reserve(1000);
	
	// SFML
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
	favouriteButton.setPosition(sf::Vector2u(855 - SHADOWHOR, 210));

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
	emojiSprite.setScale(0.76923076923, 0.76923076923);
	emojiSprite.setPosition(455, 405);

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

	// bookmark button
	bookmarkButton.setPosition(sf::Vector2u(855 - SHADOWHOR, 358));

	// Set up error text
	setUpErrorText();

	// Set up delete word page
	deleteThisWordButton.setPosition(sf::Vector2u(280 - SHADOWHOR, 295));
	currentWordText.setFont(SourceSans3);
	currentWordText.setCharacterSize(40);
	currentWordText.setOutlineColor(sf::Color::Black);
	currentWordText.setOutlineThickness(1.5);
	currentWordText.setStyle(sf::Text::Bold);
	currentWordText.setPosition(280, 255 - 20);
	currentWordText.setString("");

	// Set up add word page
	cancelButton.setPosition(sf::Vector2u(205, 527));
	addButton.setPosition(sf::Vector2u(663, 527));
}
void instance::operate()
{
	std::cout << "MAX: " << sf::Texture::getMaximumSize() << std::endl;
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
			operatePage3();
			drawPage3();
		}
		break;
		case 4:
		{
			operatePage4();
			drawPage4();
		}
		break;
		case 5:
		{
			operatePage5();
			drawPage5();
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
        deserializeBinaryWrapper(pRoot, word4Def);
		readFavourite(pRootFavourite);
		pCurrentFavourite = pRootFavourite;
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
//				int option = suggestedcontent.returnmode(windowInstance);
				if (searchButton.isClicked(windowInstance)) // static function
				{
					displayHistory = false;
					historyIndex = 0;
					std::string temp = searchBox.getString();
					history.push_back(temp);
					writeHistory(temp);
					handleSearchSignal(temp);
				}
				else if (historyButton.isClicked(windowInstance))
				{
                    if (!loadHistory)
                    {
                        readHistory(history);
                        loadHistory = true;
                    }
					displayHistory = true;
					displayFavourite = false;
					handleHistory();
				}
//				else if (option != -1)
//				{
//					displayHistory = false;
//					historyIndex = 0;
//					std::string temp = suggestedcontent.getcategory(option);
//					history.push_back(temp);
//					writeHistory(temp);
//					handleSearchSignal(temp);
//				}
				else if (nextPageButton.isClicked(windowInstance))
				{
					if (definitionNum < (int)searchResult.size() - 1)
					{
						++definitionNum;
						POSString = searchResult[definitionNum].first;
						descriptionString = searchResult[definitionNum].second;
						description.setString(descriptionString);
						wrappedDescription = false;
					}
				}
				else if (prevPageButton.isClicked(windowInstance))
				{
					if (definitionNum > 0)
					{
						--definitionNum;
						POSString = searchResult[definitionNum].first;
						descriptionString = searchResult[definitionNum].second;
						description.setString(descriptionString);
						wrappedDescription = false;
					}
				}
				else if (favouriteButton.isClicked(windowInstance))
				{
					printf("[DEBUG] trying to display favourite\n");
					if (pCurrentFavourite) 
					{
						displayFavourite = true;
						handleFavourite();
					}
					else	
					{
						displayFavourite = false;
						displayDef = false;
					}
					displayHistory = false;
				}
				else if (bookmarkButton.isClicked(windowInstance) && displayDef)
				{
					if (existInList(pRootFavourite, headWordString))
					{
						printf("turning off\n");
						bookmarkButton.setMode(false);
                        if (pCurrentFavourite && pCurrentFavourite -> pNext)
						{
                            printf("[DEBUG] moving to favourite down\n");
							pCurrentFavourite = pCurrentFavourite -> pNext;
						}
						else if (pCurrentFavourite && pCurrentFavourite -> pPrev)
						{
							printf("[DEBUG] moving to favourite up\n");
							pCurrentFavourite = pCurrentFavourite -> pPrev;
						}
						deleteLinkedList(pRootFavourite, headWordString);
						pCurrentFavourite = pRootFavourite;
						writeFavourite(pRootFavourite);
						if (!pRootFavourite && displayFavourite)
						{
							printf("[DEBUG] end displaying favourite\n");
							displayDef = false;
							displayFavourite = false;
						}
						if (displayFavourite)	handleFavourite();
					}
					else
					{
						bookmarkButton.setMode(true);
						printf("[DEBUG] new favourite\n");
						insertLinkedList(pRootFavourite, headWordString);
						pCurrentFavourite = pRootFavourite;
						writeFavourite(pRootFavourite);
						// handleFavourite();
					}
				}
				else if ((displayHistory || displayFavourite) && displayDef)
				{
					if (displayHistory)
					{
						if (pageUpButton.isClicked(windowInstance))
						{
							if (historyIndex > 0)
							{
								--historyIndex;
								handleHistory();
							}
						}
						else if (pageDownButton.isClicked(windowInstance))
						{
							if (historyIndex < (int)history.size() - 1)
							{
								++historyIndex;
								handleHistory();
							}
						}
						
					}
					else if (displayFavourite)
					{
						if (pageUpButton.isClicked(windowInstance))
						{
							if (pCurrentFavourite -> pPrev)
							{
								pCurrentFavourite = pCurrentFavourite -> pPrev;
								handleFavourite();
							}
						}
						else if (pageDownButton.isClicked(windowInstance))
						{
							if (pCurrentFavourite -> pNext)
							{
								pCurrentFavourite = pCurrentFavourite -> pNext;
								handleFavourite();
							}
						}
					}
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
				else if (event.key.code == sf::Keyboard::R)
				{

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
//		suggestedcontent.updateoptions(searchBox.getString(), pRoot);
	}
	handleSwitchModeLogic();
	searchButton.hoverSwitchTexture(windowInstance);
	searchButton.click(windowInstance);
	historyButton.hoverSwitchTexture(windowInstance);
	historyButton.click(windowInstance);
	favouriteButton.hoverSwitchTexture(windowInstance);
	favouriteButton.click(windowInstance);
	nextPageButton.hoverSwitchTexture(windowInstance);
	prevPageButton.hoverSwitchTexture(windowInstance);
	pageUpButton.hoverSwitchTexture(windowInstance);
	pageDownButton.hoverSwitchTexture(windowInstance);
	nextPageButton.click(windowInstance);
	prevPageButton.click(windowInstance);
	pageUpButton.click(windowInstance);
	pageDownButton.click(windowInstance);
	// std::cout << headWordString << std::endl;
	if (existInList(pRootFavourite, headWordString))
	{
		// printf("[DEBUG] word is favourite\n");
		bookmarkButton.setMode(true);
	}
	else
	{
		// printf("[DEBUG] word is not favourite\n");
		bookmarkButton.setMode(false);
	}
	bookmarkButton.click(windowInstance, mouseControl);
}
void instance::drawPage1()
{
	windowInstance.clear();
	windowInstance.draw(baseLayerSprite);
	searchButton.draw(windowInstance);
	historyButton.draw(windowInstance);
	favouriteButton.draw(windowInstance);
	searchBox.draw(windowInstance);
	drawDefinition();
	drawSwitchMode();
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
				// printf("[DEBUG] mouse button pressed\n");
				if (importButton.isClicked(windowInstance))
				{
					displayStatus = true;
					std::string filepath = importBox.getString();
					std::cout << filepath << std::endl;

					
					std::atomic<bool> controlLoaded(false);
					std::thread loadingAnimationThread(loadingWrapper, std::ref(windowInstance), std::ref(controlLoaded));
					

					deleteWholeTrie(pRoot);
					if (CSVButton.getSelected())
					{
						if (readDatasetCSV(filepath, pRoot, word4Def))
						{
							std::cout << "[DEBUG] import successful\n";
							importStatus.setFillColor(sf::Color(128, 255, 0));
							importStatus.setString("Import Successful\n");
							if (filepath == "UnicodeEmoji")
							{
								loadEmojiImage = true;
							}
							else
							{
								loadEmojiImage = false;
							}
						}
						else
						{
							std::cout << "[DEBUG] import failed\n";
							importStatus.setFillColor(sf::Color(255, 153, 0));
							importStatus.setString("Import Failed\n");
						}
					}
					else if (TXTButton.getSelected())
					{
						if (readDatasetTXT(filepath, pRoot))
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
						if (filepath == "UnicodeEmoji")
						{
							printf("[DEBUG] EMOJI\n");
							loadEmojiImage = true;
							std::cout << Search(pRoot, "U+1F600")[0].second << std::endl;
						}
						else
						{
							loadEmojiImage = false;
						}
					}
					else
					{
						importStatus.setFillColor(sf::Color(255, 153, 0));
						importStatus.setString("Import Failed - Format not chosen\n");
						loadEmojiImage = false;
					}

					controlLoaded.store(true);
					printf("[DEBUG] done loading!\n");
					loadingAnimationThread.join();




					loadDefinition = false;
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
void instance::operatePage3()
{
	if (!loadDefinition)
	{
		
		// DO NOT DELETE this is another approach
		std::atomic<bool> controlLoaded(false);
		std::thread loadingAnimationThread(loadingWrapper, std::ref(windowInstance), std::ref(controlLoaded));
		invertedIndex.clear();
		invertIndexTrie(pRoot, invertedIndex);
		controlLoaded.store(true);
		printf("[DEBUG] done loading!\n");
		loadingAnimationThread.join();
		loadDefinition = true;


		// DO NOT DELETE this is another approach
		// bool controlLoaded = false;
		// void (*loadDef)(trieNode*, HashMap&, bool&) = invertIndexTrie;
		// std::thread loadDefinitionWorker(loadDef, pRoot, std::ref(invertedIndex), std::ref(controlLoaded));
		// loadingWrapper(windowInstance, controlLoaded);
		// // only wait for the worker thread to join when the window is not closed during loading time
		// if (windowInstance.isOpen())
		// {
		// 	loadDefinitionWorker.join();
		// }
		// loadDefinition = true;
	}
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
				if (searchButton.isClicked(windowInstance))
				{
					std::string temp = searchBox.getString();
					std::vector<std::string> result = searchByDef(temp, invertedIndex);
					sortByDefLength(result, pRoot);
					std::cout << "SORTED" << std::endl;
					for (auto word : result)
					{
						std::cout << word << std::endl;
					}
					if (result.size() > 0)
					{
						std::cout << result[0] << std::endl;
						handleSearchSignal(result[0]);
					}
				}
				else if (nextPageButton.isClicked(windowInstance))
				{
					if (definitionNum < (int)searchResult.size() - 1)
					{
						++definitionNum;
						POSString = searchResult[definitionNum].first;
						descriptionString = searchResult[definitionNum].second;
						description.setString(descriptionString);
						wrappedDescription = false;
					}
				}
				else if (prevPageButton.isClicked(windowInstance))
				{
					if (definitionNum > 0)
					{
						--definitionNum;
						POSString = searchResult[definitionNum].first;
						descriptionString = searchResult[definitionNum].second;
						description.setString(descriptionString);
						wrappedDescription = false;
					}
				}
				else if (bookmarkButton.isClicked(windowInstance) && displayDef)
				{
					if (existInList(pRootFavourite, headWordString))
					{
						printf("turning off\n");
						bookmarkButton.setMode(false);
                        if (pCurrentFavourite && pCurrentFavourite -> pNext)
						{
                            printf("[DEBUG] moving to favourite down\n");
							pCurrentFavourite = pCurrentFavourite -> pNext;
						}
						else if (pCurrentFavourite && pCurrentFavourite -> pPrev)
						{
							printf("[DEBUG] moving to favourite up\n");
							pCurrentFavourite = pCurrentFavourite -> pPrev;
						}
						deleteLinkedList(pRootFavourite, headWordString);
						pCurrentFavourite = pRootFavourite;
						writeFavourite(pRootFavourite);
						if (!pRootFavourite && displayFavourite)
						{
							printf("[DEBUG] end displaying favourite\n");
							displayDef = false;
							displayFavourite = false;
						}
						if (displayFavourite)	handleFavourite();
					}
					else
					{
						bookmarkButton.setMode(true);
						printf("[DEBUG] new favourite\n");
						insertLinkedList(pRootFavourite, headWordString);
						pCurrentFavourite = pRootFavourite;
						writeFavourite(pRootFavourite);
						// handleFavourite();
					}
				}
			}
			break;
			case sf::Event::KeyPressed:
			{
				if (event.key.code == sf::Keyboard::Return)
				{
					std::string temp = searchBox.getString();
					std::vector<std::string> result = searchByDef(temp, invertedIndex);
					sortByDefLength(result, pRoot);
					std::cout << "SORTED" << std::endl;
					for (auto word : result)
					{
						std::cout << word << std::endl;
					}
					if (result.size() > 0)
					{
						handleSearchSignal(result[0]);
					}
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
	nextPageButton.hoverSwitchTexture(windowInstance);
	prevPageButton.hoverSwitchTexture(windowInstance);
	nextPageButton.click(windowInstance);
	prevPageButton.click(windowInstance);
	if (existInList(pRootFavourite, headWordString))
	{
		// printf("[DEBUG] word is favourite\n");
		bookmarkButton.setMode(true);
	}
	else
	{
		bookmarkButton.setMode(false);
	}
}
void instance::drawPage3()
{
	windowInstance.clear();
	windowInstance.draw(baseLayerSprite);
	searchBox.draw(windowInstance);
	searchButton.draw(windowInstance);
	drawDefinition();
	drawSwitchMode();
	windowInstance.display();
}
void instance::operatePage4()
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
				if (cancelButton.isClicked(windowInstance) && mouseControl)
				{
					mouseControl = false;
					printf("1. "); headwordBox.clear();
					printf("2. "); POSBox.clear();
					printf("3. "); descriptionBox.clear();
				}
				else if (addButton.isClicked(windowInstance) && mouseControl)
				{
					std::string newHeadword = headwordBox.getString();
					std::string newPOS = POSBox.getString();
					std::string newDescription = descriptionBox.getString();
					unwrapText(newDescription);
					addWord(newHeadword, newPOS, newDescription, pRoot, invertedIndex, word4Def);
					insert(pRoot, newHeadword, newPOS, newDescription);
					if (autoSave)
					{
						std::atomic<bool> controlLoaded(false);
						std::thread loadingAnimationThread(loadingWrapper, std::ref(windowInstance), std::ref(controlLoaded));
						serializeBinaryWrapper(pRoot);
						controlLoaded.store(true);
						printf("[DEBUG] done loading!\n");
						loadingAnimationThread.join();
					}
				}
			}
			break;
			default:
			break;
		}
		headwordBox.handleInputLogic(event, windowInstance);
		POSBox.handleInputLogic(event, windowInstance);
		descriptionBox.handleInputLogic(event, windowInstance);
	}
	cancelButton.hoverSwitchTexture(windowInstance);
	addButton.hoverSwitchTexture(windowInstance);
	hoverSubModes();
	handleSwitchModeLogic();
	switchPage();
}
void instance::drawPage4()
{
	windowInstance.clear();
	windowInstance.draw(baseLayerSprite);
	headwordBox.draw(windowInstance);
	POSBox.draw(windowInstance);
	descriptionBox.draw(windowInstance);
	cancelButton.draw(windowInstance);
	addButton.draw(windowInstance);
	drawSwitchMode();
	drawSubModes();
	windowInstance.display();
}
void instance::operatePage5()
{
	if (!loadAutoSave)
	{
		loadAutoSaveSetting();
		loadAutoSave = true;
	}
	if (!getWordToDelete)
	{
		if (headWordString != "")
		{
			currentWordText.setString("Current word: " + headWordString);
		}
		else
		{
			currentWordText.setString("No current word!");
		}
		getWordToDelete = true;
	}
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
				if (deleteThisWordButton.isClicked(windowInstance) && mouseControl)
				{
					mouseControl = false;
					if (headWordString != "")
					{
						removeAllCase(headWordString, pRoot, word4Def, invertedIndex);
						if (autoSave)
						{
							std::cout << "auto-saving\n";
							std::atomic<bool> controlLoaded(false);
							std::thread loadingAnimationThread(loadingWrapper, std::ref(windowInstance), std::ref(controlLoaded));
							serializeBinaryWrapper(pRoot);
							controlLoaded.store(true);
							printf("[DEBUG] done loading!\n");
							loadingAnimationThread.join();
						}
					}
				}
			}
			break;
			default:
			break;
		}
	}
	hoverSubModes();
	deleteThisWordButton.hoverSwitchTexture(windowInstance);
	handleSwitchModeLogic();
}
void instance::drawPage5()
{
	windowInstance.clear();
	windowInstance.draw(baseLayerSprite);
	drawSwitchMode();
	drawSubModes();
	windowInstance.draw(currentWordText);
	deleteThisWordButton.draw(windowInstance);
	windowInstance.display();
}
void instance::operatePage7()
{
	if (!loadAutoSave)
	{
		loadAutoSaveSetting();
		loadAutoSave = true;
	}
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
			if (serializeButton.isClicked(windowInstance) && mouseControl)
			{
				
				mouseControl = false;


				std::atomic<bool> controlLoaded(false);
				std::thread loadingAnimationThread(loadingWrapper, std::ref(windowInstance), std::ref(controlLoaded));
				serializeBinaryWrapper(pRoot);
				controlLoaded.store(true);
				printf("[DEBUG] done loading!\n");
				loadingAnimationThread.join();


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
			if (deserializeButton.isClicked(windowInstance) && mouseControl)
			{
				mouseControl = false;


				std::atomic<bool> controlLoaded(false);
				std::thread loadingAnimationThread(loadingWrapper, std::ref(windowInstance), std::ref(controlLoaded));
				deleteWholeTrie(pRoot);
				deserializeBinaryWrapper(pRoot, word4Def);
				controlLoaded.store(true);
				printf("[DEBUG] done loading!\n");
				loadingAnimationThread.join();
				loadDefinition = false;



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
	if (!loadGameMode)
	{
		setUpGameModeAnimation();
		loadGameMode = true;
	}
	while (windowInstance.pollEvent(event))
	{
		switch (event.type)
		{
		case sf::Event::Closed:
		windowInstance.close();
		break;
		case sf::Event::MouseButtonPressed:
		{
			if (gameMode1st.isClicked(windowInstance))
			{
				gameMode = 1;
				resetGameMode(1);
				if (pRoot) 
				{
					for (int i = 0; i < 20; ++i)
					{
						std::cout << pRoot << std::endl;
						std::pair<trieNode*, std::string> random;
						random.second = "";
						random = pickarandomword(pRoot);
						std::cout << "The random word is: " << random.second << std::endl;
						handleSearchSignal(random.second);
						if (random.second == "")	displayDef = false;
						else if (random.second != "")	
						{
							displayDef = true;
							break;
						}
					}
				}
			}
			else if (gameMode2nd.isClicked(windowInstance))
			{
				gameMode = 2;
				resetGameMode(2);
				correctAnswerString = randomWord4Def(word4Def);
				Change2Lowercase(correctAnswerString);
				std::cout << "[DEBUG] the correct answer is: " << correctAnswerString << std::endl;
				std::cout << "word with 4 def: " << correctAnswerString << std::endl;
				if (correctAnswerString != "")
					handleSearchSignal(correctAnswerString);
			}
			else if (gameMode3rd.isClicked(windowInstance))
			{
				gameMode = 3;
				resetGameMode(3);
				if (pRoot) 
				{
					int numWord = 0;
					for (int i = 0; i < 500; ++i)
					{
						std::pair<trieNode*, std::string> random;
						random.second = "";
						random = pickarandomword(pRoot);
						std::cout << "The random word is: " << random.second << std::endl;
						if (random.second == "")	displayDef = false;
						else if (random.second != "")	
						{
							multipleChoices[numWord] = random.second;
							++numWord;
						}
						if (numWord == 4)
						{
							validMultipleChoices = true;
							break;
						}
					}
					std::cout << "the 4 words are: \n";
					for (int i = 0; i < 4; ++i)
					{
						std::cout << multipleChoices[i] << std::endl;
					}
					
					correctAnswerString = multipleChoices[randomNum(0, 4)];
					std::cout << "[DEBUG] the correct answer is: " << correctAnswerString << std::endl;
					answerButton1st.setText(multipleChoices[0]);
					answerButton2nd.setText(multipleChoices[1]);
					answerButton3rd.setText(multipleChoices[2]);
					answerButton4th.setText(multipleChoices[3]);

					handleSearchSignal(correctAnswerString);
				}
			}
			else if (checkAnswerButton.isClicked(windowInstance) && gameMode == 2)
			{
				std::string temp = gameSearchBox.getString();
				if (temp == correctAnswerString)
				{
					correctAnswer = true;
					wrongAnswer = false;
					congratulationsAnimation.resetAnimation();
					std::cout << "CORRECT ANSWER\n";
				}
				else
				{
					wrongAnswer = true;
					correctAnswer = false;
				}
			}
			else if (gameMode == 3)
			{
				if (answerButton1st.isClicked(windowInstance))
				{
					if (multipleChoices[0] == correctAnswerString)
					{
						congratulationsAnimation.resetAnimation();
						correctAnswer = true;
						wrongAnswer = false;
					}
					else
					{
						wrongAnswer = true;
						correctAnswer = false;
					}
					printf("[DEBUG] chose\n");
				}
				else if (answerButton2nd.isClicked(windowInstance))
				{
					if (multipleChoices[1] == correctAnswerString)
					{
						congratulationsAnimation.resetAnimation();
						correctAnswer = true;
						wrongAnswer = false;
					}
					else
					{
						wrongAnswer = true;
						correctAnswer = false;
					}
					printf("[DEBUG] chose\n");
				}
				else if (answerButton3rd.isClicked(windowInstance))
				{
					if (multipleChoices[2] == correctAnswerString)
					{
						congratulationsAnimation.resetAnimation();
						correctAnswer = true;
						wrongAnswer = false;
					}
					else
					{
						wrongAnswer = true;
						correctAnswer = false;
					}
					printf("[DEBUG] chose\n");
				}
				else if (answerButton4th.isClicked(windowInstance))
				{
					if (multipleChoices[3] == correctAnswerString)
					{
						congratulationsAnimation.resetAnimation();
						correctAnswer = true;
						wrongAnswer = false;
					}
					else
					{
						wrongAnswer = true;
						correctAnswer = false;
					}
					printf("[DEBUG] chose\n");
				}
			}
			else if (nextPageButton.isClicked(windowInstance))
			{
				if (definitionNum < (int)searchResult.size() - 1)
				{
					++definitionNum;
					POSString = searchResult[definitionNum].first;
					descriptionString = searchResult[definitionNum].second;
					description.setString(descriptionString);
					wrappedDescription = false;
				}
			}
			else if (prevPageButton.isClicked(windowInstance))
			{
				if (definitionNum > 0)
				{
					--definitionNum;
					POSString = searchResult[definitionNum].first;
					descriptionString = searchResult[definitionNum].second;
					description.setString(descriptionString);
					wrappedDescription = false;
				}
			}
			else if (bookmarkButton.isClicked(windowInstance) && displayDef)
			{
				if (existInList(pRootFavourite, headWordString))
				{
					printf("turning off\n");
					bookmarkButton.setMode(false);
					if (pCurrentFavourite && pCurrentFavourite -> pNext)
					{
						printf("[DEBUG] moving to favourite down\n");
						pCurrentFavourite = pCurrentFavourite -> pNext;
					}
					else if (pCurrentFavourite && pCurrentFavourite -> pPrev)
					{
						printf("[DEBUG] moving to favourite up\n");
						pCurrentFavourite = pCurrentFavourite -> pPrev;
					}
					deleteLinkedList(pRootFavourite, headWordString);
					pCurrentFavourite = pRootFavourite;
					writeFavourite(pRootFavourite);
					if (!pRootFavourite && displayFavourite)
					{
						printf("[DEBUG] end displaying favourite\n");
						displayDef = false;
						displayFavourite = false;
					}
					if (displayFavourite)	handleFavourite();
				}
				else
				{
					bookmarkButton.setMode(true);
					printf("[DEBUG] new favourite\n");
					insertLinkedList(pRootFavourite, headWordString);
					pCurrentFavourite = pRootFavourite;
					writeFavourite(pRootFavourite);
					// handleFavourite();
				}
			}
			
		}
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
		gameSearchBox.handleInputLogic(event, windowInstance);
	}

	moveKnight();
	knightAnimation.updateAnimation(deltaTime);
	sceneryAnimation.updateAnimation(deltaTime);
	penguinAnimation.updateAnimation(deltaTime);
	rainbowStarAnimation.updateAnimation(deltaTime);
	congratulationsAnimation.updateAnimation(deltaTime);
	gameMode1st.hoverSwitchTexture(windowInstance);
	gameMode2nd.hoverSwitchTexture(windowInstance);
	gameMode3rd.hoverSwitchTexture(windowInstance);
	if (existInList(pRootFavourite, headWordString))
	{
		// printf("[DEBUG] word is favourite\n");
		bookmarkButton.setMode(true);
	}
	else
	{
		bookmarkButton.setMode(false);
	}
	nextPageButton.hoverSwitchTexture(windowInstance);
	nextPageButton.click(windowInstance);
	prevPageButton.hoverSwitchTexture(windowInstance);
	prevPageButton.click(windowInstance);
	exitButton.hoverSwitchTexture(windowInstance);
	checkAnswerButton.hoverSwitchTexture(windowInstance);
	answerButton1st.hoverSwitchTexture(windowInstance);
	answerButton2nd.hoverSwitchTexture(windowInstance);
	answerButton3rd.hoverSwitchTexture(windowInstance);
	answerButton4th.hoverSwitchTexture(windowInstance);
	switchPage();
}
void instance::drawPage9()
{
	windowInstance.clear(sf::Color(150, 150, 150));
	sceneryAnimation.draw(windowInstance);
	drawDefinition();
	gameMode1st.draw(windowInstance);
	gameMode2nd.draw(windowInstance);
	gameMode3rd.draw(windowInstance);
	if (correctAnswer)
	{
		congratulationsAnimation.draw(windowInstance);
	}
	if (wrongAnswer)
	{
		windowInstance.draw(wrongAnswerSprite);
	}
	if (gameMode == 2)
	{
		checkAnswerButton.draw(windowInstance);
		gameSearchBox.draw(windowInstance);
	}
	if (gameMode == 3 && validMultipleChoices)
	{
		answerButton1st.draw(windowInstance);
		answerButton2nd.draw(windowInstance);
		answerButton3rd.draw(windowInstance);
		answerButton4th.draw(windowInstance);
	}
	penguinAnimation.draw(windowInstance);
	rainbowStarAnimation.draw(windowInstance);
	exitButton.draw(windowInstance);
	knightAnimation.draw(windowInstance);
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
				displayFavourite = false;
			}
		}
		else if (settingModeButton.isClicked(windowInstance))
		{
			if (page != 2)
			{
				printf("[DEBUG] moving to page 2\n");
				page = 2;
				modeButtonActive = false;
				pageChange = true;
			}
		}
		else if (definitionModeButton.isClicked(windowInstance))
		{
			if (page != 3)
			{
				printf("[DEBUG] moving to page 3\n");
				page = 3;
				modeButtonActive = false;
				pageChange = true;
			}
		}
		else if (gameModeButton.isClicked(windowInstance))
		{
			// printf("[DEBUG] pressing page 9\n");
			if (page >= 1 && page <= 8)
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
		else if (deleteModeButton.isClicked(windowInstance) && mouseControl)
		{
			if (page == 2 || (page >= 4 && page <= 8 && page != 5))
			{
				printf("[DEBUG] changing to page 5\n");
				page = 5;
				getWordToDelete = false;
				pageChange = true;
			}
		}
		else if (addModeButton.isClicked(windowInstance) && mouseControl)
		{
			if (page == 2 || (page >= 4 && page <= 8 && page != 4))
			{
				headwordBox.clear();
				POSBox.clear();
				descriptionBox.clear();
				printf("[DEBUG changing to page 4\n]");
				page = 4;
				pageChange = true;
			}
		}
	}
	if (page == 9 && exitButton.isClicked(windowInstance))
	{
		gameMode = 0;
		page = 1;
		pageChange = true;
		printf("[DEBUG] exiting game mode\n");
	}
	if (pageChange)
	{
		// printf("[DEBUG] page changed\n");
		displayDef = false;
		displayFavourite = false;
		displayHistory = false;
		mouseControl = false;
		searchBox.clear();
		importBox.clear();
		pageChange = false;
		definitionNum = 0;
		historyIndex = 0;
		pCurrentFavourite = pRootFavourite;
		gameMode = 0;
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
	Change2Uppercase(headWordString);
	headword.setString(headWordString);
	POS.setString(POSString);
	// description.setString(descriptionString); is moved to 
	// handleSearchSignal(std::string input) and
	// to event-loops (prev/next page button clicked when
	// event.type == sf::Event::MouseButtonPressed)
	// for wrapText to work properly
	// (because setString reset the sf::Text object to be non-wrapped)
	if (!wrappedDescription)
	{
		printf("[DEBUG] wrapping\n");
		if (wrapText(description, 814, 4))
		{
			std::string temp = description.getString();
			temp = temp + "... For more information, refer to the dataset.";
			description.setString(temp);
		}
		wrappedDescription = true;
		printf("[DEBUG] wrapped\n");
	}
	if (gameMode != 2 && gameMode != 3)
		windowInstance.draw(headword);
	windowInstance.draw(POS);
	windowInstance.draw(description);
	if (loadEmojiImage && POSString.substr(0, 14) == "emoji number: ")
	{
		windowInstance.draw(emojiSprite);
	}
	if (definitionNum > 0)	prevPageButton.draw(windowInstance);
	if (definitionNum < (int)searchResult.size() - 1)	nextPageButton.draw(windowInstance);
	if (displayDef)	bookmarkButton.draw(windowInstance);
	// page up/page down and error message for history and favourite
	if (displayHistory || displayFavourite)
	{
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
			if (numberOfResult == 0)
			{
				// printf("[DEBUG] drawing error message\n");
				
				windowInstance.draw(wordNotInThisDataSet);
			}
		}
		if (displayFavourite)
		{
			if (pCurrentFavourite -> pPrev)
			{
				pageUpButton.draw(windowInstance);
			}
			if (pCurrentFavourite -> pNext)
			{
				pageDownButton.draw(windowInstance);
			}
			if (numberOfResult == 0)
			{
				// printf("[DEBUG] drawing error message\n");
				windowInstance.draw(wordNotInThisDataSet);
			}
		}
	}
}

void instance::loadAutoSaveSetting()
{
	bool temp = false;
	std::ifstream fin;
	fin.open("settings/auto-save.txt");
	fin >> temp;
	fin.close();
	autoSave = temp;
	autoSaveButton.setMode(autoSave);
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
	std::cout << input << std::endl;
	searchResult = Search(pRoot, input);
	numberOfResult = (int)searchResult.size();
	std::cout << "[DEBUG] - number of result is " << numberOfResult << std::endl;
	if (numberOfResult > 0)
	{
		headWordString = input;
		POSString = searchResult[definitionNum].first;
		descriptionString = searchResult[definitionNum].second;
		description.setString(descriptionString);
		displayDef = true;
		wrappedDescription = false;
	}
	else if (displayHistory || displayFavourite)
	{
		headWordString = input;
		description.setString(descriptionString);
		displayDef = true;
		wrappedDescription = false;
	}
	else	displayDef = false;
	std::cout << "[DEBUG] emoji state is " << loadEmojiImage << std::endl;
	if (loadEmojiImage)
	{
		if (POSString.substr(0, 14) != "emoji number: ");
		else
		{
			emojiTexture.loadFromFile("dataset/Apple/" + std::to_string(getEmojiNumber(POSString)) + ".png");
			emojiTexture.setSmooth(true);
			emojiSprite.setTexture(emojiTexture, true);
		}
	}
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

void instance::handleFavourite()
{
	resetSearchResult();
	if (displayFavourite)
	{
		if (pCurrentFavourite != nullptr)
		{
			std::string temp = pCurrentFavourite -> data;
			printf("[DEBUG] current favourite word is: %s\n", temp.c_str());
			handleSearchSignal(temp);
		}
		else
		{
			printf("[DEBUG] current is nullptr\n");
			displayFavourite = false;
			displayDef = false;
		}
	}
}

void instance::initiateSearch()
{
	displayHistory = false;
	displayFavourite = false;
	historyIndex = 0;
	pCurrentFavourite = pRootFavourite;
	std::string temp = searchBox.getString();
	handleSearchSignal(temp);
}

void instance::setUpErrorText()
{
	wordNotInThisDataSet.setFont(micross);
	wordNotInThisDataSet.setFillColor(sf::Color(247, 41, 6));
	wordNotInThisDataSet.setCharacterSize(20);
	wordNotInThisDataSet.setStyle(sf::Text::Style::Bold);
	wordNotInThisDataSet.setString("Error: this word is not in the current dataset\n");
	wordNotInThisDataSet.setPosition(73.0f, 455.0f);
}

void instance::moveKnight()
{
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
}

void instance::resetGameMode(int mode)
{
	displayDef = false;
	correctAnswer = false;
	wrongAnswer = false;
	switch (mode)
	{
	case 2:
	{
		correctAnswerString = "";
		congratulationsAnimation.setPosition(sf::Vector2u(325, 287));
		wrongAnswerSprite.setPosition(430, 260);
	}
	break;
	case 3:
	{
		correctAnswerString = "";
		for (int i = 0; i < 4; ++i)
		{
			multipleChoices[i] = "";
		}
		congratulationsAnimation.setPosition(sf::Vector2u(214, 20));
		wrongAnswerSprite.setPosition(319, 215);
	}
		break;
	
	default:
		break;
	}
}

void instance::setUpGameModeAnimation()
{

	// Set up animations
	penguinTexture.loadFromFile("assets/images/sprPenguinP.png");
	penguinAnimation.setTextureImageCount(penguinTexture, sf::Vector2u(8, 3));
	penguinAnimation.setSwitchTime(0.23f);
	rainbowStarTexture.loadFromFile("assets/images/Magicalrainbowstar.png");
	rainbowStarAnimation.setTextureImageCount(rainbowStarTexture, sf::Vector2u(sf::Vector2u(24, 1)));
	rainbowStarAnimation.setSwitchTime(0.04f);
	scenery.loadFromFile("assets/images/scenery.png");
	sceneryAnimation.setTextureImageCount(scenery, sf::Vector2u(19, 1));
	sceneryAnimation.setSwitchTime(0.15f);
	knightTexture.loadFromFile("assets/images/_Run.png");
	knightAnimation.setTextureImageCount(knightTexture, sf::Vector2u(10, 1));
	knightAnimation.setSwitchTime(0.1f);
	congratulationsTexture.loadFromFile("assets/images/Congratulations.png");
	congratulationsAnimation.setTextureImageCount(congratulationsTexture, sf::Vector2u(1, 30));
	congratulationsAnimation.setSwitchTime(0.1f);

	penguinAnimation.animationSprite.setScale(3, 3);
	penguinAnimation.setPosition(sf::Vector2u(0, 360 - (penguinAnimation.animationSprite.getGlobalBounds().height) / penguinAnimation.imageCount.y));
	rainbowStarAnimation.animationSprite.setScale(3, 3);
	rainbowStarAnimation.setPosition(sf::Vector2u(960 - (rainbowStarAnimation.animationSprite.getGlobalBounds().width) / rainbowStarAnimation.imageCount.x - 20,
	360 - (rainbowStarAnimation.animationSprite.getGlobalBounds().height) / rainbowStarAnimation.imageCount.y));
	sceneryAnimation.animationSprite.setScale(960 / sceneryAnimation.animationSprite.getGlobalBounds().width * sceneryAnimation.imageCount.x,
	720 / sceneryAnimation.animationSprite.getGlobalBounds().height);
	knightAnimation.animationSprite.setScale(-1.0f, 1.0f);
	knightAnimation.setPosition(sf::Vector2u(1100, 630));

	// wrong answer icon
	wrongAnswerTexture.loadFromFile("assets/images/WrongAnswerTexture.png");
	wrongAnswerSprite.setTexture(wrongAnswerTexture);

	// Set up buttons
	exitTexture.loadFromFile("assets/images/ExitGameMode.png");
	exitButton.shadow = false;
	exitButton.setUpHoverText(exitTexture, exitTexture, PatuaOne, "EXIT", 30);
	exitButton.setPosition(sf::Vector2u(364, 675));

	checkAnswerTextureDef.loadFromFile("assets/images/CheckResultTexture.png");
	checkAnswerTextureHov.loadFromFile("assets/images/CheckResultTextureHov.png");
	checkAnswerButton.setUpHoverText(checkAnswerTextureDef, checkAnswerTextureHov, PatuaOne, "", 24);
	checkAnswerButton.setPosition(sf::Vector2u(720, 20));

	gameModeDef.loadFromFile("assets/images/GameModeTexture.png");
	gameMode1st.shadow = false;
	gameMode2nd.shadow = false;
	gameMode3rd.shadow = false;
	gameMode1st.setUpHoverText(gameModeDef, gameModeDef, PatuaOne, "Random Word", 24);
	gameMode1st.setTextFillColor(sf::Color::Black);
	gameMode1st.setPosition(sf::Vector2u(720, 105));
	gameMode2nd.setUpHoverText(gameModeDef, gameModeDef, PatuaOne, "Game Mode 2", 24);
	gameMode2nd.setTextFillColor(sf::Color::Black);
	gameMode2nd.setPosition(sf::Vector2u(720, 190));
	gameMode3rd.setUpHoverText(gameModeDef, gameModeDef, PatuaOne, "Game Mode 3", 24);
	gameMode3rd.setTextFillColor(sf::Color::Black);
	gameMode3rd.setPosition(sf::Vector2u(720, 275));

	answerButtonTexture.loadFromFile("assets/images/pickOneTexture.png");
	answerButton1st.shadow = false;
	answerButton2nd.shadow = false;
	answerButton3rd.shadow = false;
	answerButton4th.shadow = false;
	answerButton1st.setUpHoverText(answerButtonTexture, answerButtonTexture, PatuaOne, "lorem", 24);
	answerButton2nd.setUpHoverText(answerButtonTexture, answerButtonTexture, PatuaOne, "lorem", 24);
	answerButton3rd.setUpHoverText(answerButtonTexture, answerButtonTexture, PatuaOne, "lorem", 24);
	answerButton4th.setUpHoverText(answerButtonTexture, answerButtonTexture, PatuaOne, "lorem", 24);
	answerButton1st.setPosition(sf::Vector2u(30, 190));
	answerButton2nd.setPosition(sf::Vector2u(450, 190));
	answerButton3rd.setPosition(sf::Vector2u(30, 275));
	answerButton4th.setPosition(sf::Vector2u(450, 275));
	answerButton1st.setTextFillColor(sf::Color::Black);
	answerButton2nd.setTextFillColor(sf::Color::Black);
	answerButton3rd.setTextFillColor(sf::Color::Black);
	answerButton4th.setTextFillColor(sf::Color::Black);

	gameSearchBoxTexture.loadFromFile("assets/images/gameSearchBox.png");
	gameSearchBox.setUp(gameSearchBoxTexture, SourceSans3, 24, 40, sf::Vector2u(30 - SHADOWHOR, 20));
}



instance::~instance()
{
	deallocateLinkedList(pRootFavourite);
	deleteWholeTrie(pRoot);
}
