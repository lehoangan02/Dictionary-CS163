#include<iostream>
#include<fstream>
#include<sstream>
#include<string>
#include<vector>
#include<cctype>
#include<algorithm>

const int ascii = 96;

struct trieNode
{
	bool wordExisted = false;
	trieNode* childNode[96];
	//std::pair<std::string, std::vector<std::string>> definitions;
	std::string def; //def including part of speech
	trieNode()
	{
		for (int i = 0; i < ascii; ++i) this->childNode[i] = nullptr;
	}
};

struct VEwordNode
{
	std::string mainword;
	std::string remain;
	VEwordNode* next;
	VEwordNode() {
		this->mainword = "";
		this->remain = "";
		this->next = nullptr;
	}
};

struct slangnode
{
	std::string word;
	int count;
	std::string pos;
	std::string def;
	slangnode* next;
	slangnode()
	{
		this->word = "";
		this->count = 0;
		this->pos = "";
		this->def = "";
		this->next = nullptr;
	}
};

std::string trim(const std::string& str);
//void insert(trieNode*& pRoot, std::string word, std::pair<std::string, std::vector<std::string>> definit);
void readfile(trieNode*& pRoot, std::string readfilename, std::ifstream& fin);
void readfile2(VEwordNode*& root, std::string readfilename, std::ifstream& fin);
void write2file(trieNode*pRoot, const std::string writefilename, std::ofstream& fout, std::string& prefix);
void readfile3(slangnode*& root, std::string readfilename, std::ifstream& fin);
void deleteWholeTrie(trieNode*& pRoot); 
void write(slangnode* root, std::ofstream& fout);
void deallocate(slangnode*& root);
void insert2(trieNode*& pRoot, std::string word, std::string def);
void readfile4(trieNode*& pRoot, std::string readfilename, std::ifstream& fin);
void Change2Lowercase(std::string& word);

int main()
{
	std::string readfilename, writefilename;
	std::ifstream fin;
	std::ofstream fout;
	trieNode* pRoot = nullptr;
	readfile4(pRoot, readfilename, fin);
	//if (!pRoot) std::cout << "NULL" << std::endl;
	std::cout << "- Please input filename: ";
	getline(std::cin, writefilename);
	fout.open(writefilename + ".txt");
	std::string prefix = "";
	write2file(pRoot, writefilename, fout, prefix);
	fout.close();
	std::cout << "Writing file successfully!" << std::endl;
	deleteWholeTrie(pRoot);

	/*slangnode* root = nullptr;
	readfile3(root, readfilename, fin);
	fout.open("slang.txt");
	write(root, fout);
	deallocate(root);*/

	return 0;
}

std::string trim(const std::string& str)
{
	if (str.empty())
	{
		return str;
	}

	size_t start = 0;
	size_t end = str.length() - 1;

	//Find the first non space character from the left hand side.
	while (start <= end && std::isspace(static_cast<unsigned char>(str[start])))
	{
		start++;
	}

	//Find the first non-space character from the the right hand side.
	while (end >= start && std::isspace(static_cast<unsigned char>(str[end])))
	{
		end--;
	}

	return str.substr(start, end - start + 1);
}

void readfile(trieNode*& pRoot, std::string readfilename, std::ifstream& fin)
{
	std::cout << "- Please input filename: ";
	getline(std::cin, readfilename);
	fin.open(readfilename + ".txt");
	if (!fin.is_open())
	{
		std::cerr << "Error: Unable to open file!" << std::endl;
		return;
	}
	std::string line = "";
	while (getline(fin, line))
	{
		std::stringstream split(line);
		std::string word, definition;
		std::pair<std::string, std::vector<std::string>> def;
		def.first = "sla.";

		getline(split, word, '`');
		getline(split, definition);
		int pos = definition.find('|', 0);
		if (pos == std::string::npos) def.second.push_back(definition);
		else {
			while (pos != std::string::npos)
			{
				def.second.push_back(definition.substr(0, pos));
				definition.erase(0, pos + 2);
				pos = definition.find('|', 0);
			}
			def.second.push_back(definition);
		}
		//insert(pRoot, word, def);
	}
	std::cout << "Reading file successfully!" << std::endl;
	fin.close();
}

void readfile2(VEwordNode*& root, std::string readfilename, std::ifstream& fin)
{
	std::cout << "- Please input filename: ";
	getline(std::cin, readfilename);
	fin.open(readfilename + ".txt");
	if (!fin.is_open())
	{
		std::cerr << "Error: Unable to open file!" << std::endl;
		return;
	}
	std::string line = "";
	VEwordNode* cur = root;
	while (getline(fin, line))
	{
		if (!root)
		{
			root = new VEwordNode();
			cur = root;
		}
		else {
			cur->next = new VEwordNode();
			cur = cur->next;
		}
		size_t pos = line.find('|', 0);
		cur->mainword = trim(line.substr(0, pos));
		cur->remain = trim(line.substr(pos + 1));
	}
	std::cout << "Reading file successfully!" << std::endl;
	fin.close();
}

