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
    map<string, vector<tuple<long long, long long, long long>>> mappings;
    vector<long long> seeds;

    void parseLine(const string& line) {
        static string currentMapName;
        if (line.find("map:") != string::npos) {
            currentMapName = line.substr(0, line.find(':'));
            mappings[currentMapName] = {};
        } else if (!line.empty() && line.substr(0, 6) != "seeds:") {
            stringstream ss(line);
            long long start, source, length;
            ss >> start >> source >> length;
            mappings[currentMapName].emplace_back(start, source, length);
        } else if (line.find("seeds:") != string::npos) {
            size_t startPos = line.find("seeds:") + 6;
            startPos = line.find_first_not_of(" ", startPos);
            stringstream ss(line.substr(startPos));
            long long seed;
            while (ss >> seed) {
                seeds.push_back(seed);
            }
        }
    }

    long long translate(long long number, const string& mapName) {
        cout << "Translating in " << mapName << ": " << number << " -> ";
        auto it = mappings.find(mapName);
        if (it == mappings.end()) {
            cout << "Error: map '" << mapName << "' not found." << endl;
            return number;
        }

        const auto& map = it->second;
        for (const auto& [start, source, length] : map) {
            if (number >= source && number < source + length) {
                long long translated = start + (number - source);
                cout << translated << " (within range)" << endl;
                return translated;
            }
        }
        cout << number << " (default)" << endl;
        return number;
    }

public:
    explicit Almanac(const string& filePath) {
        ifstream file(filePath);
        string line;

        while (getline(file, line)) {
            parseLine(line);
        }

        cout << "Total seeds loaded: " << seeds.size() << endl;
    }

    long long findLowestLocation() {
        long long lowestLocation = numeric_limits<long long>::max();
        cout << "Processing " << seeds.size() << " seeds." << endl;
        for (long long seed : seeds) {
            cout << "Processing seed: " << seed << endl;
            long long soil = translate(seed, "seed-to-soil map");
            long long fertiliser = translate(soil, "soil-to-fertilizer map");
            long long water = translate(fertiliser, "fertilizer-to-water map");
            long long light = translate(water, "water-to-light map");
            long long temperature = translate(light, "light-to-temperature map");
            long long humidity = translate(temperature, "temperature-to-humidity map");
            long long location = translate(humidity, "humidity-to-location map");

            cout << "Seed: " << seed
                 << ", Soil: " << soil
                 << ", Fertiliser: " << fertiliser
                 << ", Water: " << water
                 << ", Light: " << light
                 << ", Temperature: " << temperature
                 << ", Humidity: " << humidity
                 << ", Location: " << location << "\n" << endl;

            lowestLocation = min(lowestLocation, location);
        }

        cout << "Lowest location number: " << lowestLocation << endl;
        return lowestLocation;
    }
};

int main() {
    Almanac almanac("./day05-input.txt");
    almanac.findLowestLocation();
    return 0;
}
