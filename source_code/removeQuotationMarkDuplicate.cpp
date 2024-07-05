#include "removeQuotationMarkDuplicate.hpp"
void removeQuotationMarkDuplicate(std::string& inputString)
{
    int length = int(inputString.length());
    for (int i = 0; i < length - 7; ++i)
    {
        if (inputString.substr(i, 8) == "\"\"\"\"\"\"\"\"")
        {
            inputString.erase(i + 1, 7);
            length -= 7;

        }
    }
}