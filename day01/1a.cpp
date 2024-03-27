// Kyle DENIS - 21022655 - Advent of Code 2023 Day 1: Trebuchet?!
// Example answer: 142
// Input answer: 54597

#include <iostream>
#include <fstream>
#include <string>
#include <filesystem>

using namespace std;

// Function to find the first digit in a string
int findFirstDigit(const string& line) {
    for (char c : line) {
        if (isdigit(c)) {
            return c - '0';
        }
    }
    return -1;
}

// Function to find the last digit in a string
int findLastDigit(const string& line) {
    for (int i = line.size() - 1; i >= 0; --i) {
        if (isdigit(line[i])) {
            return line[i] - '0';
        }
    }
    return -1;
}

int main() {
    string inputFileName = "./day01-input.txt";

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
    const int BASE = 10;

    // Read the input file line by line
    while (getline(file, line)) {
        if (line.empty()) {
            continue;
        }

        // Find the first and last digit in the line
        int firstDigit = findFirstDigit(line);
        int lastDigit = findLastDigit(line);

        // Calculate the calibration value if both digits are found
        if (firstDigit != -1 && lastDigit != -1) {
            int calibrationValue = firstDigit * BASE + lastDigit;
            sum += calibrationValue;
        }
    }

    file.close();

    cout << "The sum of all the calibration values is: " << sum << endl;

    return 0;
}