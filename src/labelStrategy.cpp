#include "../include/labelStrategy.h"

LabelStrategy::LabelStrategy(const Digraph&G): 
    G_(G), edges(G_.edges()), 
    ne(G_.number_of_edges()), 
    nv(G_.number_of_nodes()){
        
    visited_ = new int[nv];
    label_   = new int[nv];
}

LabelStrategy::~LabelStrategy(){
    delete[] visited_;
    delete[] label_;
}