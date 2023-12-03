#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

using std::cout;
using std::string;

const string exampleInput = R"(1abc2
pqr3stu8vwx
a1b2c3d4e5f
treb7uchet)";

template <typename T>
void solution_01(T& stream) {
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
                //cout.put(c);
                lastDigit = c - '0';
            }
        }

        //cout << "\n";

        sum += 10 * firstDigit + lastDigit;
        //std::cout << firstDigit << ", " << lastDigit << "\n";
    }

    cout << "Sum = " << sum << "\n";
}

int main() {
    cout << "Advent of code day 1!" << "\n";

    //std::istringstream inputLines(exampleInput);
    std::ifstream inputLines("../input/day01.txt");
    solution_01(inputLines);
}

