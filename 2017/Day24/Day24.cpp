#include "stdafx.h"
#include <vector>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <iostream>
#include <chrono>
#include <bitset>
#include <map>
#include <sstream>
#include <algorithm>

using namespace std;

struct Component {
    int left_port, right_port;
    bool connected = false;
};

vector<Component> components;

auto maxStrength = 0;
auto maxLength = 0;
auto maxStrengthForSameLength = 0;

void connectBridge(const int nr_pins, const int accumStrength, const int accumLength)
{
    maxStrength = max(accumStrength, maxStrength);
    maxLength = max(accumLength, maxLength);

    if (accumLength == maxLength) {
        // If we found an exact match with same length, see which one is stronger
        maxStrengthForSameLength = std::max(accumStrength, maxStrengthForSameLength);
    }

    for (auto& comp : components) {
        if (((comp.left_port == nr_pins) || (comp.right_port == nr_pins)) && (comp.connected == false)) {
            int pins = 0;
            comp.connected = true;
			
            if (comp.left_port == nr_pins) {
                pins = comp.right_port;
            }
            else {
                pins = comp.left_port;
            }

            connectBridge(pins, accumStrength + (comp.right_port + comp.left_port), accumLength + 1);
            comp.connected = false;
        }
    }
}

int _tmain(int argc, _TCHAR* argv[])
{
    ifstream infile("input.txt");

    if (infile.is_open()) {
        string line;
        while (getline(infile, line)) {
            istringstream iss(line);
            Component comp;
            char dummy;

            iss >> comp.left_port;
            iss >> dummy;
            iss >> comp.right_port;

            components.push_back(comp);
        }

        infile.close();
    }
    else {
        return 1;
    }

    connectBridge(0, 0, 0);

    cout << "Part one: " << maxStrength;
    cout << "Part two: " << maxStrengthForSameLength;

    cin.ignore();
    return 0;
}
