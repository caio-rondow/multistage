#ifndef SMARTLABEL_H
#define SMARTLABEL_H

#include "labelStrategy.h"

// Estratégia concreta
class SmartLabel : public LabelStrategy{
private:
    vector<vector<int>> similar_table_;
    vector<int> multicast_;

public:
    // constru.
    SmartLabel(const Digraph&G);
    // methods
    const string &label() override;
};

#endif