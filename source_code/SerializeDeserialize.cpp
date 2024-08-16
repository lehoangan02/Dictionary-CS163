#include "SerializeDeserialize.h"

// serialization of the existing trie (compatibility mode)
void serializeWrapper(TrieNode* pRoot)
{
	std::ofstream fout; fout.open("serialized.txt");
	serialize(pRoot, fout, "");
}
void serialize(TrieNode* pRoot, std::ofstream& fout, std::string word)
{
	if (!pRoot)
	{ 
		fout << "-1\n";
		std::cout << "[DEBUG] -1\n";
		return;
	}
	fout << pRoot -> wordExisted << std::endl;
	fout << "[DEBUG] " << word << std::endl;
	fout << pRoot -> definitions.size() << std::endl;
	for (int i = 0; i < (int)(pRoot -> definitions.size()); ++i)
	{
		fout << pRoot -> definitions[i].first << std::endl;
		fout << pRoot -> definitions[i].second << std::endl;
	}
	for (int i = 0; i < 96; ++i)
	{
		int asciiVal = i + 32;
		std::string newWord = word + (char)asciiVal;
		std::cout << "[DEBUG] new word is " << newWord << std::endl;
		serialize(pRoot -> childNode[i], fout, newWord);
	}
	return;
}

// deserialization of the saved trie (compatibility mode)
bool deserializeWrapper(TrieNode*& pRoot)
{
	deleteWholeTrie(pRoot);
	std::ifstream fin; fin.open("serialized.txt");
    if (fin.is_open() == false)
    {
        std::cout << "[DEBUG] no file found to deserialize!\n";
        return false;
    }
	deserialize(pRoot, fin, "");
    return true;
}
void deserialize(TrieNode*& pRoot, std::ifstream& fin, std::string word)
{
	int temp = 0;
	fin >> temp;
	fin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	if (temp == -1)
	{
		std::cout << "[DEBUG] empty node\n";
		pRoot = nullptr;
		return;
	}
	pRoot = new TrieNode;
	pRoot -> wordExisted = temp;
	std::string tempString = "";
	std::getline(fin, tempString);
	std::cout << "[DEBUG] word is: " << tempString << std::endl;
	int size = 0;
	fin >> size;
	fin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	std::vector<std::pair<std::string, std::string>> definitionVec;
	for (int i = 0; i < size; ++i)
	{
		std::string POS = "";
		std::string description = "";
		std::getline(fin, POS);
		std::getline(fin, description);
		definitionVec.push_back(std::pair<std::string, std::string>{POS, description});
		std::cout << "[DEBUG] POS: " << POS << " - definition: " << description << std::endl;
	}
	pRoot -> definitions = definitionVec;
	for (int i = 0; i < 96; ++i)
	{
		std::string newWord = word + (char)(i + 32);
		std::cout << "[DEBUG] probing " << newWord << std::endl;
		deserialize(pRoot -> childNode[i], fin, newWord);
	}
}

// serialization of the existing trie (compatibility mode)
void serializeBinaryWrapper(TrieNode* pRoot, const int& fileNum)
{
	std::string fileName = "serialized" + std::to_string(fileNum) + ".bin";
	std::fstream f; f.open(fileName, std::ios::binary | std::ios::out | std::ios::trunc);
	std::string temp = "";
	serializeBinary(pRoot, f, temp);
}
void serializeBinary(TrieNode* pRoot, std::fstream& f, std::string& word)
{
	int temp = 0;
	if (!pRoot)
	{
		temp = -1;
		f.write((char*)&temp, sizeof(int));
		return;
	}
	temp = 0;
	f.write((char*)&temp, sizeof(int));
	bool wordExisted = pRoot -> wordExisted;
	f.write((char*)&wordExisted, sizeof(bool));
	int countChildren = pRoot -> countchildren;
	f.write((char*)&countChildren, sizeof(int));
	int size = (int)(pRoot -> definitions.size());
	f.write((char*)&size, sizeof(int));
	for (int i = 0; i < size; ++i)
	{
		int stringSize = pRoot -> definitions[i].first.size();
		f.write((char*)&stringSize, sizeof(int));
		f.write(pRoot -> definitions[i].first.c_str(), pRoot -> definitions[i].first.size());
		// std::cout << pRoot -> definitions[i].first.c_str() << std::endl;
		stringSize = pRoot -> definitions[i].second.size();
		f.write((char*)&stringSize, sizeof(int));
		f.write(pRoot -> definitions[i].second.c_str(), pRoot -> definitions[i].second.size());
		// std::cout << pRoot -> definitions[i].second.c_str() << std::endl;
	}
	for (int i = 0; i < 96; ++i)
	{
		word.push_back((char)(i + 32));
		// std::cout << "[DEBUG] new word is " << newWord << std::endl;
		serializeBinary(pRoot -> childNode[i], f, word);
		word.pop_back();
	}
	return;
}

