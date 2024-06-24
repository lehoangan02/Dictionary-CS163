#include "trie.h"
#include "readDatasetCSV.hpp"
#include "removeQuotationMarkDuplicate.hpp"

bool readDatasetCSV(std::string filename, trieNode*& pRoot)
{
    std::ifstream inputStream;
    inputStream.open(filename);
    std::string line = "";
    getline(inputStream, line);
    std::vector<std::pair<std::string, std::string>> definitionVec;
    std::string word = ""; std::string previousWord = "";
    std::string POS;
    std::string description;
    while(getline(inputStream, line))
    {
        int count;
        std::stringstream tempStream(line);
        std::string tempString = "";
        
        // read the keyword
        getline(tempStream, word, ',');
        Change2Lowercase(word);

        // read the count (not used in our dictionary)
        getline(tempStream, tempString, ',');
        count  = stoi(tempString);

        // read the position of speech
        getline(tempStream, POS, ',');
        POS = POS.substr(3, POS.length() - 6);

        // read the description
        getline(tempStream, description, ',');
        description = description.substr(3, description.length() - 6);
        removeQuotationMarkDuplicate(description);

        // if word is the same, insert the word into vector
        // if word is new, then insert the vector (which contain the previous word)
        if (word != previousWord)
        {
            insert(pRoot, previousWord, definitionVec);
            definitionVec.clear();
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
        for (int i = 0; i < definitionVec.size(); ++i)
        {
            std::cout << word << " ";
            std::cout << definitionVec[i].first << " ";
            std::cout << definitionVec[i].second << std::endl;
        }
        insert(pRoot, previousWord, definitionVec);
    }
    return true;
}