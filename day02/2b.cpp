// Kyle DENIS - 21022655 - Advent of Code 2023 Day 2 - Part 2: Cube Conundrum
// Example answer: 2286
// Input answer: 76008

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <unordered_map>

using namespace std;

// Find the minimum number of cubes required for each color in a game
unordered_map<string, int> findMinimumCubes(const vector<unordered_map<string, int>> &subsets) {
    unordered_map<string, int> minimumCubes;

    for (const auto &subset : subsets) {
        for (const auto &[colour, count] : subset) {
            minimumCubes[colour] = max(minimumCubes[colour], count);
        }
    }

    return minimumCubes;
}

// Calculate the power of a set of cubes
int calculatePower(const unordered_map<string, int> &cubes) {
    int power = 1;

    for (const auto &[colour, count] : cubes) {
        power *= count;
    }

    return power;
}

// Parse a subset string and return a map of cube colors and counts
unordered_map<string, int> parseSubset(const string &subset) {
    unordered_map<string, int> colourCounts;
    istringstream subsetStream(subset);
    string cube;

    while (getline(subsetStream, cube, ',')) {
        istringstream cubeStream(cube);
        int count;
        string colour;
        cubeStream >> count >> colour;
        colourCounts[colour] = count;
    }

    return colourCounts;
}

int main() {
    vector<string> gameData;
    ifstream inputFile("./day02-input.txt");

    // Read game data from input file
    if (inputFile.is_open()) {
        string line;
        while (getline(inputFile, line)) {
            gameData.push_back(line);
        }
        inputFile.close();
    } else {
        cout << "Unable to open the input file." << endl;
        return 1;
    }

    int sumOfPowers = 0;

    // Process each game
    for (const auto &game : gameData) {
        istringstream gameStream(game);
        string gameInfo;
        vector<unordered_map<string, int>> subsets;

        // Extract Game ID
        getline(gameStream, gameInfo, ':');

        // Extract subsets of cubes
        while (getline(gameStream, gameInfo, ';')) {
            subsets.push_back(parseSubset(gameInfo));
        }

        // Find the minimum number of cubes required for each color
        unordered_map<string, int> minimumCubes = findMinimumCubes(subsets);

        // Calculate the power of the minimum set of cubes and add it to the sum
        int power = calculatePower(minimumCubes);
        sumOfPowers += power;
    }

    cout << "Sum of powers of minimum sets of cubes: " << sumOfPowers << endl;

    return 0;
}