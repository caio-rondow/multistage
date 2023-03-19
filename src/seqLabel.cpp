#include "../include/seqLabel.h"
#include "../include/omega.h"

SeqLabel::SeqLabel(const Digraph&G):LabelStrategy(G){}

const string &SeqLabel::label(){
    // code sequential strat. here...
    int labels[256];            // rotulos disponiveis
    int pos=0;                  // cursor do rotulo
    
    // Init arrays
    for(int i=0; i<nv; i++)
        visited_[i]=-1;
    for(int i=0; i<256; i++)
        labels[i]=i;

    stringstream ss;
    for(auto &e:edges){

        int u = e.first;
        int v = e.second;
        int name;

        // se u não foi visitado
        if(visited_[u]==-1){
            name = labels[pos++];  // pega label valida e marca como usada
            label_[u] = name;      // rotula u
            visited_[u]=0;         // marca como visitado
        }
        
        // se v não foi visitado
        if(visited_[v]==-1){
            name = labels[pos++];
            label_[v]=name;
            visited_[v]=1;

        } else{
            visited_[v]++;
            if(visited_[v]>1){
                name = labels[pos++];
                label_[v]=name;
            } 
        }
        ss << label_[u] << " " << label_[v] << "\n";
    }


    file = ss.str();
    
    return file;
}