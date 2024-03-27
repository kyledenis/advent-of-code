// Kyle DENIS - 21022655 - Advent of Code 2023 Day 1 - Part 2: Trebuchet?!
// Example answer: 281
// Input answer: 54504

#include <iostream>
#include <string>
#include <unordered_map>
#include <fstream>

using namespace std;

unordered_map<string, int> digitMap = {
    {"zero", 0}, {"one", 1}, {"two", 2}, {"three", 3}, {"four", 4},
    {"five", 5}, {"six", 6}, {"seven", 7}, {"eight", 8}, {"nine", 9}
};

// Find digit and convert if necessary
int getDigit(const string &word) {
    for (const auto &entry : digitMap) {
        if (word.find(entry.first) == 0) {
            return entry.second;
        }
    }

    if (!word.empty() && isdigit(word[0])) {
        return word[0] - '0'; // Convert char to int
    }

    return -1;
}

void findFirstDigit(const string &line, int &firstDigit) {
    for (int i = 0; i < line.length(); ++i) {
        string word;
        for (int j = i; j < line.length(); ++j) {
            word += line[j];
            cout << "  Word: " << word << endl;
            int digit = getDigit(word);
            if (digit != -1) {
                firstDigit = digit;
                cout << "  Detected digit: " << word << " -> " << firstDigit << endl;
                i = j;  // Skip characters already processed
                return;
            }
        }
    }
}

void findLastDigit(const string &line, int &lastDigit) {
    for (int i = line.length() - 1; i >= 0; --i) {
        string word;
        for (int j = i; j >= 0; --j) {
            word = line[j] + word;
            cout << "  Word: " << word << endl;
            int digit = getDigit(word);
            if (digit != -1) {
                lastDigit = digit;
                cout << "  Detected digit: " << word << " -> " << lastDigit << endl;
                i = j - 1;  // Skip the characters already processed
                return;
            }
        }
    }
}

int main() {
    string filename = "./day01-input.txt";
    ifstream file(filename);

    if (!file.is_open()) {
        cerr << "Failed to open file: " << filename << endl;
        return 1;
    }

    string line;
    int totalSum = 0;
    const int BASE = 10;

    while (getline(file, line)) {
        cout << "Processing line: " << line << endl;

        int firstDigit = -1;
        int lastDigit = -1;

        findFirstDigit(line, firstDigit);
        findLastDigit(line, lastDigit);

        if (firstDigit != -1 && lastDigit != -1) {
            int calibrationValue = firstDigit * BASE + lastDigit;
            cout << "  Calibration value: " << calibrationValue << endl;
            totalSum += calibrationValue;
        }

        cout << endl;
    }

    cout << "Total sum of calibration values: " << totalSum << endl;

    file.close();

    return 0;
}