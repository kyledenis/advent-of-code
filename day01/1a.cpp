// Kyle DENIS - 21022655 - Advent of Code 2023 Day 1: Trebuchet?!
#include <iostream>
#include <fstream>
#include <string>
#include <filesystem>

using namespace std; // Stops the need to use std:: prefix

int main() {
    string inputFileName = "puzzle-input.txt";

    // Check if the file exists
    if (!filesystem::exists(inputFileName)) {
        cerr << "Error: file '" << inputFileName << "' not found." << endl;
        return 1;
    }

    ifstream file(inputFileName);
    if (!file) {
        cerr << "Error: file '" << inputFileName << "' cannot be opened." << endl;
        return 1;
    }

    string line;
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

    cout << "The sum of all the calibration values is: " << sum << endl;

    return 0;
}
