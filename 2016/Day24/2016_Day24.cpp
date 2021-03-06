// 2016_Day24.cpp : Defines the entry point for the console application.
//

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
#include <sstream>
#include <numeric>

using namespace std;

enum NodeType  {OPEN,
                WALL,
                TARGET};

struct Node
{
    int x;
    int y;

    NodeType type;
    int targetNumber = -1;

    bool visited = false;
    int distance = 0;
};

bool myfnx(Node i, Node j) { return i.x < j.x; }
bool myfny(Node i, Node j) { return i.y < j.y; }

bool isValid(map<int, std::map<int, Node> > &mymap, int x, int y, int max_X, int max_Y)
{
    return (x >= 0) && (x <= max_X) && (y >= 0) && (y <= max_Y)
        && !mymap[x][y].visited && (mymap[x][y].type != WALL);
}

int findDistanceBetweenTargets(vector<Node> &grid, Node currentTarget, int findingTarget)
{
    map<int, std::map<int, Node> > mymap;

    Node maxNode = *max_element(grid.begin(), grid.end(), myfnx);
    int max_X = maxNode.x;

    maxNode = *max_element(grid.begin(), grid.end(), myfny);
    int max_Y = maxNode.y;

    for (auto node : grid)
    {
        mymap[node.x][node.y] = node;
    }

    queue<Node> q;

    mymap[currentTarget.x][currentTarget.y].visited = true;

    q.push(mymap[currentTarget.x][currentTarget.y]);

    int min_dist = 0;

    int target = findingTarget;

    while (!q.empty())
    {
        Node node = q.front();
        q.pop();

        int i = node.x; int j = node.y; int dist = node.distance;

        if ((node.type == TARGET) && (node.targetNumber == target))
        {
            min_dist = node.distance;
            break;
        }

        if (isValid(mymap, i - 1, j, max_X, max_Y))
        {
            mymap[i - 1][j].visited = true;
            mymap[i - 1][j].distance = dist + 1;
            q.push(mymap[i - 1][j]);
        }

        if (isValid(mymap, i, j - 1, max_X, max_Y))
        {
            mymap[i][j - 1].visited = true;
            mymap[i][j - 1].distance = dist + 1;
            q.push(mymap[i][j - 1]);
        }

        if (isValid(mymap, i, j + 1, max_X, max_Y))
        {
            mymap[i][j + 1].visited = true;
            mymap[i][j + 1].distance = dist + 1;
            q.push(mymap[i][j + 1]);
        }

        if (isValid(mymap, i + 1, j, max_X, max_Y))
        {
            mymap[i + 1][j].visited = true;
            mymap[i + 1][j].distance = dist + 1;
            q.push(mymap[i + 1][j]);
        }
    }

    return min_dist;
}

void findDistances(vector<Node> &grid, Node currentTarget, int maxTarget, vector<int> &distances)
{
    for (int i = 0; i <= maxTarget; ++i)
    {
        distances.push_back(findDistanceBetweenTargets(grid, currentTarget, i));
    }
}

int findFirst(map<int, vector<int>> &distances, int maxTarget)
{
    vector<int> targets(maxTarget);
    std::iota(targets.begin(), targets.end(), 1);

    int minDistance = INT_MAX;

    do {
        vector<int> targetPath;
        targetPath.push_back(0);
        targetPath.insert(targetPath.end(), targets.begin(), targets.end());

        int distance = 0;

        int prev = targetPath[0];
        for (auto i : targetPath)
        {
            distance += distances[i][prev];
            prev = i;
        }

        minDistance = std::min(minDistance, distance);

    } while (std::next_permutation(targets.begin(), targets.end()));

    return minDistance;
}

int findSecond(map<int, vector<int>> &distances, int maxTarget)
{
    vector<int> targets(maxTarget);
    std::iota(targets.begin(), targets.end(), 1);
    int minDistance = INT_MAX;
    do {
        vector<int> targetPath;
        targetPath.push_back(0);
        targetPath.insert(targetPath.end(), targets.begin(), targets.end());
        targetPath.push_back(0);

        int distance = 0;

        int prev = targetPath[0];
        for (auto i : targetPath)
        {
            distance += distances[i][prev];
            prev = i;
        }

        minDistance = std::min(minDistance, distance);

    } while (std::next_permutation(targets.begin(), targets.end()));

    return minDistance;
}

int main()
{
    ifstream myfile("Input.txt");

    string line;
    vector<Node> grid;

    int x = 0;
    int y = 0;
    int maxTarget = 0;
    
    const auto begin = std::chrono::high_resolution_clock::now();

    if (myfile.is_open()) {
        while (getline(myfile, line))
        {
            istringstream iss(line);
            char point;
            while (iss >> point)
            {
                Node oneNode;
                oneNode.x = x;
                oneNode.y = y;

                if (point == '#') {
                    oneNode.type = WALL;
                } else if (point == '.') {
                    oneNode.type = OPEN;
                }
                else {
                    oneNode.type = TARGET;
                    oneNode.targetNumber = point - '0';
                    maxTarget = max(maxTarget, oneNode.targetNumber);
                }
                grid.push_back(oneNode);
                ++x;
            }
            ++y;
            x = 0;
        }
    }
    else {
        cout << "cannot open file " << endl;
        return 0;
    }

    map<int, vector<int>> distances;

    // Find distances between all targets
    for (int i = 0; i <= maxTarget; i++)
    {
        auto it = find_if(grid.begin(), grid.end(), [&i](const Node & item) {return item.targetNumber == i; });
        findDistances(grid, *it, maxTarget, distances[i]);
    }

    // Now that we have all distances find all permutations and look for the shortest path
    cout << "First part: " << findFirst(distances, maxTarget) << endl;
    cout << "Second part: " << findSecond(distances, maxTarget) << endl;

    const auto end = std::chrono::high_resolution_clock::now();
    std::cout << std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin).count() << " ns for both parts" << std::endl;

    cin.ignore();
    return 0;
}