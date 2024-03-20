#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <fstream>

using namespace std;

unordered_map<string, int> digit_map = {
    {"zero", 0}, {"one", 1}, {"two", 2}, {"three", 3}, {"four", 4},
    {"five", 5}, {"six", 6}, {"seven", 7}, {"eight", 8}, {"nine", 9}
};

int get_digit(const string& word) {
    for (const auto& entry : digit_map) {
        if (word.find(entry.first) != string::npos) {
            return entry.second;
        }
    }
    return isdigit(word[0]) ? word[0] - '0' : -1;
}

int main() {
    string filename = "aoc1b_test-case.txt";
    ifstream file(filename);

    if (!file.is_open()) {
        cout << "Failed to open file: " << filename << endl;
        return 1;
    }

    string line;
    int total_sum = 0;

    while (getline(file, line)) {
        cout << "Processing line: " << line << endl;

        int first_digit = -1;
        int last_digit = -1;

        for (int i = 0; i < line.length(); ++i) {
            string word;
            for (int j = i; j < line.length(); ++j) {
                word += line[j];
                cout << "  Word: " << word << endl;
                int digit = get_digit(word);
                if (digit != -1) {
                    first_digit = digit;
                    cout << "  Detected written digit: " << word << " -> " << first_digit << endl;
                    break;
                }
            }
            if (first_digit != -1) {
                break;
            }
        }

        for (int i = line.length() - 1; i >= 0; --i) {
            string word;
            for (int j = i; j >= 0; --j) {
                word = line[j] + word;
                cout << "  Word: " << word << endl;
                int digit = get_digit(word);
                if (digit != -1) {
                    last_digit = digit;
                    cout << "  Detected written digit: " << word << " -> " << last_digit << endl;
                    break;
                }
            }
            if (last_digit != -1) {
                break;
            }
        }

        if (first_digit != -1 && last_digit != -1) {
            int calibration_value = first_digit * 10 + last_digit;
            cout << "  Calibration value: " << calibration_value << endl;
            total_sum += calibration_value;
        }

        cout << endl;
    }

    cout << "Total sum of calibration values: " << total_sum << endl;

    file.close();

    return 0;
}