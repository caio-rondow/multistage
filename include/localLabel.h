#ifndef LOCALLABEL_H
#define LOCALLABEL_H

#include "labelStrategy.h"

// Estratégia concreta
class LocalLabel : public LabelStrategy{
public:
    // constru.
    LocalLabel(const Digraph&G);
    // methods
    const string &label() override;
};

#endif