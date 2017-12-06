// Day6.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <fstream>
#include <vector>
#include <iostream>
#include <chrono>
#include <iterator>
#include <algorithm>
#include <chrono>
#include <map>
using namespace std;

int _tmain(int argc, _TCHAR* argv[])
{
  ifstream myfile("Input.txt");

  auto step_counter = 0;

  if (myfile.is_open()) {

    //vector<vector<int>> seen;

    std::map<std::vector<int>, int> seen;

    vector<int> memory{ istream_iterator<int>(myfile), istream_iterator<int>() };

    const auto begin = std::chrono::high_resolution_clock::now();
    
    seen.emplace(memory, step_counter);

    bool solved = false;
    
    while (!solved)
    {
      step_counter++;

      auto max = std::max_element(memory.begin(), memory.end());
      int maxValue = *max;
      *max = 0;

      for (int i = maxValue; i--; ++*max)
      {        
        if (++max == memory.end())
          max = memory.begin();
      }

      if (!seen.emplace(memory, step_counter).second)
      {
        solved = true;
        const auto end = std::chrono::high_resolution_clock::now();
        std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count() << " ms for both parts" << std::endl;
        
        cout << "Number of cycles (first part) is " << seen.size() << endl;
        cout << "Identical iteration seen after (second part)" << seen.size() - seen[memory] << endl;
      }
    }
  }
  else {
    cout << "cannot open file " << endl;
    return 0;
  }

  cin.ignore();
  return 0;
}

