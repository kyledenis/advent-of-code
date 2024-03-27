// Kyle DENIS - 21022655 - Advent of Code 2023 Day 4 - Part 2: Scratchcards
// Example answer: 30
// Input answer: 5329815

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <unordered_set>

using namespace std;

// Parses a line of text into winning numbers and your numbers
bool parseLine(const string& line, vector<int>& winningNumbers, vector<int>& yourNumbers) {
    // Find positions of colon and separator to isolate winning and your numbers
    size_t colonPos = line.find(':');
    size_t delimiterPos = line.find('|', colonPos);
    if (colonPos == string::npos || delimiterPos == string::npos) {
        cerr << "Invalid line format" << endl;
        return false;
    }

    // Extract winning numbers and your numbers from the line
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

// Counts the number of matching numbers between the winning numbers and your numbers
int countMatches(const vector<int>& winningNumbers, const vector<int>& yourNumbers) {
    // Convert winning numbers to a set for efficient look-up
    unordered_set<int> winningSet(winningNumbers.begin(), winningNumbers.end());
    int matches = 0;
    // Count how many numbers in yourNumbers are present in the winningSet
    for (int number : yourNumbers) {
        if (winningSet.find(number) != winningSet.end()) {
            matches++;
        }
    }
    return matches;
}

// Calculates the total number of scratchcards including copies won based on matching numbers
long long calculateTotalScratchcards(vector<vector<int>>& allWinningNumbers, vector<vector<int>>& allYourNumbers) {
    long long totalScratchcards = allWinningNumbers.size(); // Initial count is the number of original scratchcards
    vector<int> scratchcardCopies(allWinningNumbers.size(), 1); // Start with one copy of each scratchcard

    // Iterate over each scratchcard to calculate additional copies won based on matches
    for (size_t i = 0; i < allWinningNumbers.size(); ++i) {
        int copiesToWin = countMatches(allWinningNumbers[i], allYourNumbers[i]);
        // Add extra copies to future scratchcards based on matches
        for (int j = 1; j <= copiesToWin && i + j < allWinningNumbers.size(); ++j) {
            scratchcardCopies[i + j] += scratchcardCopies[i];
        }
    }

    // Total all the copies of scratchcards, excluding the original count
    for (int copies : scratchcardCopies) {
        totalScratchcards += copies - 1; // Subtract 1 to not count the original card twice
    }

    return totalScratchcards;
}

int main() {
    ifstream file("./day04-input.txt");
    if (!file) {
        cerr << "Error opening file!" << endl;
        return 1;
    }

    string line;
    vector<vector<int>> allWinningNumbers, allYourNumbers;

    // Read each line from the file, parse it, and populate the vectors
    while (getline(file, line)) {
        vector<int> winningNumbers, yourNumbers;
        if (parseLine(line, winningNumbers, yourNumbers)) {
            allWinningNumbers.push_back(winningNumbers);
            allYourNumbers.push_back(yourNumbers);
        }
    }

    // Calculate the total number of scratchcards, including the ones won
    long long totalScratchcards = calculateTotalScratchcards(allWinningNumbers, allYourNumbers);
    cout << "Total scratchcards: " << totalScratchcards << endl; // Print the total points after processing all lines

    return 0;
}
