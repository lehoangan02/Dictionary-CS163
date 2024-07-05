#include "history.hpp"

/// @brief read previous history saves
/// @param history 
void readHistory(std::vector<std::string>& history)
{
    std::string temp;
    std::ifstream fin;
    fin.open("settings/history.txt");
    while (getline(fin, temp))
    {
        history.push_back(temp);
        // printf("[DEBUG] reading history %s\n", temp.c_str());
    }
    fin.close();
}

/// @brief write new history to saves
/// @param newHistory 
void writeHistory(std::string newHistory)
{
    bool emptyFile = false;
    std::ifstream fin;
    fin.open("settings/history.txt");
    std::string firstLine = "";
    getline(fin, firstLine);
    if (firstLine.compare("") == 0)
        emptyFile = true;
    std::ofstream fout;
    fout.open("settings/history.txt", std::ios::app);
    // printf("[DEBUG] writing new history %s\n", newHistory.c_str());
    if (!emptyFile) fout << std::endl << newHistory;
    else    fout << newHistory;
    fout.close();
}