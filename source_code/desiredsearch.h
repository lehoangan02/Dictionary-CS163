#pragma once
#include "button.hpp"
#include "trie.h"
#include <vector>
#include <string>

class desiredsearch
{
	std::vector<std::string> categories;
	std::vector<Button> options;
	desiredsearch();
	void updateoptions(std::string word);
	void draw();
};