void readfile4(trieNode*& pRoot, std::string readfilename, std::ifstream& fin)
{
	std::cout << "- Please input filename: ";
	getline(std::cin, readfilename);
	fin.open(readfilename + ".txt");
	if (!fin.is_open())
	{
		std::cerr << "Error: Unable to open file!" << std::endl;
		return;
	}
	std::string line = "";
	while (getline(fin, line))
	{
		std::stringstream split(line);
		std::string word, def;
		getline(split, word , '|');
		getline(split, def);
		insert2(pRoot, word, def);
	}
	std::cout << "Reading file successfully!" << std::endl;
	fin.close();
}

void write(slangnode* root, std::ofstream& fout)
{
	slangnode* cur = root;
	while (cur)
	{
		//std::cout << cur->mainword;
		fout << cur->word << "|";
		fout << cur->pos << "|";
		int end = cur->def.length() - 1;
		while (end >= 0 && cur->def[end] == ';') end--;
		fout << cur->def.substr(0, end + 1) << std::endl;
		cur = cur->next;
	}
	std::cout << "Printing file successfully!" << std::endl;
	fout.close();
}

void readfile3(slangnode*& root, std::string readfilename, std::ifstream& fin)
{
	std::cout << "- Please input filename: ";
	getline(std::cin, readfilename);
	fin.open(readfilename + ".csv");
	if (!fin.is_open())
	{
		std::cerr << "Error: Unable to open file!" << std::endl;
		return;
	}
	std::string line = "";
	slangnode* cur = root;
	while (getline(fin, line))
	{
		if (!root)
		{
			root = new slangnode();
			cur = root;
		}
		else {
			cur->next = new slangnode();
			cur = cur->next;
		}
		std::istringstream ss(line);
		std::string add = "";
		getline(ss, cur->word, ',');
		getline(ss, add, ',');
		cur->count = stoi(add);
		getline(ss, cur->pos, ',');
		getline(ss, cur->def);
	}
	std::cout << "Reading file successfully!" << std::endl;
	fin.close();
}

void deallocate(slangnode*& root)
{
	slangnode* temp = nullptr;
	while (root)
	{
		temp = root;
		root = root->next;
		delete temp;
	}
}

//void insert(trieNode*& pRoot, std::string word, std::pair<std::string, std::vector<std::string>> definit)
//{
//	if (word.empty()) return;
//
//	if (!pRoot)
//	{
//		pRoot = new trieNode();
//	}
//	trieNode* cur = pRoot;
//	for (auto c : word)
//	{
//		if (!cur->childNode[int(c) - 32])
//		{
//			trieNode* newNode = new trieNode();
//			cur->childNode[int(c) - 32] = newNode;
//		}
//		cur = cur->childNode[int(c) - 32];
//	}
//	cur->wordExisted = true;
//
//	cur->definitions = definit;
//}

void Change2Lowercase(std::string& word)
{
	// Check if the string is empty before transforming
	if (!word.empty())
	{
		std::transform(word.begin(), word.end(), word.begin(),
			[](unsigned char c) { return std::tolower(c); });
	}
}

void insert2(trieNode*& pRoot, std::string word, std::string def)
{
	if (word.empty()) return;
	//Change2Lowercase(word);
	//Change2Lowercase(def);
	if (!pRoot)
	{
		pRoot = new trieNode();
	}
	trieNode* cur = pRoot;
	for (auto c : word)
	{
		if (c - 32 < 0 || c - 32 >= 96) {
			continue; // Skip characters outside the range
		}
		if (!cur->childNode[c - 32])
		{
			trieNode* newNode = new trieNode();
			cur->childNode[c - 32] = newNode;
		}
		cur = cur->childNode[c - 32];
	}
	cur->wordExisted = true;

	cur->def = def;
}

void write2file(trieNode* pRoot, const std::string writefilename, std::ofstream& fout, std::string& prefix)
{
	if (!fout.is_open())
	{
		std::cerr << "Error: Unable to open file!" << std::endl;
		return;
	}
	if (!pRoot) return;
	if (pRoot->wordExisted)
	{
		fout << prefix << "|";
		fout << pRoot->def << std::endl;
	}
	for (int i = 0; i < ascii; ++i)
	{
		prefix.push_back(static_cast<char>(i + 32));
		write2file(pRoot->childNode[i], writefilename, fout, prefix);
		prefix.pop_back(); 
	}
}

//delete the whole tree
void deleteWholeTrie(trieNode*& pRoot)
{
	if (!pRoot)
		return;
	for (int i = 0; i < ascii; ++i)
	{
		deleteWholeTrie(pRoot->childNode[i]);
	} //update
	delete pRoot;
	pRoot = nullptr;
}