void serializeBinaryThread(TrieNode* pRoot, const int& fileNum, std::atomic<bool>& finished)
{
	serializeBinaryWrapper(pRoot, fileNum);
	finished.store(true);
}

// deserialization of the saved trie (compatibility mode)
bool deserializeBinaryWrapper(TrieNode*& pRoot, std::vector<std::string>& word4Def, const int& fileNum)
{
	std::cout << "[DEBUG] deserializing file " << fileNum << std::endl;
	std::fstream f; 
	std::string fileName = "serialized" + std::to_string(fileNum) + ".bin";
	f.open(fileName, std::ios::binary | std::ios::in);
	if (!f.is_open())
	{
		std::cout << "[DEBUG] no file found to deserialize!\n";
		return false;
	}
	std::string temp = "";
	deserializeBinary(pRoot, f, temp, word4Def);
	return true;
}
void deserializeBinary(TrieNode*& pRoot, std::fstream& f, std::string& word, std::vector<std::string>& word4Def)
{
	int temp = 0;
	f.read((char*)&temp, sizeof(int));
	if (temp == -1)
	{
		// std::cout << "[DEBUG] empty node\n";
		pRoot = nullptr;
		return;
	}
	pRoot = new TrieNode;
	bool wordExisted = false;
	f.read((char*)&wordExisted, sizeof(bool));
	pRoot -> wordExisted = wordExisted;
	int countChildren = 0;
	f.read((char*)&countChildren, sizeof(int));
	pRoot -> countchildren = countChildren;
	int sizeDef = 0;
	f.read((char*)&sizeDef, sizeof(int));
	int sizeString = 0;
	std::vector<std::pair<std::string, std::string>> definitionVec;
	for (int i = 0; i < sizeDef; ++i)
	{
		std::string POS = "";
		std::string description = "";
		f.read((char*)&sizeString, sizeof(int)); // read the size of POS
		char* buffer = new char[sizeString]; // allocate a char array buffer
		f.read(buffer, sizeString);
		POS.assign(buffer, sizeString);
		delete [] buffer;
		f.read((char*)&sizeString, sizeof(int)); // read the size of description
		buffer = new char[sizeString]; // allocate a char array buffer
		f.read(buffer, sizeString);
		description.assign(buffer, sizeString);
		delete [] buffer;
		definitionVec.push_back(std::pair<std::string, std::string>{POS, description});
		// std::cout << "[DEBUG] POS: " << POS << " - definition: " << description << std::endl;
	}
	if (static_cast<int> (definitionVec.size()) >= 4)
	{
		word4Def.push_back(word);
	}
	pRoot -> definitions = definitionVec;
	for (int i = 0; i < 96; ++i)
	{
		word.push_back((char)(i + 32));
		// std::cout << "[DEBUG] probing " << newWord << std::endl;
		deserializeBinary(pRoot -> childNode[i], f, word, word4Def);
		word.pop_back();
	}
}

bool deserializeBinaryThread(TrieNode*& pRoot, std::vector<std::string>& word4Def, const int& fileNum, std::atomic<bool>& finished)
{
	bool success = deserializeBinaryWrapper(pRoot, word4Def, fileNum);
	finished.store(true);

	return success;
}