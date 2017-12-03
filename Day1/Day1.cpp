#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

int processPartOne(vector<int> myVector)
{
  auto sum = 0;

  myVector.push_back(myVector[0]);

  for (auto i = 0; i < myVector.size()-1; i++)
  {
    if (myVector[i] == myVector[i + 1])
    {
      sum += myVector[i];
    }
  }

  return sum;
}

int processPartTwo(vector<int> myVector)
{
  auto sum = 0;
  const int step = myVector.size() / 2;

  for (auto i = 0; i < myVector.size(); i++)
  {
    if (myVector[i] == myVector[(i + step) % myVector.size()])
    {
      sum += myVector[i];
    }
  }

  return sum;
}

int _tmain(int argc, _TCHAR* argv[])
{
	char my_char;

	vector<int> my_vector;

	std::ifstream ifile("Input1_1.txt");

	if (ifile.is_open())
	{
		while (ifile >> my_char)
		{
		  my_vector.push_back(my_char - '0');
		}
	}

	cout << "First part is: " << processPartOne(my_vector) << endl;
	cout << "Second part is: " << processPartTwo(my_vector) << endl;

	return 0;
}