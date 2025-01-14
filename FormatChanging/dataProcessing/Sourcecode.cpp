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
	std::vector<std::pair<std::string, std::string>> definitions;
	//std::string definitions; //def including part of speech
	//std::pair<std::string, std::string> definitions;
	//std::vector<std::string> definitions;
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

struct emojinode {
	std::string word;
	std::string pos;
	std::string def;
	emojinode* next;
	emojinode() {
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
//void insert(trieNode*& pRoot, std::string word, std::vector<std::string> def);
void readfile(trieNode*& pRoot, std::string readfilename, std::ifstream& fin);
void readfile2(VEwordNode*& root, std::string readfilename, std::ifstream& fin);
void write2file(trieNode*pRoot, const std::string writefilename, std::ofstream& fout, std::string& prefix);
void readfile3(trieNode*& root, std::string readfilename, std::ifstream& fin);
void readfile5(trieNode*& pRoot, std::string readfilename, std::ifstream& fin);
void deleteWholeTrie(trieNode*& pRoot); 
void write(slangnode* root, std::ofstream& fout);
void deallocate(slangnode*& root);
//void insert2(trieNode*& pRoot, std::string word, std::string def);
void insert(trieNode*& pRoot, std::string word, std::pair<std::string, std::string> means);
void readfile4(trieNode*& pRoot, std::string readfilename, std::ifstream& fin);
void Change2Lowercase(std::string& word);


void readfileemoji(emojinode*& root, std::ifstream& fin, std::string readfilename);
void write(emojinode* root, std::ofstream& fout, std::string writefilename);
void deleteemojinode(emojinode* root);
void readfile6(trieNode*& root, std::string readfilename, std::ifstream& fin);
void insert3(trieNode*& pRoot, std::string word, std::string pos, std::string def);

int main()
{
	std::string readfilename, writefilename;
	std::ifstream fin;
	std::ofstream fout;

	/*trieNode* pRoot = nullptr;
	readfile6(pRoot, readfilename, fin);
	std::cout << "Input writefilename: ";
	getline(std::cin, writefilename);
	std::string prefix = "";
	fout.open(writefilename + ".txt");
	write2file(pRoot, writefilename, fout, prefix);
	fout.close();
	deleteWholeTrie(pRoot);*/


	emojinode* root = nullptr;
	readfileemoji(root, fin, readfilename);
	write(root, fout, writefilename);
	deleteemojinode(root);

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
	while (start <= end && (str[start] == ';' || str[start] == '"'))
	{
		start++;
	}

	//Find the first non-space character from the the right hand side.
	while (end >= start && (str[end] == ';' || str[end] == '"'))
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
		std::vector<std::string> means;
		getline(split, word , '|');
		getline(split, def);
		int start = 0;
		int pos = def.find("||", start);
		while (pos != std::string::npos)
		{
			std::string newdef = def.substr(start, pos - start);
			means.push_back(newdef);
			start = pos + 2;
			pos = def.find("||", start);
		}
		std::string newdef = def.substr(start);
		means.push_back(newdef);
		//insert(pRoot, word, means);
	}
	std::cout << "Reading file successfully!" << std::endl;
	fin.close();
}

void readfile5(trieNode*& pRoot, std::string readfilename, std::ifstream& fin)
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
		std::string word, pos, def;

		getline(split, word, '|');
		int length = word.length();
		for (int i = 0; i < length; ++i) {
			if ((i == 0 || (i - 1 >= 0 && word[i - 1] == ' ')) && std::islower(word[i])) {
				word[i] -= 32;
			}
		}

		getline(split, pos, '|');

		getline(split, def);
		if (def.length() > 400) continue;
		std::pair<std::string, std::string> means{ pos, def };
		insert(pRoot, word, means);
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

void readfile3(trieNode*& root, std::string readfilename, std::ifstream& fin)
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
	std::string word = "", pos = "", def = "";
	while (getline(fin, line))
	{
		if (line[0] == '@') {
			if (!word.empty()) {
				if (!def.empty()) {
					def.pop_back();
					def.pop_back();
				}
				//insert(root, word, pos, def);
				pos.clear();
				def.clear();
			}
			word = line.substr(1);
			int posIndex = word.find('/');
			if (posIndex != std::string::npos) {
				word = word.substr(0, posIndex);
			}
		}
		else if (line[0] == '*')
		{
			pos = line.substr(line.find_first_not_of("* "));
		}
		else {
			if (line[0] == '-') {
				std::string newdef = line.substr(line.find_first_not_of("- "));
				def += newdef + "; ";
			}
			else if (line[0] == '=') {
				std::string example = line.substr(1);
				def += "( " + example + " )" + "; ";
			}
		}
	}
	if (!word.empty()) {
		//insert(root, word, pos, def);
	}
	std::cout << "Reading file successfully!" << std::endl;
	fin.close();
}

