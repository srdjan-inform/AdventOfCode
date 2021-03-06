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
#include <sstream>
#include <queue>

using namespace std;
using std::regex;

bool isDigit(string line)
{
    char* p;
    strtol(line.c_str(), &p, 10);
    return *p == 0;
}
int mulCounter = 0;

class Program {

public:
    void Program::setRegister(string regName, long long value)
    {
        registers[regName] = value;
    }

    long long Program::getRegister(string regName)
    {
        return registers[regName];
    }

    void Program::setProgram(vector<string> prog)
    {
        program = prog;
    }

    bool Program::isStuck()
    {
        return stuck;
    }

    bool Program::isDone()
    {
        return done;
    }

    queue<long long>* Program::getQueue()
    {
        return &progQueue;
    }

    void Program::setQueue(Program* child)
    {
        sQueue = child->getQueue();
    }

    void Program::Exec()
    {
        string s;
        istringstream ss(program[programCounter]);

        ss >> s;

        if (s == "set") {
            string reg;
            string value;
            ss >> reg;
            ss >> value;
            if (isDigit(value))
                registers[reg] = stol(value);
            else
                registers[reg] = registers[value];
            programCounter++;
        }
        else if (s == "mul") {
            string reg;
            string value;
            mulCounter++;
            ss >> reg;
            ss >> value;
            if (isDigit(value))
                registers[reg] *= stol(value);
            else
                registers[reg] *= registers[value];
            programCounter++;
        }
        else if (s == "sub") {
            string reg;
            string value;
            ss >> reg;
            ss >> value;
            if (isDigit(value))
                registers[reg] -= stol(value);
            else
                registers[reg] -= registers[value];
            programCounter++;
        }
        else if (s == "jnz") {
            string reg;
            string value;
            ss >> reg;
            ss >> value;
            if (isDigit(reg)) {
                if (stol(reg) != 0) {
                    {
                        if (isDigit(value))
                            programCounter += stol(value);
                        else
                            programCounter += registers[value];
                    }
                }
            }
            else if (registers[reg] != 0) {
                if (isDigit(value))
                    programCounter += stol(value);
                else
                    programCounter += registers[value];
            }
            else
                programCounter++;

            if ((programCounter < 0) || (programCounter >= program.size()))
                done = true;
        }
    }

public:
    long long totalSent = 0;

private:
    unordered_map<string, long long> registers;
    vector<string> program;

    queue<long long> progQueue;
    queue<long long>* sQueue;

    bool stuck = false;
    bool done = false;

    int programCounter = 0;
};

void part2()
{
    auto b = 105700;
    auto c = 122700;
    auto h = 0;

    for (; b <= c; b += 17) {
        auto f = 1;
        auto d = 2;
        do {
            if (b % d == 0)
                f = 0;
            d++;
        } while (d != b);
        if (f == 0)
            h++;
    }

    cout << "H register is: " << h << endl;
}

int _tmain(int argc, _TCHAR* argv[])
{
    ifstream myfile("Input.txt");
    vector<string> prog;

    Program p0;

    if (myfile.is_open()) {

        string line;


        while (getline(myfile, line)) {
            prog.push_back(line);
        }

        p0.setProgram(prog);
    }
    else {
        cout << "cannot open file " << endl;
        return 0;
    }

    while (!(p0.isDone())) {
        p0.Exec();
    }

    cout << "Part1 solution: " << mulCounter << endl;

    part2();

    cin.ignore();
    return 0;
}