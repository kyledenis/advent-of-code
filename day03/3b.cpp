// Kyle DENIS - 21022655 - Advent of Code 2023 Day 3 - Part 2: Gear Ratios
// Example answer: 467835
// Input answer: 87605697

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <set>

using namespace std;

// Extracts part number starting from the given row and column in the schematic
int extractPartNumber(const vector<string>& schematic, int& row, int& col) {
    int startCol = col;
    while (startCol > 0 && isdigit(schematic[row][startCol - 1])) {
        --startCol;
    }

    int endCol = col;
    while (endCol < schematic[row].length() && isdigit(schematic[row][endCol])) {
        ++endCol;
    }

    col = endCol; // Update column to the end of the part number
    return stoi(schematic[row].substr(startCol, endCol - startCol));
}

vector<int> getAdjacentPartNumbers(const vector<string>& schematic, int row, int col, set<pair<int, int>>& visited) {
    vector<int> partNumbers;

    for (int r = row - 1; r <= row + 1; ++r) {
        for (int c = col - 1; c <= col + 1; ++c) {
            if (r >= 0 && r < schematic.size() && c >= 0 && c < schematic[r].length() && isdigit(schematic[r][c])) {
                if (visited.find({r, c}) == visited.end()) {
                    visited.insert({r, c});
                    partNumbers.push_back(extractPartNumber(schematic, r, c));

                    if (partNumbers.size() == 2) {
                        return partNumbers;
                    }
                }
            }
        }
    }

    return partNumbers;
}

// Calculates the sum of gear ratios in the schematic
long long calculateGearRatioSum(const vector<string>& schematic) {
    long long totalGearRatio = 0;
    set<pair<int, int>> visited;

    for (int row = 0; row < schematic.size(); ++row) {
        for (int col = 0; col < schematic[row].length(); ++col) {
            if (schematic[row][col] == '*') {
                vector<int> partNumbers = getAdjacentPartNumbers(schematic, row, col, visited);

                if (partNumbers.size() == 2) {
                    long long gearRatio = static_cast<long long>(partNumbers[0]) * partNumbers[1];
                    totalGearRatio += gearRatio;
                    cout << "Gear at (" << row << ", " << col
                         << ") with part numbers " << partNumbers[0]
                         << " and " << partNumbers[1]
                         << " has gear ratio: " << gearRatio << endl;
                }
            }
        }
    }

    return totalGearRatio;
}

int main() {
    vector<string> schematic;
    ifstream inputFile("./day03-input.txt");

    if (!inputFile.is_open()) {
        cerr << "Unable to open file" << endl;
        return 1;
    }

    string line;
    while (getline(inputFile, line)) {
        schematic.push_back(line);
    }
    inputFile.close();

    long long totalGearRatio = calculateGearRatioSum(schematic);
    cout << "Sum of all gear ratios: " << totalGearRatio << endl;

    return 0;
}