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

    if (s == "snd") {
      string reg;
      ss >> reg;
      sQueue->push(registers[reg]);
      programCounter++;
      totalSent++;
    }
    else if (s == "set") {
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
    else if (s == "add") {
      string reg;
      string value;
      ss >> reg;
      ss >> value;
      if (isDigit(value))
        registers[reg] += stol(value);
      else
        registers[reg] += registers[value];
      programCounter++;
    }
    else if (s == "mul") {
      string reg;
      string value;
      ss >> reg;
      ss >> value;
      if (isDigit(value))
        registers[reg] *= stol(value);
      else
        registers[reg] *= registers[value];
      programCounter++;
    }
    else if (s == "mod") {
      string reg;
      string value;
      ss >> reg;
      ss >> value;
      if (isDigit(value))
        registers[reg] %= stol(value);
      else
        registers[reg] %= registers[value];
      programCounter++;
    }
    else if (s == "rcv") {
      string reg;
      ss >> reg;

      if (!progQueue.empty()) {
        registers[reg] = progQueue.front();
        progQueue.pop();
        programCounter++;
        stuck = false;
      }
      else
        this->stuck = true;
    }
    else if (s == "jgz") {
      string reg;
      string value;
      ss >> reg;
      ss >> value;
      if (isDigit(reg)) {
        if (stol(reg) > 0) {
          {
            if (isDigit(value))
              programCounter += stol(value);
            else
              programCounter += registers[value];
          }
        }
      }
      else if (registers[reg] > 0) {
        if (isDigit(value))
          programCounter += stol(value);
        else
          programCounter += registers[value];
      }
      else
        programCounter++;

      if ((programCounter < 0) || (programCounter > program.size()))
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

int _tmain(int argc, _TCHAR* argv[])
{
  ifstream myfile("Input.txt");

  Program p0;
  Program p1;

  p0.setQueue(&p1);
  p1.setQueue(&p0);

  p1.setRegister("p", 1);

  if (myfile.is_open()) {

    string line;

    vector<string> prog;

    while (getline(myfile, line)) {
      prog.push_back(line);
    }

    p0.setProgram(prog);
    p1.setProgram(prog);
  }
  else {
    cout << "cannot open file " << endl;
    return 0;
  }

  while (!(p0.isStuck() && p1.isStuck())) {
    p0.Exec();
    p1.Exec();
  }

  cout << "Second Part " << p1.totalSent;

  return 0;
}
