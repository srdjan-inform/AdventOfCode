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
#include <bitset>

#define HASH_LENGTH (256)

bool markNeighbours(std::vector<std::string>& grid, int row, int col)
{
  if (col < 0 || row < 0 || row >= grid.size() || col >= grid[0].length())
    return false;

  if (grid[row][col] == '1') {
    grid[row][col] = '.';
    markNeighbours(grid, row + 1, col);
    markNeighbours(grid, row - 1, col);
    markNeighbours(grid, row, col + 1);
    markNeighbours(grid, row, col - 1);
    return true;
  }

  return false;
}

int findGroups(std::vector<std::string>& grid)
{
  int groups = 0;

  for (int i = 0; i < grid.size(); i++) {
    for (int j = 0; j < grid[i].length(); j++) {
      if (markNeighbours(grid, i, j))
        groups++;
    }
  }

  return groups;
}

std::vector<int> run_hash(const std::vector<int>& inputs, const int& rounds)
{
  std::vector<int> ringBuffer(HASH_LENGTH);

  std::iota(ringBuffer.begin(), ringBuffer.end(), 0);

  auto skip = 0;
  auto index = 0;

  for (auto round = 0; round < rounds; ++round) {
    for (auto& input : inputs) {
      int first = index;
      int end = first + input - 1;

      while (first < end)
        std::swap(ringBuffer[first++ % ringBuffer.size()], ringBuffer[end-- % ringBuffer.size()]);

      index = (index + input + skip++) % ringBuffer.size();
    }
  }

  return ringBuffer;
}

int main()
{
  std::string input = "jzgqcdpd";
  std::vector<std::string> grid;

  std::vector<int> inputs;
  int countOnes = 0;

  for (int i = 0; i < 128; i++) {
    std::string binary;
    std::string sequence = input + "-" + std::to_string(i);
    inputs.clear();

    copy(sequence.begin(), sequence.end(), std::back_inserter(inputs));
    inputs.insert(inputs.end(), { 17, 31, 73, 47, 23 });

    // Run the hash 64 times
    auto ring = run_hash(inputs, 64);

    // Calculate the XOR on each 16 elements
    std::vector<int> dense_hash(ring.size() / 16);

    for (auto i = 0; i < ring.size(); i += 16) {
      for (size_t j = 0; j < 16; ++j) {
        dense_hash[i / 16] ^= ring[i + j];
      }
    }

    for (auto& hex : dense_hash) {
      std::bitset<8> bits(hex);
      countOnes += bits.count();
      binary += bits.to_string();
    }

    grid.push_back(binary);
  }

  std::cout << "Number of ones: " << countOnes << std::endl;
  std::cout << "Part two: " << findGroups(grid) << std::endl;

  std::cin.ignore();

  return 0;
}