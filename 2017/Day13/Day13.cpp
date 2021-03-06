#include "stdafx.h"
#include <vector>
#include <numeric>
#include <iostream>
#include <iomanip>
#include <iterator>
#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>
#include <chrono>
#include <map>
using namespace std;

int main()
{
    map<int, int> firewall;

    ifstream myfile("Input.txt");

    std::string line;
    while (getline(myfile, line)) {
        istringstream iss(line);
        int layer, depth;
        string _;

        iss >> layer >> _ >> depth;
        firewall[layer] = depth;
    }

    const auto begin = std::chrono::high_resolution_clock::now();

    int part1 = 0;

    for (auto cur : firewall) {
        if (cur.first % (2 * cur.second - 2) == 0) {
            part1 += cur.first * cur.second;
        }
    }

    int delay = 0;

    while (true) {
        bool test = true;
        for (auto cur : firewall) {
            if ((cur.first + delay) % (2 * (cur.second - 1)) == 0) {
                test = false;
                break;
            }
        }
        if (test) {
            break;
        }
        delay++;
    }

    const auto end = std::chrono::high_resolution_clock::now();

    cout << part1 << endl;
    cout << delay << endl;

    std::cout << std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin).count() << " ns for both parts" << std::endl;

    return 0;
}
