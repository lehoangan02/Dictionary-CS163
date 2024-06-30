#include "trie.h"
#include "readDatasetCSV.hpp"
#include "removeQuotationMarkDuplicate.hpp"

//rewrite the read function as data format has been changed.

bool readDataset(std::string filename, trieNode*& pRoot)
{
    std::ifstream inputStream;
    inputStream.open(filename);
    if (!inputStream.is_open())
    {
        printf("[DEBUG] - file not found!\n");
        return false;
    }
    std::string line = "";
    getline(inputStream, line);
    std::vector<std::pair<std::string, std::string>> definitionVec;
    std::string word = ""; std::string previousWord = "";
    std::string POS;
    std::string description;
    while(getline(inputStream, line))
    {
        std::stringstream tempStream(line);
        std::string tempString = "";
        
        // read the keyword
        getline(tempStream, word, ',');
        Change2Lowercase(word);
        std::cout << "[DEBUG]" << word << " ";

        // read the count (not used in our dictionary)
        getline(tempStream, tempString, ',');

        // read the position of speech
        getline(tempStream, POS, ',');
        if (POS.length() >= 6)
            POS = POS.substr(3, POS.length() - 6);
        std::cout << POS << " ";

        // read the description
        getline(tempStream, description, ',');
        if (description.length() >= 6)
            description = description.substr(3, description.length() - 7);
        removeQuotationMarkDuplicate(description);
        std::cout << description << std::endl;

        // if word is the same, insert the word into vector
        // if word is new, then insert the vector (which contain the previous word)
        if (word != previousWord && previousWord != "")
        {
            std::cout << "[DEBUG] end of vec\n";
            insert(pRoot, previousWord, definitionVec);
            for (int i = 0; i < definitionVec.size(); ++i)
            {
                // std::cout << "[DEBUG]" << previousWord << " ";
                // std::cout << definitionVec[i].first << " ";
                // std::cout << definitionVec[i].second << std::endl;
            }
            definitionVec.clear();
            definitionVec.push_back(std::pair<std::string, std::string>{POS, description});
        }
        else
        {
            definitionVec.push_back(std::pair<std::string, std::string>{POS, description});
        }
        line = "";
        previousWord = word;
    }
    // insert the last vector
    if (word != "")
    {
        // for (int i = 0; i < definitionVec.size(); ++i)
        // {
        //     std::cout << "[DEBUG]" << word << " ";
        //     std::cout << definitionVec[i].first << " ";
        //     std::cout << definitionVec[i].second << std::endl;
        // }
        insert(pRoot, previousWord, definitionVec);
    }
    return true;
}