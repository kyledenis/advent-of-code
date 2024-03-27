// Kyle DENIS - 21022655 - Advent of Code 2023 Day 3: Gear Ratios
// Example answer: 4361
// Input answer: 540212

#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

int main() {
    vector<string> schematic;
    string line;
    ifstream inputFile("./day03-input.txt");

    // Read the engine schematic from the file
    if (inputFile.is_open()) {
        while (getline(inputFile, line)) {
            schematic.push_back(line);
        }
        inputFile.close();
    } else {
        cout << "Unable to open file" << endl;
        return 1;
    }

    int rows = schematic.size();
    int cols = schematic[0].size();
    int sum = 0;

    // Iterate over each character in the schematic
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            // Check if the current character is a digit
            if (isdigit(schematic[i][j])) {
                bool isPartNumber = false;
                int partNumber = 0;

                // Check adjacent cells for symbols
                for (int dx = -1; dx <= 1; dx++) {
                    for (int dy = -1; dy <= 1; dy++) {
                        if (dx == 0 && dy == 0)
                            continue;

                        int nx = i + dx;
                        int ny = j + dy;

                        if (nx >= 0 && nx < rows && ny >= 0 && ny < cols) {
                            if (schematic[nx][ny] != '.' && !isdigit(schematic[nx][ny])) {
                                isPartNumber = true;
                            }
                        }
                    }
                }

                // If it's a part number, calculate its value
                if (isPartNumber) {
                    int startCol = j;
                    while (startCol > 0 && isdigit(schematic[i][startCol - 1])) {
                        startCol--;
                    }
                    int endCol = j;
                    while (endCol < cols - 1 && isdigit(schematic[i][endCol + 1])) {
                        endCol++;
                    }

                    partNumber = stoi(schematic[i].substr(startCol, endCol - startCol + 1));
                    sum += partNumber;
                    j = endCol;
                }
            }
        }
    }

    cout << "Sum of all part numbers: " << sum << endl;

    return 0;
}