#ifndef RANDLABEL_H
#define RANDLABEL_H

#include "labelStrategy.h"

// Estratégia concreta
class RandLabel : public LabelStrategy{
public:
    // constru.
    RandLabel(const Digraph&G);
    // methods
    const string &label() override;
};

#endif