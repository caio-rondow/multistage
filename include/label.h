#ifndef LABEL_H
#define LABEL_H

#include "randLabel.h"
#include "smartLabel.h"
#include "seqLabel.h"
#include "localLabel.h"

using namespace std;

// Cliente (Contexto)
class Label{
private:
    LabelStrategy* strategy_;

public:
    // constru./destru.
    Label(const Digraph&G, int type=1);
    ~Label();
    // methods
    const string &label();
    void set_strategy(LabelStrategy* strategy);
};

#endif