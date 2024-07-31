#include "trie.h"
#include "readDataset.hpp"
#include "removeQuotationMarkDuplicate.hpp"

bool readDatasetCSV(std::string filename, trieNode*& pRoot, std::vector<std::string>& wordFourDef)
{
    int count4Def = 0;
    std::ifstream inputStream;
    inputStream.open("dataset/" + filename + ".csv");
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
        // std::cout << "[DEBUG]" << word << " ";

        // read the count (not used in our dictionary)
        getline(tempStream, tempString, ',');

        // read the position of speech
        getline(tempStream, POS, ',');
        if (POS.length() >= 6)
            POS = POS.substr(3, POS.length() - 6);
        // std::cout << POS << " ";

        // read the description
        getline(tempStream, description, ',');
        if (description.length() >= 6)
            description = description.substr(3, description.length() - 7);
        removeQuotationMarkDuplicate(description);
        // std::cout << description << std::endl;

        // if word is the same, insert the word into vector
        // if word is new, then insert the vector (which contain the previous word)
        if (word != previousWord && previousWord != "")
        {
            // std::cout << "[DEBUG] end of vec\n";
            insert(pRoot, previousWord, definitionVec);
            if (definitionVec.size() >= 4)
            {
                ++count4Def;
                wordFourDef.push_back(word);
            }
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
        if (definitionVec.size() >= 4)
        {
            ++count4Def;
            wordFourDef.push_back(word);
        }
    }
    std::cout << "count word4Def: " << count4Def << std::endl;
    return true;
}

bool readDatasetTXT(const std::string& filename, trieNode*& pRoot)
{
    std::ifstream fin;
    fin.open("dataset/" + filename + ".txt");
    if (!fin.is_open())
    {
        std::cerr << "Error:: Unable to open file!" << std::endl;
        return false;
    }
    std::string line = "";
    while (getline(fin, line))
    {
        std::stringstream split(line);
        std::string word, pos, def;
        getline(split, word, '|');
        getline(split, pos, '|');
        getline(split, def);
        /*std::cout << word << " (" << pos << ") " << std::endl;
        std::cout << "- " << def << std::endl;*/
        insert(pRoot, word, pos, def);
    }
    std::cout << "File imported successfully!" << std::endl;
    fin.close();
    return true;
}

