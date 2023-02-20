#include "../include/randLabel.h"

RandLabel::RandLabel(const Digraph&G):LabelStrategy(G){}

const string &RandLabel::label(){

    int labels[256];            // rotulos disponiveis
    int pos=0;                  // cursor do rotulo

    // Init arrays
    for(int i=0; i<nv; i++)
        visited_[i]=-1;
    for(int i=0; i<256; i++)
        labels[i]=i;

    // fator aleatorio
    random_shuffle(labels, labels+256);

    stringstream ss;
    // cout << "digraph fir16{\n";
    for(auto &e:edges){
        
        int u = e.first;
        int v = e.second;
        int name;

        // se u não foi visitado
        if(visited_[u]==-1){
            name = labels[pos++];  // pega um rotulo
            label_[u] = name;      // rotula u
            visited_[u]=0;         // visita u
        }
        
        // se v não foi visitado
        if(visited_[v]==-1){
            name = labels[pos++];   // pega um rotulo
            label_[v]=name;         // rotula v
            visited_[v]=1;          // visita v

        } else{
            /* conta quantas vezes v foi visitado */
            visited_[v]++;
            /* se for mais de uma vez, troque de rotulo */
            if(visited_[v]>1){
                name = labels[pos++]; 
                label_[v]=name;
            } 
        }
        ss << label_[u] << " " << label_[v] << "\n";
        // cout << "\t" << u << "->" << v << " [label_=\"("<< label_[u] << ", " << label_[v] << ")\"]\n";
    }
    // cout << "}\n";
    file = ss.str();

    return file;
}