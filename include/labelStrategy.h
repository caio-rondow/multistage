#ifndef LABELSTRATEGY_H
#define LABELSTRATEGY_H

#include "digraph.h"

#include <iostream>
#include <sstream>
#include <random>
#include <string>
#include <map>

// Interface da estratégia
class LabelStrategy{
protected:
    /* set attr. for all strats. */
    const Digraph G_;
    string file;
    vector<pair<int,int>> edges;
    int ne, nv;
    int *visited_;
    int *label_;

public:
    // constru.
    LabelStrategy(const Digraph&G);
    virtual ~LabelStrategy();

    /* label a graph */
    virtual const string &label() = 0;
};

#endif