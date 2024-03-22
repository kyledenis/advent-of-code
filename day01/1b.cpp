// Kyle DENIS - 21022655 - Advent of Code 2023 Day 1 - Part 2: Trebuchet?!
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <fstream>

using namespace std; // Stops the need to use std:: prefix

unordered_map<string, int> digit_map = {
    {"zero", 0}, {"one", 1}, {"two", 2}, {"three", 3}, {"four", 4},
    {"five", 5}, {"six", 6}, {"seven", 7}, {"eight", 8}, {"nine", 9}
};

// Find digit and convert if necessary
int get_digit(const string &word) {
    for (const auto &entry : digit_map) {
        if (word.find(entry.first) == 0) {
            return entry.second;
        }
    }

    if (!word.empty() && isdigit(word[0])) {
        return word[0] - '0'; // Convert char to int
    }

    return -1;
}

int main() {
    string filename = "puzzle-input.txt";
    ifstream file(filename);

    if (!file.is_open()) {
        cout << "Failed to open file: " << filename << endl;
        return 1;
    }

    string line;
    int total_sum = 0;
    const int base = 10;

    while (getline(file, line)) {
        cout << "Processing line: " << line << endl;

        int first_digit = -1;
        int last_digit = -1;

        // First digit
        for (int i = 0; i < line.length(); ++i) {
            string word;
            for (int j = i; j < line.length(); ++j) {
                word += line[j];
                cout << "  Word: " << word << endl;
                int digit = get_digit(word);
                if (digit != -1) {
                    first_digit = digit;
                    cout << "  Detected digit: " << word << " -> " << first_digit << endl;
                    i = j;  // Skip the characters already processed
                    break;
                }
            }
            if (first_digit != -1) {
                break;
            }
        }

        // Last digit
        for (int i = line.length() - 1; i >= 0; --i) {
            string word;
            for (int j = i; j >= 0; --j) {
                word = line[j] + word;
                cout << "  Word: " << word << endl;
                int digit = get_digit(word);
                if (digit != -1) {
                    last_digit = digit;
                    cout << "  Detected digit: " << word << " -> " << last_digit << endl;
                    i = j - 1;  // Skip the characters already processed
                    break;
                }
            }
            if (last_digit != -1) {
                break;
            }
        }

        // Summation
        if (first_digit != -1 && last_digit != -1) {
            int calibration_value = first_digit * base + last_digit;
            cout << "  Calibration value: " << calibration_value << endl;
            total_sum += calibration_value;
        }

        cout << endl; // Add a new line for better readability
    }

    cout << "Total sum of calibration values: " << total_sum << endl;

    file.close();

    return 0;
}