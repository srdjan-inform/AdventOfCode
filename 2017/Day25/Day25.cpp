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
#include <map>

using namespace std;

typedef enum state {
    A = 0,
    B,
    C,
    D,
    E,
    F
} State;

struct machine {
    State curState = A;
    map<int, int> locations;
    int curLocation;
};

int _tmain(int argc, _TCHAR* argv[])
{
    ifstream infile("input.txt");

    machine turing;

    turing.curLocation = 0;
    turing.curState = A;
    turing.locations[0] = 0;

    for (int i = 0; i < 12656374; ++i) {
        switch (turing.curState) {
        case A:
            if (turing.locations[turing.curLocation] == 0) {
                turing.locations[turing.curLocation] = 1;
                turing.curLocation++;
                turing.curState = B;
            }
            else {
                turing.locations[turing.curLocation] = 0;
                turing.curLocation--;
                turing.curState = C;
            }
            break;
        case B:
            if (turing.locations[turing.curLocation] == 0) {
                turing.locations[turing.curLocation] = 1;
                turing.curLocation--;
                turing.curState = A;
            }
            else {
                turing.locations[turing.curLocation] = 1;
                turing.curLocation--;
                turing.curState = D;
            }
            break;
        case C:
            if (turing.locations[turing.curLocation] == 0) {
                turing.locations[turing.curLocation] = 1;
                turing.curLocation++;
                turing.curState = D;
            }
            else {
                turing.locations[turing.curLocation] = 0;
                turing.curLocation++;
                turing.curState = C;
            }
            break;
        case D:
            if (turing.locations[turing.curLocation] == 0) {
                turing.locations[turing.curLocation] = 0;
                turing.curLocation--;
                turing.curState = B;
            }
            else {
                turing.locations[turing.curLocation] = 0;
                turing.curLocation++;
                turing.curState = E;
            }
            break;
        case E:
            if (turing.locations[turing.curLocation] == 0) {
                turing.locations[turing.curLocation] = 1;
                turing.curLocation++;
                turing.curState = C;
            }
            else {
                turing.locations[turing.curLocation] = 1;
                turing.curLocation--;
                turing.curState = F;
            }
            break;
        case F:
            if (turing.locations[turing.curLocation] == 0) {
                turing.locations[turing.curLocation] = 1;
                turing.curLocation--;
                turing.curState = E;
            }
            else {
                turing.locations[turing.curLocation] = 1;
                turing.curLocation++;
                turing.curState = A;
            }
            break;
        }
    }
    int cnt = 0;

    for (auto element : turing.locations) {
        if (element.second == 1) {
            cnt++;
        }
    }

    cout << "Nr Elements " << cnt << endl;

    cin.ignore();

    return 0;
}
