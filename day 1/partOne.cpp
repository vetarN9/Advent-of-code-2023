#include <iostream>
#include <stdint.h>
#include <fstream>
#include <string>
#include <cctype>

int main(int argc, char* argv[])
{
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
        }
        
        // Find last digit
        for (int i = length - 1; i >= 0; i--)
        {
            if (isdigit(line[i]))
            {
                lastNum = line[i] - '0';
                break;
            }
        }

        output += (firstNum * 10) + lastNum;
    }

    std::cout << output << std::endl;
}