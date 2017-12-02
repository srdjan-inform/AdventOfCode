#include "stdafx.h"
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <iostream>
#include <sstream>

using namespace std;

int processPartOne(vector<string> spreadsheet_lines)
{
  auto checksum = 0;

  for (const auto oneline : spreadsheet_lines)
  {
    istringstream iss(oneline);
    vector<int> numbers;

    copy(istream_iterator<int>(iss),
      istream_iterator<int>(),
      back_inserter(numbers));

    const auto result = minmax_element(numbers.begin(), numbers.end());

    const auto difference = *result.second - *result.first;

    checksum += difference;
  }

  return checksum;
}

int processPartTwo(vector<string> spreadsheet_lines)
{
  auto checksum = 0;

  for (const auto oneline : spreadsheet_lines)
  {
    istringstream iss(oneline);
    vector<int> numbers;

    copy(istream_iterator<int>(iss),
      istream_iterator<int>(),
      back_inserter(numbers));


  for (auto i = 0; i < numbers.size(); i++)
    for (auto j = 0; j < numbers.size(); j++)
    {
      if (i != j)
      {
        if (numbers[i] % numbers[j] == 0)
        {
          checksum += (numbers[i] / numbers[j]);
          break;
        }
      }
    }
  }
  return checksum;
}

int _tmain(int argc, _TCHAR* argv[])
{
	vector<string> spreadsheet_lines;


	ifstream myfile("Input.txt");

	if (myfile.is_open()) {

		string str;
		while (getline(myfile, str))
		{
			spreadsheet_lines.push_back(str);
		}
	}
	else {
		cout << "cannot open file " << endl;
		return 0;
	}

  cout << "First part is: " << processPartOne(spreadsheet_lines) << endl;
  cout << "Second part is: " << processPartTwo(spreadsheet_lines) << endl;

	return 0;
}

