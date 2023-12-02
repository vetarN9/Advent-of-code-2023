#include <iostream>
#include <stdint.h>
#include <fstream>
#include <string>
#include <cctype>
#include <sstream>
#include <vector>
#include <map>

int main(int argc, char* argv[])
{
    std::ifstream file("input.txt");

    std::string line;
    int gameID = 0;
    int output = 0;

    while (std::getline(file, line))
    {
        gameID++;

        // Start string at first cube amount
        auto start = line.find(':', 5) + 2;
        line = line.substr(start);

        std::stringstream ss(line);
        std::string substring;
        std::vector<std::string> substrings;

        while (std::getline(ss, substring, ';'))
        {
            substrings.push_back(substring);
        }

        std::map<std::string, int> colorCounts = 
        {
            {"blue",  0},
            {"red",   0},
            {"green", 0}
        };

        // Loop over each subset of cubes
        for (const std::string& str : substrings)
        {
            std::istringstream iss(str);
            
            while (true)
            {
                int count;
                std::string color;
                iss >> count >> color; 

                if (!iss)
                    break;

                // Remove comma after color
                if (color.back() == ',')
                    color.pop_back();

                if (colorCounts[color] < count)
                    colorCounts[color] = count;
            }

        }

            output += colorCounts["red"] * colorCounts["blue"] * colorCounts["green"];
    }

    std::cout << output << std::endl;
}