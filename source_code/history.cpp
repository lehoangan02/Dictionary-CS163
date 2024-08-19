#include "history.hpp"

/// @brief read previous history saves
/// @param history 
void readHistory(std::vector<std::string>& history, const int& curDataset)
{
    std::string temp;
    std::ifstream fin;
    std::string mode = "";
    switch (curDataset) {
    case 0: {
        mode = "EE"; break;
    }
    case 1: {
        mode = "VE"; break;
    }
    case 2: {
        mode = "EV"; break;
    }
    case 3: {
        mode = "Emoji"; break;
    }
    case 4: {
        mode = "Slang"; break;
    }
    case 5: {
        mode = "Other"; break;
    }
    default:
        break;
    }
    fin.open("settings/history/history" + mode + ".txt");
    while (getline(fin, temp))
    {
        history.push_back(temp);
        // printf("[DEBUG] reading history %s\n", temp.c_str());
    }
    fin.close();
}

/// @brief write new history to saves
/// @param newHistory 
void writeHistory(std::string newHistory, const int& curDataset)
{
    bool emptyFile = false;
    std::ifstream fin;
    std::string mode = "";
    switch (curDataset) {
    case 0: {
        mode = "EE"; break;
    }
    case 1: {
        mode = "VE"; break;
    }
    case 2: {
        mode = "EV"; break;
    }
    case 3: {
        mode = "Emoji"; break;
    }
    case 4: {
        mode = "Slang"; break;
    }
    case 5: {
        mode = "Other"; break;
    }
    default:
        break;
    }
    fin.open("settings/history/history" + mode + ".txt");
    std::string firstLine = "";
    getline(fin, firstLine);
    if (firstLine.compare("") == 0)
        emptyFile = true;
    std::ofstream fout;
    fout.open("settings/history/history" + mode + ".txt", std::ios::app);
    // printf("[DEBUG] writing new history %s\n", newHistory.c_str());
    if (!emptyFile) fout << std::endl << newHistory;
    else    fout << newHistory;
    fout.close();
}