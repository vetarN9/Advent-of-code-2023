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

    const int NUM_BLUES  = 14;
    const int NUM_GREENS = 13;
    const int NUM_REDS   = 12;

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

        bool ok = true;

        // Loop over each subset of cubes
        for (const std::string& str : substrings)
        {
            std::istringstream iss(str);
            std::map<std::string, int> colorCounts;

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

                colorCounts[color] = count;
            }

            for (const auto& cc : colorCounts)
            {
                if (cc.first == "blue" && cc.second > NUM_BLUES)
                {
                    ok = false;
                    break;
                }
                
                if (cc.first == "red" && cc.second > NUM_REDS)
                {
                    ok = false;
                    break;
                }
                
                if (cc.first == "green" && cc.second > NUM_GREENS)
                {
                    ok = false;
                    break;
                }
            }

            if (!ok)
                break;
        }

        if (ok)
            output += gameID;
    }

    std::cout << output << std::endl;
}