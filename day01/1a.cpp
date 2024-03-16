// Kyle DENIS - 21022655 - Advent of Code 2023 Day 1: Trebuchet?! v.4
#include <iostream>
#include <fstream>
#include <string>
#include <filesystem>

int main() {
    std::string inputFileName = "puzzle-input.txt";

    // Check if the file exists
    if (!std::filesystem::exists(inputFileName)) {
        std::cerr << "Error: file '" << inputFileName << "' not found." << std::endl;
        return 1;
    }

    std::ifstream file(inputFileName);
    if (!file) {
        std::cerr << "Error: file '" << inputFileName << "' cannot be opened." << std::endl;
        return 1;
    }

    std::string line;
    int sum = 0;
    const int base = 10;

    while (getline(file, line)) {
        if (line.empty()) {
            continue;
        }

        int firstDigit = -1;
        int lastDigit = -1;

        // Find the first and last digit in the line simultaneously
        for (size_t i = 0, j = line.size() - 1; i < line.size() && (firstDigit == -1 || lastDigit == -1); ++i, --j) {
            if (firstDigit == -1 && isdigit(line[i])) {
                firstDigit = line[i] - '0';
            }

            if (lastDigit == -1 && isdigit(line[j])) {
                lastDigit = line[j] - '0';
            }

            // Break the loop if both digits are found
            if (firstDigit != -1 && lastDigit != -1) {
                break;
            }
        }

        if (firstDigit != -1 && lastDigit != -1) {
            int calibrationValue = firstDigit * base + lastDigit;
            sum += calibrationValue;

        }
    }

    std::cout << "The sum of all the calibration values is: " << sum << std::endl;

    return 0;
}
