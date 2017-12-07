#include "stdafx.h"
#include <fstream>
#include <vector>
#include <string>
#include <iostream>
#include <chrono>
#include <iterator>
#include <sstream>
#include <functional>
#include <algorithm>

using namespace std;

struct Program
{
  string name;
  int weight;

  std::vector<std::string> children;
  std::vector<int> weights;
  
  bool operator<(const Program &p) const
  {
    return name < p.name;
  }
};

Program parent(const std::string &child, const std::vector<Program> &stack)
{
  for (auto &t : stack)
  {
    auto c = std::find(t.children.begin(), t.children.end(), child);
    if (c != t.children.end())
      return parent(t.name, stack);
  }
  for (auto &t : stack)
  {
    if (t.name == child)
      return t;
  }
}

int calc_cumulative_weight(Program &p, std::vector<Program> &stack)
{
  // Create a tree of weights (each node contains the sum of weights of it's children)
  for (auto &c : p.children)
  {
    for (auto &t : stack)
    {
      if (t.name == c)
      {
        p.weights.push_back(calc_cumulative_weight(t, stack));
        break;
      }
    }
  }
  
  int result = 0;
  if (!p.weights.empty())
  {
    // Let's say that first element has the nominal value
    int balanced_weight(*p.weights.begin());

    for (auto &w : p.weights)
    {
      if (balanced_weight != w)
      {       
        // This tree is unbalanced. Find which element is unbalanced
        cout << "Program " << p.name << " is unbalanced" << endl;

        cout << "Its children are " << endl;

        for (auto &c : p.children)
        {
          std::cout << c << "\n";        
        }

        for (auto &ww : p.weights)
        {
          std::cout << ww << "\n";
        }        

        cout << endl;
      }
      result += w;
    }
  }

  result += p.weight;
  return result;
}

int _tmain(int argc, _TCHAR* argv[])
{
  ifstream myfile("Input.txt");

  string line;
  std::vector<Program> stack;

  if (myfile.is_open()) {
    while (getline(myfile, line))
    {
      if (!line.empty())
      {
        vector<string> words;
        istringstream iss(line);

        Program prog;
        char c;
        iss >> prog.name;
        iss >> c;
        iss >> prog.weight;

        const auto crtka(line.find('-'));
        if (crtka != std::string::npos)
        {
          const auto elements(line.substr(crtka + 2));

          istringstream elementsStream(elements);
          while (elementsStream.good())
          {
            string substr;
            getline(elementsStream, substr, ',');
            // Fuck C++
            substr.erase(substr.begin(), std::find_if(substr.begin(), substr.end(), std::bind1st(std::not_equal_to<char>(), ' '))); 
            prog.children.push_back(substr); 
          }
        }

        stack.push_back(prog);
      }
    }
  }
  else {
    cout << "cannot open file " << endl;
    return 0;
  }

  const auto begin = std::chrono::high_resolution_clock::now();
  auto find_parent(parent(stack.begin()->name, stack));

  const auto end = std::chrono::high_resolution_clock::now();
  std::cout << std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin).count() << " ns for part one" << std::endl;

  std::cout << "Parent program is: " << find_parent.name << "\n";

  calc_cumulative_weight(find_parent, stack);

  const auto end2 = std::chrono::high_resolution_clock::now();
  std::cout << std::chrono::duration_cast<std::chrono::nanoseconds>(end2 - begin).count() << " ns for part two" << std::endl;

  cout << endl;

  cin.ignore();


  return 0;
}

