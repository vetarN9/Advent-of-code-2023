#include <iostream>
#include <stdint.h>
#include <fstream>
#include <string>
#include <cctype>
#include <map>


int main(int argc, char* argv[])
{
    std::map<std::string, int> digitMap = 
    {
        {"one",   1},
        {"two",   2},
        {"three", 3},
        {"four",  4},
        {"five",  5},
        {"six",   6},
        {"seven", 7},
        {"eight", 8},
        {"nine",  9}
    };

    std::ifstream file("input.txt");

    std::string line;
    int length, firstNum, lastNum;
    int output = 0;

    while (std::getline(file, line))
    {
        length = line.length();

        // Find first digit
        for (int i = 0; i < length; i++)
        {
            if (isdigit(line[i]))
            {
                firstNum = line[i] - '0';
                break;
            }

            bool foundDigit = false;

            // Not a digit, check the following 4 chars if word or digit
            for (int subStrLen = 2; subStrLen <= 5; subStrLen++)
            {
                std::string substring = line.substr(i, subStrLen);

                for (const auto& pair : digitMap)
                {
                    size_t found = substring.find(pair.first);

                    if (found != std::string::npos)
                    {
                        firstNum = pair.second;
                        foundDigit = true;
                        break;
                    }
                }

                if (foundDigit)
                    break;
                
                if (isdigit(line[i+subStrLen-1]))
                {
                    firstNum = line[i+subStrLen-1] - '0';
                    break;
                }
            }

            if (foundDigit)
                break;
        }

        // Find last digit
        for (int i = length - 1; i >= 0; i--)
        {
            // Trivial digit case
            if (isdigit(line[i]))
            {
                lastNum = line[i] - '0';
                break;
            }

            bool foundDigit = false;

            // Not a digit, check the previous 4 chars if word or digit
            for (int subStrLen = 2; subStrLen <= 5; subStrLen++)
            {
                int a = i - subStrLen + 1;
                int index = (a < 0) ? 0 : a;
                std::string substring = line.substr(index, subStrLen);

                for (const auto& pair : digitMap)
                {
                    size_t found = substring.find(pair.first);

                    if (found != std::string::npos)
                    {
                        lastNum = pair.second;
                        foundDigit = true;
                        break;
                    }
                }

                if (foundDigit)
                    break;
                
                if (isdigit(line[i-subStrLen+1]))
                {
                    lastNum = line[i-subStrLen+1] - '0';
                    break;
                }
            }

            if (foundDigit)
                break;
        }

        output += (firstNum * 10) + lastNum;
    }

    std::cout << output << std::endl;
}