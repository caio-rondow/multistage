#ifndef SEQLABEL_H
#define SEQLABEL_H

#include "labelStrategy.h"

// Estratégia concreta
class SeqLabel : public LabelStrategy{
public:
    // constru.
    SeqLabel(const Digraph&G);
    // methods
    const string &label() override;
};

#endif