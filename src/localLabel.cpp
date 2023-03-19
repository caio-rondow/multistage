#include "../include/localLabel.h"
#include "../include/omega.h"

LocalLabel::LocalLabel(const Digraph&G):LabelStrategy(G){}

const string &LocalLabel::label(){
    
    // code sequential strat. here...
    int labels[256];            // rotulos disponiveis
    int pos=0;                  // cursor do rotulo

    Omega simu(256,4,4);
    vector<pair<int,int>> fail;

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

        if(!simu.route(label_[u], label_[v])){
            fail.push_back(make_pair(label_[u], label_[v]));
        } else{
            ss << label_[u] << " " << label_[v] << "\n";
        }

        // cout << "\t" << u << "->" << v << "[label = " << "\"(" << label_[u] << ", " << label_[v] << ")\"];\n"; 
    }
    // cout << "}\n";

    vector<bool> in_use(256,false);
    for(auto &f:fail){
        bool is_fail = true;
        
        for(int i=pos; i<256; i++){

            if(in_use[ labels[i] ]){
                continue;
            }

            if(simu.route(f.first, labels[i])){
                in_use[ labels[i] ] = true;
                ss << f.first << " " << labels[i] << "\n";
                is_fail = false;
                // cout << "//[label = " << "\"(" << f.first << ", " << labels[i] << ")\" color=\"blue\"]; (" << f.second << ")\n"; 
                break;
            }

        }

        /* se não encontrou... mantem */
        if(is_fail){
            ss << f.first << " " << f.second << "\n";
        }
    }

    file = ss.str();
    
    return file;
}