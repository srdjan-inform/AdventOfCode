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

#define HASH_LENGTH (256)

std::vector<int> run_hash(const std::vector<int> &inputs, const int &rounds)
{
    std::vector<int> ringBuffer(HASH_LENGTH);

    std::iota(ringBuffer.begin(), ringBuffer.end(), 0);

    auto skip = 0;
    auto index = 0;

    for (auto round = 0; round < rounds; ++round)
    {
        for (auto &input : inputs)
        {
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
    std::ifstream myFile("input.txt");
    std::vector<int> inputs;

    std::string line;
    std::getline(myFile, line);
    std::istringstream ss(line);

    const auto begin = std::chrono::high_resolution_clock::now();

    while (ss)
    {
        std::string s;
        if (!std::getline(ss, s, ',')) break;
        inputs.push_back(stoi(s));
    }

    auto result = run_hash(inputs, 1);
    std::cout << "Part 1: " << result[0] * result[1] << "\n";

    // Clear the vector and fill it up with new values
    inputs.clear();

    std::istringstream ss2(line);
    char ch;

    while (ss2.get(ch))
    {
        // This will convert each char into its ASCII value
        inputs.push_back(ch);
    }

    // Append the special sequence
    for (auto &c : { 17, 31, 73, 47, 23 })
    {
        inputs.push_back(c);
    }

    // Run the has 64 times
    auto ring = run_hash(inputs, 64);

    // Calculate the XOR on each 16 elements
    std::vector<int> dense_hash(ring.size() / 16);

    for (auto i = 0; i < ring.size(); i += 16)
    {
        for (size_t j = 0; j < 16; ++j)
        {
            dense_hash[i / 16] ^= ring[i + j];
        }
    }
    std::cout << "Part 2: ";

    for (auto &hex : dense_hash)
    {
        std::cout << std::setw(2) << std::setfill('0') << std::hex << (int)hex;
    }

    std::cout << "\n";

    const auto end = std::chrono::high_resolution_clock::now();
    std::cout << std::setw(0) << std::dec << std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin).count() << " ns for both parts" << std::endl;

    
    std::cin.ignore();

}