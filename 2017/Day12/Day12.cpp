#include "stdafx.h"
#include <fstream>
#include <vector>
#include <string>
#include <iostream>
#include <chrono>
#include <functional>
#include <algorithm>
#include <regex>
#include <map>

using namespace std;
using std::regex;

struct Node {
    int name;
    bool visited = false;
    int groupNr = 0;

    bool operator<(const Node& p) const
    {
        return name < p.name;
    }

    std::vector<int> children;
};

void visit_nodes(map<int, Node>& pipeline, vector<int>& nodes, const int group_nr)
{
    for (auto node : nodes) {
        if (!pipeline[node].visited) {
            pipeline[node].visited = true;
            pipeline[node].groupNr = group_nr;
            visit_nodes(pipeline, pipeline[node].children, group_nr);
        }
    }
}

int _tmain(int argc, _TCHAR* argv[])
{

    ifstream myfile("Input.txt");

    string line;
    map<int, Node> pipeline;

    if (myfile.is_open()) {

        const regex base_regex("(\\d+) <-> ([0-9, ]+)");
        const regex children_regex("(, )");

        smatch pieces_match;

        while (getline(myfile, line)) {
            if (!line.empty()) {
                if (regex_match(line, pieces_match, base_regex)) {
                    Node node;

                    node.name = stoi(pieces_match[1]);

                    if (pieces_match[2].matched) {
                        string list = pieces_match[2];

                        for_each(std::sregex_token_iterator(list.begin(), list.end(), children_regex, -1), std::sregex_token_iterator(),
                            [&node](const string& ch) { node.children.push_back(stoi(ch)); });
                    }
                    pipeline[node.name] = node;
                }
            }
        }
    }
    else {
        cout << "cannot open file " << endl;
        return 0;
    }

    const auto begin = std::chrono::high_resolution_clock::now();

    auto groupNr = 0;

    for (auto i = 0; i < pipeline.size(); i++) {
        if (pipeline[i].groupNr == 0) {
            groupNr++;
            pipeline[i].visited = true;
            pipeline[i].groupNr = groupNr;
            visit_nodes(pipeline, pipeline[i].children, groupNr);
        }
    }

    auto number = count_if(pipeline.begin(), pipeline.end(), [](pair<int, Node> it) { return (it.second.groupNr == 1); });

    const auto end2 = std::chrono::high_resolution_clock::now();

    cout << "First part: " << number << endl;
    cout << "Second part: " << groupNr << endl;

    std::cout << std::chrono::duration_cast<std::chrono::nanoseconds>(end2 - begin).count() << " ns for both parts" << std::endl;

    cin.ignore();

    return 0;
}
