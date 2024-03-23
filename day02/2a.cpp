// Kyle DENIS - 21022655 - Advent of Code 2023 Day 2: Cube Conundrum
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <unordered_map>

using namespace std; // Stops the need to use std:: prefix

// Check if game is possible given the available cubes
bool isGamePossible(const vector<unordered_map<string, int>> &subsets, int redCubes, int greenCubes, int blueCubes) {
    for (const auto &subset : subsets) {
        if (subset.count("red") > 0 && subset.at("red") > redCubes)
            return false;
        if (subset.count("green") > 0 && subset.at("green") > greenCubes)
            return false;
        if (subset.count("blue") > 0 && subset.at("blue") > blueCubes)
            return false;
    }
    return true;
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
    ifstream inputFile("day02-input.txt");

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

    const int RED_CUBES = 12;
    const int GREEN_CUBES = 13;
    const int BLUE_CUBES = 14;
    int sumOfPossibleGameIDs = 0;

    // Process each game
    for (const auto &game : gameData) {
        istringstream gameStream(game);
        string gameInfo;
        vector<unordered_map<string, int>> subsets;

        // Extract Game ID
        getline(gameStream, gameInfo, ':');
        int gameID = stoi(gameInfo.substr(5)); // Convert Game ID to int

        // Extract subsets of cubes
        while (getline(gameStream, gameInfo, ';')) {
            subsets.push_back(parseSubset(gameInfo));
        }

        // If game is possible, add its ID to the sum
        if (isGamePossible(subsets, RED_CUBES, GREEN_CUBES, BLUE_CUBES)) {
            sumOfPossibleGameIDs += gameID;
        }
    }

    cout << "Sum of IDs of possible games: " << sumOfPossibleGameIDs << endl;

    return 0;
}