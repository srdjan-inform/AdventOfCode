#include "stdafx.h"
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <iostream>
#include <sstream>
#include <set>

using namespace std;


int _tmain(int argc, _TCHAR* argv[])
{
  ifstream myfile("Input.txt");

  string word;
  string line;

  auto totalPassphrase1 = 0;
  auto totalPassphrase2 = 0;

  if (myfile.is_open()) {

    while (getline(myfile, line))
    {
      vector<string> words;
      istringstream iss(line);

      copy(istream_iterator<string>(iss),
        istream_iterator<string>(),
        back_inserter(words));


      if (std::set<std::string>(words.begin(), words.end()).size() == words.size())
      {
        totalPassphrase1++;
        std::for_each(words.begin(), words.end(), [](std::string &x){std::sort(x.begin(), x.end()); });

        if (std::set<std::string>(words.begin(), words.end()).size() == words.size()) totalPassphrase2++;
      
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