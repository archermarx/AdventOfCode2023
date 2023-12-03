#ifndef COMMON_H
#define COMMON_H

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <map>
#include <vector>

using std::cout;
using std::string;
using std::vector;
using std::tuple;

// STRING UTILITY FUNCTIONS

const char* ws = " \t\n\r\f\v";

// trim from end of string (right)
inline std::string& rtrim(string& str, const char* t = ws){
    str.erase(str.find_last_not_of(t) + 1);
    return str;
}

// trim from beginning of string (left)
inline string& ltrim(string& str, const char* t = ws){
    str.erase(0, str.find_first_not_of(t));
    return str;
}

// trim from both ends of string (right then left)
inline string& trim(string& str, const char* t = ws){
    return ltrim(rtrim(str, t), t);
}
// split string by delimiter
vector<string> split(string str, string dlm) {
    vector<string> splitstr;

    size_t last = 0;
    size_t next = 0;
    string token;
    while ((next = str.find(dlm, last)) != string::npos) {
        token = str.substr(last, next - last);
        splitstr.push_back(token);
        last = next + 1;
    }

    token = str.substr(last);
    splitstr.push_back(token);

    return splitstr;
}

#endif