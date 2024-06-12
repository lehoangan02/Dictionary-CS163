#include "trie.h"
#include "readDatasetCSV.hpp"
#include "removeQuotationMarkDuplicate.hpp"
bool readDatasetCSV(std::string filename, trieNode*& pRoot)
{
    std::ifstream inputStream;
    inputStream.open(filename);
    std::string line = "";
    getline(inputStream, line);
    while(getline(inputStream, line))
    {
        std::string word;
        int count;
        std::string POS;
        std::string description;
        std::stringstream tempStream(line);
        std::string tempString = "";
        
        // read the keyword
        getline(tempStream, word, ',');

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

        // insert the word into trie
        // assuming the insert function will be 
        // insert(trieNode*& pRoot, std::string keyword, std::pair<std::string, std::string>> definition);
        // the function call will be
        insert(pRoot, word, std::pair<std::string, std::string>{POS, description});
        line = "";
    }
    return true;
}