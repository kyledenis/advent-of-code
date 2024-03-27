// Kyle DENIS - 21022655 - Advent of Code 2023 Day 5: If You Give A Seed A Fertilizer
// Example answer: 46
// Input answer:


// Too slow to use on real input data.
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <unordered_map>
#include <limits>
#include <algorithm>

using namespace std;

class Almanac {
private:
    unordered_map<string, vector<pair<long long, pair<long long, long long>>>> mappings;
    vector<pair<long long, long long>> seedRanges;

    void parseLine(const string& line) {
        static string currentMapName;
        if (line.find("map:") != string::npos) {
            currentMapName = line.substr(0, line.find(':'));
            mappings[currentMapName].clear();
        } else if (!line.empty() && line.substr(0, 6) != "seeds:") {
            stringstream ss(line);
            long long start, source, length;
            ss >> start >> source >> length;
            mappings[currentMapName].emplace_back(start, make_pair(source, length));
        } else if (line.find("seeds:") != string::npos) {
            size_t startPos = line.find("seeds:") + 6;
            startPos = line.find_first_not_of(" ", startPos);
            stringstream ss(line.substr(startPos));
            long long start, length;
            while (ss >> start >> length) {
                seedRanges.emplace_back(start, length);
            }
        }
    }

    long long translate(long long number, const string& mapName) {
        auto it = mappings.find(mapName);
        if (it == mappings.end()) {
            return number;
        }

        const auto& map = it->second;
        for (const auto& [start, range] : map) {
            if (number >= range.first && number < range.first + range.second) {
                return start + (number - range.first);
            }
        }
        return number;
    }

public:
    explicit Almanac(const string& filePath) {
        ifstream file(filePath);
        string line;

        while (getline(file, line)) {
            parseLine(line);
        }
    }

    long long findLowestLocation() {
        long long lowestLocation = numeric_limits<long long>::max();

        for (const auto& [start, length] : seedRanges) {
            for (long long i = 0; i < length; ++i) {
                long long seed = start + i;
                long long location = translate(seed, "seed-to-soil map");
                location = translate(location, "soil-to-fertilizer map");
                location = translate(location, "fertilizer-to-water map");
                location = translate(location, "water-to-light map");
                location = translate(location, "light-to-temperature map");
                location = translate(location, "temperature-to-humidity map");
                location = translate(location, "humidity-to-location map");

                lowestLocation = min(lowestLocation, location);
            }
        }

        return lowestLocation;
    }
};

int main() {
    Almanac almanac("day05-example.txt");
    cout << "Lowest location number: " << almanac.findLowestLocation() << endl;
    return 0;
}