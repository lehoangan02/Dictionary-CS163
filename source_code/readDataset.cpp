#include "trie.h"
#include "readDataset.hpp"
#include "removeQuotationMarkDuplicate.hpp"

bool readDatasetCSV(const std::string& filename, TrieNode*& pRoot, std::vector<std::string>& wordFourDef)
{
    int count4Def = 0;
    std::ifstream inputStream;
    inputStream.open("dataset/" + filename + ".csv");
    std::cout << "dataset/" + filename + ".csv" << std::endl;
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
        // std::cout << "[DEBUG]" << word << " ";

        // read the count (not used in our dictionary)
        getline(tempStream, tempString, ',');

        // read the position of speech
        getline(tempStream, POS, ',');

        // read the description
        getline(tempStream, description, ',');

        // if word is the same, insert the word into vector
        // if word is new, then insert the vector (which contain the previous word)
        if (word != previousWord && previousWord != "")
        {
            // std::cout << "[DEBUG] end of vec\n";
            insert(pRoot, previousWord, definitionVec);
            if (definitionVec.size() >= 4)
            {
                ++count4Def;
                wordFourDef.push_back(previousWord);
            }
            for (int i = 0; i < static_cast<int>(definitionVec.size()); ++i)
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
        insert(pRoot, previousWord, definitionVec);
        if (definitionVec.size() >= 4)
        {
            ++count4Def;
            wordFourDef.push_back(previousWord);
        }
    }
    std::cout << "count word4Def: " << count4Def << std::endl;
    std::cout << "File imported successfully!" << std::endl;
    return true;
}

bool readDatasetCSVThread(const std::string& filename, TrieNode*& pRoot, std::vector<std::string>& wordFourDef, std::atomic<bool>& finished)
{
    bool readSuccess = readDatasetCSV(filename, pRoot, wordFourDef);
    finished.store(true);

    return readSuccess;
}

bool readDatasetTXT(const std::string& filename, TrieNode*& pRoot, std::vector<std::string>& word4Def)
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
        insert(pRoot, word, pos, def, word4Def);
    }
    std::cout << "File imported successfully!" << std::endl;
    fin.close();
    return true;
}

bool readDatasetTXTThread(const std::string& filename, TrieNode*& pRoot, std::vector<std::string>& word4Def, std::atomic<bool>& finished)
{
    bool readSuccess = readDatasetTXT(filename, pRoot, word4Def);
    finished.store(true);

    return readSuccess;
}