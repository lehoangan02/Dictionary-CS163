#include <string>
#include <ctime>
#include <random>
#include "wrapping.hpp"

/// @brief wrap sf::Text object to according to a certain width, with a line limit
/// @param inputText 
/// @param width 
/// @param lineLimit 
/// @return true if linelimit is  achieved, false if otherwise
bool wrapText(sf::Text& inputText, int width, int lineLimit)
{
    std::string str = inputText.getString();
    std::string result;
    int space = -1; // index for the space bar
    int hyphen_and_newline = 0;
    int numLine = 0;
    for (int i = 0; i < str.size(); i++)
    {
        if (str[i] == ' ') space = i + hyphen_and_newline;
        result.push_back(str[i]);
        
        inputText.setString(result);
        if (inputText.getGlobalBounds().width > width)
        {
            if (space != -1)
            {
                result[space] = '\n'; // replace the space with newline
                space = -1; // reset
            }
            else
            {
                // decrease the index of insert by 1
                // from 2 to 3 and from 3 to 4
                // because width of 'j' (example) is smaller and '-'
                // this can make hyphen addition violates the condition
                // inputText.getGlobalBounds().width > width
                // examples: "jj" violates, replace with "j-\nj", but
                // "j-" still violates
                result.insert(result.size() - 3, "\n"); // add newline right before that, for very long words
                result.insert(result.size() - 4, "-"); // add additional hyphen
                hyphen_and_newline += 2; // account for the difference between str and result
            }
        }
        
        numLine = countNewLines(result) + 1;
        // printf("[DEBUG] numLine: %d\n", numLine);
        if (numLine == lineLimit) 
        {
            printf("[DEBUG] limit reached\n");
            inputText.setString(result);
            return true;
        }
    }
    inputText.setString(result);
    return false;
}

int countNewLines(const std::string& input) 
{
    int count = 0;
    for (char character : input) {
        if (character == '\n') {
            ++count;
        }
    }
    return count;
}

void unwrapText(std::string& text)
{
    for (int i = 0; i < text.size(); i++)
    {
        if (text[i] == '\n')
        {
            if (text[i - 1] == '-')
            {
                text.erase(i - 1, 2);
                
            }
            else
            {
                text[i] = ' ';
            }
        }
    }
}

int randomNum(int a, int b)
{
    std::mt19937 gen(static_cast<unsigned>(std::time(0)));
    std::uniform_int_distribution<> dist(a, b);

    return dist(gen);
}