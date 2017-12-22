#include "stdafx.h"
#include <vector>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <iostream>
#include <chrono>
#include <bitset>
#include <map>

using namespace std;

typedef enum direction {
  U = 0,
  R,
  D,
  L
} Direction;

struct coordinate {
  int x;
  int y;

  bool operator<(const coordinate& rhs) const
  {
    if (x < rhs.x)
      return true;
    if (x > rhs.x)
      return false;
    //x == coord.x
    if (y < rhs.y)
      return true;
    if (y > rhs.y)
      return false;

    return false;
  }
};

map<coordinate, char> cluster;

int main(int argc, char const* argv[])
{
  ifstream infile("input.txt");
  const int iterations = 10000000;
  vector<string> input;

  if (infile.is_open()) {
    string line;
    while (getline(infile, line)) {
      if (line[line.length() - 1] == '\r')
        line.erase(line.length() - 1);
      input.push_back(line);
    }
    infile.close();
  }
  else {
    return 1;
  }

  const auto begin = std::chrono::high_resolution_clock::now();

  for (int y = 0; y < input.size(); y++) {
    for (int x = 0; x < input[0].length(); x++) {
      if (input[y][x] == '#') {
        coordinate coor;
        coor.x = x - (input[0].length() / 2);
        coor.y = (input.size() / 2) - y;
        cluster[coor] = input[y][x];
      }
    }
  }

  coordinate location;
  location.x = 0;
  location.y = 0;

  typedef enum direction {
    U = 0,
    R,
    D,
    L
  } Direction;
  int bursts = 0;
  Direction dir = U;

  for (int i = 0; i < iterations; i++) {
    auto it = cluster.find(location);
    if (it != cluster.end()) {
      // found an element
      if (cluster[location] == 'W') {
        cluster[location] = '#';
        bursts++;
      }
      else if (cluster[location] == '#') {
        cluster[location] = 'F';
        dir = (Direction)((dir + 1) % 4);
      }
      else if (cluster[location] == 'F') {
        cluster.erase(location);
        dir = (Direction)((dir + 2) % 4);
      }
    }
    else {
      // element not found. it means it's not infected
      cluster[location] = 'W';
      dir = (Direction)((dir + 4 - 1) % 4);
    }

    if (dir == U)
      location.y += 1;
    else if (dir == R)
      location.x += 1;
    else if (dir == D)
      location.y -= 1;
    else
      location.x -= 1;
  }

  cout << bursts << endl;
  const auto end = std::chrono::high_resolution_clock::now();
  std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count() << " ms for both parts" << std::endl;

  return 0;
}