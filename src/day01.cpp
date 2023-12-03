#include "common.h"

const string exampleInput1 = R"(1abc2
pqr3stu8vwx
a1b2c3d4e5f
treb7uchet)";

const string exampleInput2 = R"(two1nine
eightwothree
abcone2threexyz
xtwone3four
4nineeightseven2
zoneight234
7pqrstsixteen)";

const std::map<string, int> digitMap{
    {"one", 1},
    {"two", 2},
    {"three", 3},
    {"four", 4},
    {"five", 5},
    {"six", 6},
    {"seven", 7},
    {"eight", 8},
    {"nine", 9}
};

std::pair<size_t, int> findFirstDigit(string str){
    
    size_t firstPos = string::npos;
    int firstDigit = 0;

    // Find which digit occurs first and its position
    for (auto &[digit, val]: digitMap) {
        size_t pos = str.find(digit, 0);   // Find first occurance of digit;
        if (pos < firstPos) {
            firstPos = pos;
            firstDigit = val;
        }
    }

    return std::make_pair(firstPos, firstDigit);
}

std::pair<size_t, int> findLastDigit(string str){
    
    int lastPos = -1;
    int lastDigit = 0;

    // Find which digit occurs first and its position
    for (auto &[digit, val]: digitMap) {
        size_t pos = str.rfind(digit);   // Find first occurance of digit;
        
        if (pos != string::npos) {
            //cout << "\n{" << str << ", " << digit << ", " << pos << lastPos << "}\n";        
            if (int(pos) > lastPos) {
                lastPos = pos;
                lastDigit = val;
            }
        }
    }
    return std::make_pair(lastPos, lastDigit);
}

template <typename T>
void solution_01_1(T& stream) {
    std::string line;
    int sum = 0;
    while (std::getline(stream, line)) {
        std::istringstream lineStream(line);
        char c;

        bool isFirstDigit = true;
        int firstDigit = -1;
        int lastDigit = -1;

        while(lineStream.get(c)) {
            if (isdigit(c)) {
                if (isFirstDigit) {
                    firstDigit = c - '0';
                    isFirstDigit = false;
                }
                lastDigit = c - '0';
            }
        }
        sum += 10 * firstDigit + lastDigit;
    }
    cout << "Sum = " << sum << "\n";
}

template <typename T>
void solution_01_2(T& stream, bool verbose) {
    std::string line;
    int sum = 0;
    while (std::getline(stream, line)) {
        auto [firstPos, firstDigit] = findFirstDigit(line);
        auto [lastPos, lastDigit] = findLastDigit(line);
        
        std::istringstream lineStream(line);
        char c;

        bool isFirstDigit = true;
        int firstDigit_numeral = -1;
        int lastDigit_numeral = -1;

        size_t firstPos_numeral = string::npos;
        size_t lastPos_numeral = string::npos;
        size_t pos = 0;

        while(lineStream.get(c)) {
            if (isdigit(c)) {
                if (isFirstDigit) {
                    firstDigit_numeral = c - '0';
                    firstPos_numeral = pos;
                    isFirstDigit = false;
                }
                lastDigit_numeral = c - '0';
                lastPos_numeral = pos;
            }
            pos++;
        }

        if (verbose) {
            cout << line << " => ";
            cout << firstDigit << "("<< firstPos << "), " << lastDigit << "(" << lastPos << ") => ";
            cout << firstDigit_numeral << "(" << firstPos_numeral << "), " << lastDigit_numeral << "(" << lastPos_numeral << ") => ";
        }

        if ((firstPos_numeral != string::npos && firstPos_numeral < firstPos) || firstPos == string::npos) {
            firstDigit = firstDigit_numeral;
        }

        if ((lastPos_numeral != string::npos && lastPos_numeral > lastPos) || lastPos == string::npos) {
            lastDigit = lastDigit_numeral;
        }

        if (verbose) {
            cout << firstDigit << ", " << lastDigit << "\n";
        }

        sum += 10 * firstDigit + lastDigit;
    }
    cout << "Sum = " << sum << "\n";
}

int main() {
    string inputPath = "../input/day01.txt";
    
    cout << "Advent of code day 1!" << "\n";
    cout << "====================================" << "\n";

    cout << "Part 1 example (expected 142)" << "\n";
    std::istringstream example01(exampleInput1);
    solution_01_1(example01);    
    
    cout << "\nPart 1 solution" << "\n";
    std::ifstream inputLines(inputPath);
    solution_01_1(inputLines);

    cout << "====================================" << "\n";
    cout << "\nPart 2 example (expected 281)" << "\n";
    std::istringstream example02(exampleInput2);
    solution_01_2(example02, true);

    cout << "\nPart 2 solution" << "\n";
    std::ifstream inputLines2(inputPath);
    solution_01_2(inputLines2, false);
}

