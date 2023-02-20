#include "../include/label.h"

Label::Label(const Digraph&G, int type){
    /* set strategy */
    switch(type){
        case 0: 
            strategy_ = new SeqLabel(G);
        break;

        case 2: 
            strategy_ = new SmartLabel(G);
        break;
        
        default:
            strategy_ = new RandLabel(G);
        break;
    }
}

Label::~Label(){ delete strategy_; }

void Label::set_strategy(LabelStrategy* strategy){ strategy_ = strategy; }

const string &Label::label(){ return strategy_->label(); }