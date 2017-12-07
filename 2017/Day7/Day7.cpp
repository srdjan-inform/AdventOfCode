#include "stdafx.h"
#include <fstream>
#include <vector>
#include <string>
#include <iostream>
#include <chrono>
#include <iterator>
#include <functional>
#include <algorithm>
#include <regex>

using namespace std;
using std::regex;

struct Program
{
	std::string name;
	int weight;

	bool operator<(const Program &p) const
	{
		return name < p.name;
	}

	std::vector<std::string> children;
	std::vector<int> weights;
};

Program parent(const std::string &child, const std::vector<Program> &tower)
{
	for (auto &t : tower)
	{
		auto c = std::find(t.children.begin(), t.children.end(), child);
		if (c != t.children.end())
			return parent(t.name, tower);
	}
	for (auto &t : tower)
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
		
		const regex base_regex("([a-z]+) \\((\\d+)\\)( -> ([a-z, ]+))?");
		const regex children_regex("(, )");

		smatch pieces_match;

		while (getline(myfile, line))
		{
			if (!line.empty())
			{           
				if (regex_match(line, pieces_match, base_regex)) {
					// The first sub_match is the whole string; the next
					// sub_match is the first parenthesized expression.
					Program prog;
					
					prog.name = pieces_match[1];
					prog.weight = stoi(pieces_match[2]);

					if (pieces_match[3].matched)
					{           
						string list = pieces_match[4];

						copy(std::sregex_token_iterator(list.begin(), list.end(), children_regex, -1),
							std::sregex_token_iterator(),
							back_inserter(prog.children));
					}
					stack.push_back(prog);
				}
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