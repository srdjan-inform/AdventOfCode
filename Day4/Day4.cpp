// Day4.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <fstream>
#include <string>
#include <iostream>
#include <sstream>
#include <map>

using namespace std;

int _tmain(int argc, _TCHAR* argv[])
{
  ifstream myfile("Input.txt");

  string word;
  string line;

  int totalPassphrase1 = 0;
  int totalPassphrase2 = 0;

  if (myfile.is_open()) {

    while (getline(myfile, line))
    {
      map<string, int> wordsMap;
      map<string, int> sortedMap;

      istringstream iss(line);
      int totalWords = 0;
	  
      while (iss >> word)
      {
        wordsMap[word]++;
        std::sort(word.begin(), word.end());
        sortedMap[word]++;
        totalWords++;
      }
      
      if (wordsMap.size() == totalWords)
      {
        totalPassphrase1++;
      }

      if ((wordsMap.size() == sortedMap.size()) && (wordsMap.size() == totalWords))
      {
        totalPassphrase2++;
      }

    }
  }
  else {
    cout << "cannot open file " << endl;
    return 0;
  }

  cout << "Number of valid passphrases from part1: " << totalPassphrase1 << endl;
  cout << "Number of valid passphrases from part2: " << totalPassphrase2 << endl;


  return 0;
}

