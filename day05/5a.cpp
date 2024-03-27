// Kyle DENIS - 21022655 - Advent of Code 2023 Day 5: If You Give A Seed A Fertilizer
// Example answer: 35
// Input answer: 600279879

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <map>
#include <limits>

using namespace std;

class Almanac {
private:
    // Holds mapping data for translating numbers from one form to another
    map<string, vector<tuple<long long, long long, long long>>> translationMaps;
    // Stores the list of seeds to be processed
    vector<long long> seeds;

    // Parses a single line from the input file
    void parseLine(const string& line) {
        static string currentMapName; // Stores the current map name across calls
        if (line.find("map:") != string::npos) {
            // When a new map is found, reset the current map name and prepare for new entries
            currentMapName = line.substr(0, line.find(':'));
            translationMaps[currentMapName] = {};
        } else if (!line.empty() && line.substr(0, 6) != "seeds:") {
            // Parse translation line if it's not a seed line
            parseTranslationLine(line, currentMapName);
        } else if (line.find("seeds:") != string::npos) {
            // Parse seed line to populate the seeds vector
            parseSeedLine(line);
        }
    }

    // Parses a line containing translation data and adds it to the map
    void parseTranslationLine(const string& line, const string& mapName) {
        stringstream ss(line);
        long long start, source, length;
        ss >> start >> source >> length;
        translationMaps[mapName].emplace_back(start, source, length);
    }

    // Parses a line containing seed data and adds the seeds to the list
    void parseSeedLine(const string& line) {
        size_t startPos = line.find("seeds:") + 6;
        startPos = line.find_first_not_of(" ", startPos);
        stringstream ss(line.substr(startPos));
        long long seed;
        while (ss >> seed) {
            seeds.push_back(seed);
        }
    }

    // Translates a number according to the specified map
    long long translate(long long number, const string& mapName) {
        auto it = translationMaps.find(mapName);
        if (it == translationMaps.end()) {
            cerr << "Error: map '" << mapName << "' not found." << endl;
            return number;
        }

        for (const auto& [start, source, length] : it->second) {
            if (number >= source && number < source + length) {
                return start + (number - source);
            }
        }
        return number;
    }

public:
    // Constructor that initializes the Almanac by parsing a file
    explicit Almanac(const string& filePath) {
        ifstream file(filePath);
        string line;

        while (getline(file, line)) {
            parseLine(line);
        }

        cout << "Total seeds loaded: " << seeds.size() << "\n" << endl;
    }

    // Finds and returns the lowest location value among all seeds
    long long findLowestLocation() {
        long long lowestLocation = numeric_limits<long long>::max();
        cout << "Processing " << seeds.size() << " seeds." << "\n" << endl;
        for (long long seed : seeds) {
            long long location = processSeed(seed);
            lowestLocation = min(lowestLocation, location);
        }

        cout << "Lowest location number: " << lowestLocation << endl;
        return lowestLocation;
    }

    // Processes a single seed through all translation stages to find its location
    long long processSeed(long long seed) {
        cout << "Processing seed: " << seed << endl;
        vector<string> stages = {
            "seed-to-soil map", "soil-to-fertilizer map", "fertilizer-to-water map",
            "water-to-light map", "light-to-temperature map", "temperature-to-humidity map",
            "humidity-to-location map"
        };
        long long currentResult = seed;

        for (const string& stage : stages) {
            currentResult = translate(currentResult, stage);
        }

        cout << "Seed: " << seed << ", Location: " << currentResult << "\n" << endl;
        return currentResult;
    }
};

// Initializes the Almanac and finds the lowest location
int main() {
    Almanac almanac("./day05-input.txt");
    almanac.findLowestLocation();

    return 0;
}
