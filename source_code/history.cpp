#include "history.hpp"
void readHistory(std::vector<std::string>& history)
{
    std::string temp;
    std::ifstream fin;
    fin.open("settings/history.txt");
    while (getline(fin, temp))
    {
        history.push_back(temp);
        printf("[DEBUG] %s\n", temp.c_str());
    }
    fin.close();
}
void writeHistory(std::string newHistory)
{
    std::ofstream fout;
    fout.open("settings/history.txt", std::ios::app);
    printf("[DEBUG] writing %s\n", newHistory.c_str());
    fout << std::endl << newHistory;
    fout.close();
}