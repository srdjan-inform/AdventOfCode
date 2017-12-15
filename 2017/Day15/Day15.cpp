// Day15.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <chrono>
#include <iostream>
#include <bitset>

#define MOD 2147483647

int _tmain(int argc, _TCHAR* argv[])
{
  unsigned long first = 722, second = 354;
  auto countFirst = 0;
  auto countSecond = 0;

  const auto begin = std::chrono::high_resolution_clock::now();

  for (auto i = 0; i < 40000000; i++) {
    first *= 16807;
    first %= MOD;
    second *= 48271;
    second %= MOD;

    if ((first & 0xFFFF) == (second & 0xFFFF))
      countFirst++;
  }

  const auto end = std::chrono::high_resolution_clock::now();

  first = 722;
  second = 354;

  for (auto i = 0; i < 5000000; i++) {
    do {
      first *= 16807;
      first %= MOD;
    } while ((first % 4) != 0);
    do {
      second *= 48271;
      second %= MOD;
    } while ((second % 8) != 0);
    if ((first & 0xFFFF) == (second & 0xFFFF))
      countSecond++;
  }

  const auto end2 = std::chrono::high_resolution_clock::now();

  std::cout << "First part: " << countFirst << std::endl;
  std::cout << "First part time : " << std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count() << "ms" << std::endl;

  std::cout << "Second part: " << countSecond << std::endl;
  std::cout << "Second part time : " << std::chrono::duration_cast<std::chrono::milliseconds>(end2 - begin).count() << "ms" << std::endl;

  std::cin.ignore();
  return 0;
}
