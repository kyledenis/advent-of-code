// Kyle DENIS - 21022655 - Advent of Code 2023 Day 4: Scratchcards
// Example answer: 13
// Input answer: 21105

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <unordered_set>
#include <cmath>

using namespace std;

constexpr char NUMBER_SEPARATOR = '|';
constexpr char ENTRY_DELIMITER = ':';

bool parseLine(const string& line, vector<int>& winningNumbers, vector<int>& yourNumbers) {
    size_t colonPos = line.find(ENTRY_DELIMITER);
    if (colonPos == string::npos) {
        cerr << "Invalid line format: No colon found!" << endl;
        return false;
    }

    size_t delimiterPos = line.find(NUMBER_SEPARATOR, colonPos);
    if (delimiterPos == string::npos) {
        cerr << "Invalid line format: No separator found!" << endl;
        return false;
    }

    istringstream winningStream(line.substr(colonPos + 2, delimiterPos - colonPos - 2));
    istringstream yourStream(line.substr(delimiterPos + 2));

    int number;
    while (winningStream >> number) {
        winningNumbers.push_back(number);
    }
    while (yourStream >> number) {
        yourNumbers.push_back(number);
    }

    return true;
}

int calculatePoints(const vector<int>& winningNumbers, const vector<int>& yourNumbers) {
    unordered_set<int> winningSet(winningNumbers.begin(), winningNumbers.end());
    int matches = 0;
    for (int number : yourNumbers) {
        if (winningSet.count(number) > 0) {
            matches++;
        }
    }
    return matches > 0 ? pow(2, matches - 1) : 0;
}

void printNumbers(const string& label, const vector<int>& numbers) {
    cout << label << ": ";
    for (int num : numbers) {
        cout << num << " ";
    }
    cout << "\n";
}

int main() {
    ifstream file("./day04-input.txt");
    if (!file) {
        cerr << "Error opening file!" << endl;
        return 1;
    }

    long long totalPoints = 0;
    string line;
    while (getline(file, line)) {
        vector<int> winningNumbers, yourNumbers;
        if (!parseLine(line, winningNumbers, yourNumbers)) {
            continue;
        }

        int points = calculatePoints(winningNumbers, yourNumbers);
        totalPoints += points;

        printNumbers("Winning numbers", winningNumbers);
        printNumbers("Your numbers", yourNumbers);
        cout << "Matches: " << points <<
        "\nPoints: " << points << "\n" << endl;
    }

    cout << "Total points: " << totalPoints << endl;
    return 0;
}
