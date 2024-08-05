#pragma once

#include <SFML/Graphics.hpp>

/// @brief get the number of '\newline' in the string, add 1 to get the number of lines
/// @param input 
/// @return number of '\newline' in the string
int countNewLines(const std::string& input);
bool wrapText(sf::Text& inputText, int width, int lineLimit);
void unwrapText(std::string& text);