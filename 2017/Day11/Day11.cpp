#include "stdafx.h"
#include <vector>
#include <iostream>
#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>


int _tmain(int argc, _TCHAR* argv[])
{
  std::ifstream myFile("input.txt");

  std::vector<std::string> inputs;

  std::string line;
  std::getline(myFile, line);
  std::istringstream ss(line);
  
  int x = 0, y = 0;
  int maxDist = 0;;

  while (ss)
  {
    std::string s;
    if (!std::getline(ss, s, ',')) break;
    inputs.push_back(s);
  }

  for (auto curMove : inputs)
  {
    if (curMove == "n")
    {
      --y;
    } else if(curMove == "ne"){
      ++x;
      --y;
    }
    else if(curMove == "se") {
      ++x;
    }
    else if (curMove == "s") {
      ++y;
    }
    else if(curMove == "sw") {
      --x;
      ++y;
    } 
    else if (curMove == "nw") {
      --x;
    }

    int dist = abs((0 - x) + abs(0 + 0 - x - y) + abs(0 - y)) / 2;

    maxDist = std::max(maxDist, dist);
  }
  
  std::cout << "Distance is: ";

  std::cout <<( abs(0 - x) + abs(0 + 0 - x - y) + abs(0 - y)) / 2 << std::endl;

  std::cout << "Maximal distance is: ";
  std::cout << maxDist << std::endl;

  std::cin.ignore();

  return 0;
}

