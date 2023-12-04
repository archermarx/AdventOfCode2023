#include "common.h"
#include <numeric>

const string exampleInput1 = R"(Game 1: 3 blue, 4 red; 1 red, 2 green, 6 blue; 2 green
Game 2: 1 blue, 2 green; 3 green, 4 blue, 1 red; 1 green, 1 blue
Game 3: 8 green, 6 blue, 20 red; 5 blue, 4 red, 13 green; 5 green, 1 red
Game 4: 1 green, 3 red, 6 blue; 3 green, 6 red; 3 green, 15 blue, 14 red
Game 5: 6 red, 1 blue, 3 green; 2 blue, 1 red, 2 green)";

const vector<int> exampleGames1{1,2,5};

const std::map<string, int> maxCubes1{
    {"red", 12},
    {"green", 13},
    {"blue", 14}
};

const int exampleAnswer1 = std::reduce(exampleGames1.begin(), exampleGames1.end());
const int exampleAnswer2 = 2286;

bool validDraw(string draw) {
    auto splitStr = split(draw, ", ");
    for (auto &s : splitStr ) {
        auto parts = split(trim(s), " ");
        auto key = parts[1];
        auto val = stoi(parts[0]);
        if (val > maxCubes1.at(key)) {
            return false;
        }
    }
    return true;
}

bool validGame(string line) {
    auto draws = split(split(line, ": ")[1], ";");
    for (auto &draw : draws) {
        if (!validDraw(draw)) {
            return false;
        }
    }
    return true;
}

std::map<string, int> parseDraw(string draw) {
    auto ans = std::map<string, int>{{"red", 1}, {"green", 1}, {"blue", 1}};
    auto splitStr = split(draw, ", ");
    for (auto &s : splitStr ) {
        auto parts = split(trim(s), " ");
        auto key = parts[1];
        auto val = stoi(parts[0]);
        ans.at(key) =  val;
    }
    return ans;
}

int gamePower(string game) {
    int maxRed = 1;
    int maxGreen = 1;
    int maxBlue = 1;
    auto draws = split(split(game, ": ")[1], ";");
    for (auto &draw : draws) {
        auto parsed = parseDraw(draw);
        maxRed = std::max(parsed.at("red"), maxRed);
        maxGreen = std::max(parsed.at("green"), maxGreen);
        maxBlue = std::max(parsed.at("blue"), maxBlue);
    }
    return maxRed * maxGreen * maxBlue;
}

template <typename T>
void solution_02_1(T& stream, bool verbose) {
    std::string line;
    int sum = 0;
    int ind = 1;
    while (std::getline(stream, line)) {
        std::istringstream lineStream(line);
        bool isValid = validGame(line);
        if (verbose) {
            cout << "Game " << ind << ": " << isValid << "\n";
        }
        if (isValid) {
            sum += ind;
        }
        ind += 1;
    }

    cout << "Solution: " << sum << "\n";
}

template <typename T>
void solution_02_2(T& stream, bool verbose) {
    std::string line;
    int sum = 0;
    while (std::getline(stream, line)) {
        std::istringstream lineStream(line);
        int power = gamePower(line);
        if (verbose) {
            cout << "Power = " << power << "\n";
        }
        sum += power;
    }
    cout << "Solution: " << sum << "\n";
}


int main() {
    string inputPath = "../input/day02.txt";
    
    cout << "Advent of code day 2!" << "\n";
    cout << "====================================" << "\n";

    cout << "Part 1 example (expected " << exampleAnswer1 << ")\n";
    std::istringstream example01(exampleInput1);
    solution_02_1(example01, true);    
    
    cout << "\nPart 1 solution" << "\n";
    std::ifstream inputLines(inputPath);
    solution_02_1(inputLines, false);

    cout << "====================================" << "\n";

    cout << "Part 2 example (expected " << exampleAnswer2 << ")\n";
    std::istringstream example02(exampleInput1);
    solution_02_2(example02, true);    
    
    cout << "\nPart 2 solution" << "\n";
    std::ifstream inputLines2(inputPath);
    solution_02_2(inputLines2, false);

    return 0;
}