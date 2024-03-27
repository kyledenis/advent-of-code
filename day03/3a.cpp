// Kyle DENIS - 21022655 - Advent of Code 2023 Day 3: Gear Ratios
// Example answer: 4361
// Input answer: 540212

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cctype>

using namespace std;

// Check if the given position is adjacent to a symbol
bool isAdjacentToSymbol(const vector<string>& schematic, int row, int col) {
    const int rows = schematic.size();
    const int cols = schematic[0].size();

    for (int dx = -1; dx <= 1; dx++) {
        for (int dy = -1; dy <= 1; dy++) {
            if (dx == 0 && dy == 0) continue; // Skip the current cell

            int adjacentRow = row + dx;
            int adjacentCol = col + dy;

            // Check boundaries
            if (adjacentRow >= 0 && adjacentRow < rows && adjacentCol >= 0 && adjacentCol < cols) {
                char adjacentChar = schematic[adjacentRow][adjacentCol];
                if (adjacentChar != '.' && !isdigit(adjacentChar)) {
                    return true;
                }
            }
        }
    }
    return false;
}

// Calculate the part number starting from the given position
int calculatePartNumber(const vector<string>& schematic, int row, int& col) {
    const int cols = schematic[row].size();
    int startCol = col;
    while (startCol > 0 && isdigit(schematic[row][startCol - 1])) {
        startCol--;
    }

    int endCol = col;
    while (endCol < cols && isdigit(schematic[row][endCol])) {
        endCol++;
    }

    // Adjust col to the end of the current part number to avoid re-evaluation
    col = endCol - 1;

    return stoi(schematic[row].substr(startCol, endCol - startCol));
}

int main() {
    vector<string> schematic;
    string line;
    ifstream inputFile("./day03-input.txt");

    // Read the engine schematic from the file
    if (inputFile.is_open()) {
        while (getline(inputFile, line)) {
            schematic.push_back(line);
        }
    } else {
        cerr << "Unable to open file" << endl;
        return 1;
    }

    int totalPartNumbersSum = 0;

    // Iterate over each row in the schematic
    for (int row = 0; row < schematic.size(); row++) {
        // Iterate over each column in the current row
        for (int col = 0; col < schematic[row].size(); col++) {
            // Check if the current character is a digit and is adjacent to a symbol
            if (isdigit(schematic[row][col]) && isAdjacentToSymbol(schematic, row, col)) {
                // Calculate the part number and add it to the total sum
                totalPartNumbersSum += calculatePartNumber(schematic, row, col);
            }
        }
    }

    cout << "Sum of all part numbers: " << totalPartNumbersSum << endl;

    return 0;
}