void readfile6(trieNode*& root, std::string readfilename, std::ifstream& fin)
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
	while (getline(fin, line)) {
		std::stringstream split(line);
		std::string word, pos, def;

		getline(split, word, '|');
		getline(split, pos, '|');
		getline(split, def);
		if (def[0] != ' ' && def[0] == 'n' && def[1] == 'o') {
			size_t posit = def.find('|', 0);
			std::string classifier = def.substr(0, posit);
			pos += " (" + classifier + ")";
			def.erase(0, posit + 1);
		}
		if (def[0] == 'c' && def[1] == 'o') {
			size_t posit = def.find('|', 0);
			if (posit != std::string::npos)
				def.erase(0, posit + 1);
			else def = "";
		}
		insert3(root, word, pos, def);
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

void insert(trieNode*& pRoot, std::string word, std::pair<std::string, std::string> means)
{
	if (word.empty()) return;

	if (!pRoot)
	{
		pRoot = new trieNode();
	}
	trieNode* cur = pRoot;
	for (auto c : word)
	{
		if (!cur->childNode[int(c) - 32])
		{
			trieNode* newNode = new trieNode();
			cur->childNode[int(c) - 32] = newNode;
		}
		cur = cur->childNode[int(c) - 32];
	}
	cur->wordExisted = true;

	for (auto& x : cur->definitions)
	{
		if (means.first == x.first) {
			x.second += "; " + means.second;
		}
	}

	cur->definitions.push_back(means);
}

void insert3(trieNode*& pRoot, std::string word, std::string pos, std::string def)
{
	if (word.empty()) return;

	if (!pRoot)
	{
		pRoot = new trieNode();
	}
	trieNode* cur = pRoot;
	for (auto c : word)
	{
		if (!cur->childNode[int(c) - 32])
		{
			trieNode* newNode = new trieNode();
			cur->childNode[int(c) - 32] = newNode;
		}
		cur = cur->childNode[int(c) - 32];
	}
	cur->wordExisted = true;

	cur->definitions.push_back({pos, def});
}

void Change2Lowercase(std::string& word)
{
	// Check if the string is empty before transforming
	if (!word.empty())
	{
		std::transform(word.begin(), word.end(), word.begin(),
			[](unsigned char c) { return std::tolower(c); });
	}
}

//void insert2(trieNode*& pRoot, std::string word, std:: string pos, std::string def)
//{
//	if (word.empty()) return;
//	//Change2Lowercase(word);
//	//Change2Lowercase(def);
//	if (!pRoot)
//	{
//		pRoot = new trieNode();
//	}
//	trieNode* cur = pRoot;
//	for (auto c : word)
//	{
//		if (c - 32 < 0 || c - 32 >= 96) {
//			continue; // Skip characters outside the range
//		}
//		if (!cur->childNode[c - 32])
//		{
//			trieNode* newNode = new trieNode();
//			cur->childNode[c - 32] = newNode;
//		}
//		cur = cur->childNode[c - 32];
//	}
//	cur->wordExisted = true;
//
//	cur->definitions = def;
//}

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
		for (auto& x : pRoot->definitions)
		{
			fout << prefix << "|" << x.first << "|" << x.second << std::endl;
		}
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

void readfileemoji(emojinode*& root, std::ifstream& fin, std::string readfilename)
{
	std::cout << "- Please input filename: ";
	getline(std::cin, readfilename);
	std::cout << readfilename << std::endl;
	fin.open(readfilename + ".csv");
	if (!fin.is_open())
	{
		std::cerr << "Error: Unable to open file!" << std::endl;
		return;
	}
	std::string line = "";
	emojinode* cur = root;
	while (getline(fin, line))
	{
		if (!root) {
			root = new emojinode();
			cur = root;
		}
		else {
			cur->next = new emojinode();
			cur = cur->next;
		}
		std::stringstream split(line);
		
		getline(split, cur->pos, ',');
		getline(split, cur->word, ',');
		getline(split, cur->def);
	}
	fin.close();
}

void write(emojinode* root, std::ofstream& fout, std::string writefilename)
{
	std::cout << "- Please input write filename: ";
	getline(std::cin, writefilename);
	fout.open(writefilename + ".txt");
	if (!fout.is_open())
	{
		std::cerr << "Error: Unable to open file!" << std::endl;
		return;
	}
	emojinode* cur = root;
	while (cur) {
		fout << cur->word << "|";
		fout << "emoji number: " << cur->pos << "|";
		fout << cur->def << std::endl;
		cur = cur->next;
	}
	fout.close();
}

void deleteemojinode(emojinode* root)
{
	emojinode* cur = nullptr;
	while (root)
	{
		cur = root;
		root = root->next;
		delete cur;
	}
}