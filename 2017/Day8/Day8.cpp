#include "stdafx.h"
#include <fstream>
#include <vector>
#include <string>
#include <iostream>
#include <chrono>
#include <iterator>
#include <functional>
#include <algorithm>
#include <regex>
#include <unordered_map>

using namespace std;
using std::regex;

static std::unordered_map<std::string, std::function<bool(int, int)> > const cmp{ 
{ { "==", std::equal_to<void>() },{ "!=", std::not_equal_to<void>() },
{ "<=", std::less_equal<void>() },{ "<", std::less<void>() },
{ ">=", std::greater_equal<void>() },{ ">", std::greater<void>() } } };

int _tmain(int argc, _TCHAR* argv[])
{
    ifstream myfile("Input.txt");

    string line;
    unordered_map<string, int> registers;

    int maxValue = INT_MIN;

    const auto begin = std::chrono::high_resolution_clock::now();

    if (myfile.is_open()) {

        const regex base_regex("^(\\w+) (dec|inc) (-?\\d+) if (\\w+) ([><=!]=?) (-?\\d+)$");

        smatch pieces_match;

        while (getline(myfile, line)) {
            if (!line.empty()) {
                if (regex_match(line, pieces_match, base_regex)) {
                    // Now check the condition
                    string condition = pieces_match[5];
                    bool condResult = false;

                    if (cmp.at(condition)(registers[pieces_match[4]], stoi(pieces_match[6]))) {
                        // Contition is true. Do the operation
                        string operation = pieces_match[2];

                        if (operation == "inc") {
                            registers[pieces_match[1]] += stoi(pieces_match[3]);
                        }
                        else if (operation == "dec") {
                            registers[pieces_match[1]] -= stoi(pieces_match[3]);
                        }
                    }

                    maxValue = std::max(maxValue, registers[pieces_match[1]]);
                }
            }
        }
    }
    else {
        cout << "cannot open file " << endl;
        return 0;
    }

    auto x = std::max_element(registers.begin(), registers.end(),
        [](const pair<string, int>& p1, const pair<string, int>& p2) { return p1.second < p2.second; });

    cout << x->first << " : " << x->second << endl;
    cout << "Maximum value in register " << maxValue << endl;

    const auto end = std::chrono::high_resolution_clock::now();
    std::cout << std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin).count() << " ns for part one" << std::endl;

    cout << endl;
    cin.ignore();

    return 0;
}