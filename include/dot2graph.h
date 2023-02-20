#ifndef DOT2GRAPH_H
#define DOT2GRAPH_H

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <regex>
#include <map>

#include "digraph.h"

using namespace std;

typedef vector<vector<int>> adjacency_list;

class Dot2Graph{
public:
    // construc./destruc.
    // Dot2Graph();
    // ~Dot2Graph();

    // method
    const Digraph read_dot(const string &filename, int copy=1) const;
};

#endif