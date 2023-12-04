#include "common.h"

const string exampleInput1 = R"(467..114..
...*......
..35..633.
......#...
617*......
.....+.58.
..592.....
......755.
...$.*....
.664.598..)";

const string symbols = "@#$%&*/+=-";

template <typename T>
vector<string> getLines(T& stream) {
    vector<string> lines;
    string line;
    while (std::getline(stream, line)) {
        std::istringstream lineStream(line);
        lines.push_back(line);
    }
    return lines;
}

bool isSymbol(char c) {
    return !isdigit(c) && c != '.';//symbols.find(c) != string::npos;
}

bool checkSymbolAtInd(const vector<string> lines, const std::pair<size_t, size_t> neighborInd) {
    const size_t N = lines[0].length();
    const size_t M = lines.size();
    auto [i, j] = neighborInd;
    if (i >= N || i < 0|| j>= M || j < 0) {
        return false;
    }
    return isSymbol(lines[j][i]);
}

bool checkNeighborhood(const vector<string> lines, const size_t i, const size_t j) {
    bool neighborhoodContainsSymbol = false;

    // indices for nine-point stencil
    const auto inds = vector<std::pair<size_t, size_t>>{
        std::make_pair(i-1, j-1),
        std::make_pair(i-1, j),
        std::make_pair(i-1, j+1),
        std::make_pair(i, j-1),
        std::make_pair(i, j+1),
        std::make_pair(i+1, j-1),
        std::make_pair(i+1, j),
        std::make_pair(i+1, j+1) 
    };

    for (auto &ind : inds) {
        neighborhoodContainsSymbol = neighborhoodContainsSymbol || checkSymbolAtInd(lines, ind);
    }

    return neighborhoodContainsSymbol;
}

int partNumberSum(vector<string> lines, bool verbose) {
    const size_t N = lines[0].length();
    const size_t M = lines.size();

    vector<int> numbers;

    for (size_t j = 0; j < M; j++) {
        bool insideNumber = false;
        bool foundSymbol = false;
        string acc = "";

        for (size_t i = 0; i < N; i++) {
            char c = lines[j][i];
            if (isdigit(c)) {
                if (!insideNumber) {
                    acc = c;
                    insideNumber = true;
                } else {
                    acc += c;
                }
                foundSymbol = foundSymbol || checkNeighborhood(lines, i, j);

                if ((i == N - 1) && foundSymbol) {
                    numbers.push_back(stoi(acc));
                } 
            } else {
                if (insideNumber) {
                    insideNumber = false;
                    if (foundSymbol) {
                        numbers.push_back(stoi(acc));
                        acc = "";
                        foundSymbol = false;
                    }
                }
            }
        }
    }

    int sum = 0;
    for (auto number : numbers) {
        if (verbose) {
            cout << number << "\n";
        }
        sum += number;
    }

    return sum;
}



int main() {
    string inputPath = "../input/day03.txt";
    
    cout << "Advent of code day 3!" << "\n";
    cout << "====================================" << "\n";
    

    cout << "Part 1 example (expected " << 4361 << ")\n";
    std::istringstream example01(exampleInput1);
    cout << "Answer: " << partNumberSum(getLines(example01), false) << "\n";

    cout << "\nPart 1 solution" << "\n";
    std::ifstream inputLines(inputPath);
    cout << "Answer: " << partNumberSum(getLines(inputLines), false) << "\n";

    cout << "====================================" << "\n";
}