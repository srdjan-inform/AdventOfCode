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
#include <map>
#include <queue>
#include <iomanip>

using namespace std;
using std::regex;

struct Node
{
	int x;
	int y;

	int size;
	int used;
	int avail;
	int use_percent;
	int distance = 0;
	bool marked = false;

	bool target = false;
};

bool myfnx(Node i, Node j) { return i.x < j.x; }
bool myfny(Node i, Node j) { return i.y < j.y; }

bool isValid(map<int, std::map<int, Node> > &mymap, int x, int y, int max_X, int max_Y)
{
	return (x >= 0) && (x <= max_X) && (y >= 0) && (y <= max_Y)
		&& !mymap[x][y].marked && (mymap[x][y].size < 200);
}

void partTwo(vector<Node> &grid)
{
	map<int, std::map<int, Node> > mymap;

	Node maxNode = *max_element(grid.begin(), grid.end(), myfnx);
	int max_X = maxNode.x;

	maxNode = *max_element(grid.begin(), grid.end(), myfny);
	int max_Y = maxNode.y;

	for(auto node : grid)
	{
		mymap[node.x][node.y] = node;
	}

	mymap[max_X][0].target = true;
	
	int emptyX, emptyY;

	for (int i = 0; i <= max_Y; i++)
	{
		for (int j = 0; j <= max_X; j++)
		{
			if (mymap[j][i].used == 0)
			{
				emptyX = j;
				emptyY = i;
			}
		}
	}

	// Output the map on screen
	for (int i = 0; i <= max_Y; i++)
	{
		for (int j = 0; j <= max_X; j++)
		{
		if (i == 0 && j == 0)
		{
			cout << "(.)";
		}
		else if (mymap[j][i].used == 0)
		{
			cout << " _ ";
		}
		else if (mymap[j][i].target)
		{
			cout << " G ";
		}
		else if (mymap[j][i].size > 200)
		{
			cout << " # ";
		}
		else
		{
			cout << " . ";
		}
	}
	cout << "\n";
	}

	// Stupid implementation of BFS to find the shortest path from empty node to the target node
	queue<Node> q;

	mymap[emptyX][emptyY].marked = true;

	q.push(mymap[emptyX][emptyY]);

	int min_dist = INT_MAX;

	while (!q.empty())
	{
		Node node = q.front();
		q.pop();

		int i = node.x; int j = node.y; int dist = node.distance;

		if (node.target)
		{
			min_dist = node.distance;
			break;
		}

		if (isValid(mymap, i - 1, j, max_X, max_Y))
		{
			mymap[i - 1][j].marked = true;
			mymap[i - 1][j].distance = dist + 1;
			q.push(mymap[i - 1][j]);
		}

		if (isValid(mymap, i, j-1, max_X, max_Y))
		{
			mymap[i][j-1].marked = true;
			mymap[i][j-1].distance = dist + 1;
			q.push(mymap[i][j-1]);
		}

		if (isValid(mymap, i, j + 1, max_X, max_Y))
		{
			mymap[i][j+1].marked = true;
			mymap[i][j+1].distance = dist + 1;
			q.push(mymap[i][j + 1]);
		}

		if (isValid(mymap, i + 1, j, max_X, max_Y))
		{
			mymap[i + 1][j].marked = true;
			mymap[i + 1][j].distance = dist + 1;
			q.push(mymap[i + 1][j]);
		}
	}

	cout << "Number of steps to get empty space to the target is " << min_dist << endl;

	cout << "Total number of steps is " << (max_X - 1) * 5 + min_dist << endl;
	
	cout << endl;
}

int processPartOne(vector<Node> &grid)
{
	auto viable = 0;

	for (int i = 0; i < grid.size(); ++i)
	{
		if (grid[i].used != 0)
		{
			for (int j = 0; j < grid.size(); ++j)
			{
				if ((j != i) && (grid[i].used < grid[j].avail))
				{
					viable++;
				}
			}
		}
	}

	return viable;
}

int _tmain(int argc, _TCHAR* argv[])
{
	ifstream myfile("Input.txt");

	string line;

	vector<Node> grid;
	const auto begin = std::chrono::high_resolution_clock::now();
	if (myfile.is_open()) {

		const regex base_regex("\\/dev\\/grid\\/node-x(\\d+)-y(\\d+) *(\\d+)T *(\\d+)T *(\\d+)T *(\\d+)%");
		smatch pieces_match;
		
		while (getline(myfile, line))
		{
			if (!line.empty())
			{
				if (regex_match(line, pieces_match, base_regex)) {

					Node oneNode;

					oneNode.x = stoi(pieces_match[1]);
					oneNode.y = stoi(pieces_match[2]);
					oneNode.size = stoi(pieces_match[3]);
					oneNode.used = stoi(pieces_match[4]);
					oneNode.avail = stoi(pieces_match[5]);
					oneNode.use_percent = stoi(pieces_match[6]);

					grid.push_back(oneNode);
				}
			}
		}
	}
	else {
		cout << "cannot open file " << endl;
		return 0;
	}
	
	cout << "Number of pairs " << processPartOne(grid) << endl;
	partTwo(grid);
	const auto end = std::chrono::high_resolution_clock::now();
	std::cout << std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin).count() << " ns for both parts" << std::endl;

	cout << endl;
	cin.ignore();

	return 0;
}