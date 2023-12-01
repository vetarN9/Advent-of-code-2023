#include <iostream>
#include <string>
#include <map>

int main() {
    std::map<std::string, int> digitMap = 
    {
        {"zero", 0},
        {"one", 1},
        {"two", 2},
        {"three", 3},
        {"four", 4},
        {"five", 5},
        {"six", 6},
        {"seven", 7},
        {"eight", 8},
        {"nine", 9}
    };

    std::string inputString = "There are two apples and thre oranges.";

    int foundDigit = -1; // Initialize with a default value

    // Iterate through the map to find the first spelled-out digit in the string
    for (const auto& pair : digitMap) {
        size_t found = inputString.find(pair.first);
        if (found != std::string::npos) {
            foundDigit = pair.second;
            std::cout << "Found the word \"" << pair.first << "\" representing the digit " << foundDigit << std::endl;
            break; // Stop searching after finding the first occurrence
        }
    }

    if (foundDigit == -1) {
        std::cout << "No spelled-out digit found in the string." << std::endl;
    }

    return 0;
}