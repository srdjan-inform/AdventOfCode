#include "stdafx.h"
#include <fstream>
#include <vector>
#include <string>
#include <iostream>
#include <chrono>

using namespace std;

int partOne(vector<int> commands)
{
  const auto begin = std::chrono::high_resolution_clock::now();

  auto current = 0;
  auto next = 0;
  auto step_counter = 0;

  while ((current >= 0) && (current < commands.size()))
  {
    step_counter++;

    next = current + commands[current];

    commands[current] ++;

    current = next;
  }
  const auto end = std::chrono::high_resolution_clock::now();
  std::cout << std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin).count() << " ns for Part One" << std::endl;

  return step_counter++;
}

int partTwo(vector<int> commands)
{
  const auto begin = std::chrono::high_resolution_clock::now();

  auto current = 0;
  auto next = 0;;
  auto step_counter = 0;

  while ((current >= 0) && (current < commands.size()))
  {
    step_counter++;

    next = current + commands[current];

    commands[current] += (commands[current] >= 3 ? -1 : 1);

    current = next;
  }

  const auto end = std::chrono::high_resolution_clock::now();
  std::cout << std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin).count() << " ns for Part Two" << std::endl;

  return step_counter++;
}

int _tmain(int argc, _TCHAR* argv[])
{
	ifstream myfile("Input.txt");
 
  if (myfile.is_open()) {
    const vector<int> commands{ istream_iterator<int>(myfile), istream_iterator<int>() };

    cout << "Total number of steps PartOne: " << partOne(commands) << endl;
    cout << "Total number of steps PartTwo: " << partTwo(commands) << endl;
    
  }
  else {
    cout << "cannot open file " << endl;
    return 0;
  }

  cin.ignore();
	return 0;
}

