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

    std::getline(file, line);
    int width = line.length();

    int height = 1;
    while (std::getline(file, line))
    {
        height++;
    }

    file.clear();
    file.seekg(0);

    const char EMPTY = '.';
    const char GEAR = '*';
    const int SYMBOL = -1;

    std::vector<std::vector<int>> vec(width, std::vector<int>(height, 0));

    // Init vector
    for (int m = 0; m < height; m++)
    {
        std::getline(file, line);
        
        for (int n = 0; n < width; n++)
        {
            if (line[n] == EMPTY)
                continue;

            if (isdigit(line[n]))
            {
                int numLen = 1;

                // Get numbers length
                while (n+numLen < width)
                {
                    if (!isdigit(line[n+numLen]))
                        break;
                    
                    numLen++;
                }

                // Extract number as int
                std::string numStr = line.substr(n, numLen);
                int num = std::stoi(numStr);

                // Insert number into vector at each digit position
                for (int i = 0; i < numLen; i++)
                    vec[m][n+i] = num;
                
                n += numLen-1;
            }

            else if (line[n] == GEAR)
                vec[m][n] = SYMBOL;
        }
    }
    
    int output = 0;

    // Find numbers adjacent to symbols
    for (int m = 0; m < width; m++)
    {
        for (int n = 0; n < height; n++)
        {
            if (vec[m][n] == SYMBOL)
            {
                std::vector<int> partNums;

                int north = m-1;
                int south = m+1;
                int west = n-1;
                int east = n+1;

                bool northOk = north >= 0;
                bool southOk = south < height;
                bool westOk = west >= 0;
                bool eastOk = east < width;

                // North
                if (northOk)
                {
                    if (vec[north][n] > 0)
                        partNums.push_back(vec[north][n]);
                        
                    else 
                    {
                        // North west
                        if (westOk && vec[north][west] > 0)
                            partNums.push_back(vec[north][west]);
                            
                        // North east
                        if (eastOk && vec[north][east] > 0)
                            partNums.push_back(vec[north][east]);       
                    }
                }

                // South
                if (southOk)
                {
                    if (vec[south][n] > 0)
                        partNums.push_back(vec[south][n]);
                        
                    else 
                    {
                        // South west
                        if (westOk && vec[south][west] > 0)
                            partNums.push_back(vec[south][west]);
                            
                        // South east
                        if (eastOk && vec[south][east] > 0)
                            partNums.push_back(vec[south][east]);
                    }
                }

                // West
                if (westOk && vec[m][west] > 0)
                    partNums.push_back(vec[m][west]);
                    
                // East
                if (eastOk && vec[m][east] > 0)
                    partNums.push_back(vec[m][east]);

                // If gear, add gear ratio to output
                if (partNums.size() == 2)
                    output += partNums[0] * partNums[1];
            }
        }
    }

    std::cout << output << std::endl;
}