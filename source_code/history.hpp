#pragma once
#include <fstream>
#include <vector>
#include <string>
void readHistory(std::vector<std::string>& history, const int& curDataset);
void writeHistory(std::string newHistory, const int& curDataset);