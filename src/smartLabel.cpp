#include "../include/smartLabel.h"

SmartLabel::SmartLabel(const Digraph&G):LabelStrategy(G){
    /* create similar table */
    for(int i=0; i<64; i++){
        vector<int> line(4);
        iota(line.begin(), line.end(), (i*4));
        similar_table_.push_back(line);
    }

    /* finding multicast nodes */
    for(auto &node:G_.nodes()){
        if( G_.out_degree(node) > 1 ){
            multicast_.push_back(node);
        }
    }
}

const string &SmartLabel::label(){
    // code smart strat. here...        
    int labels[256];
    int pos=0;

    // Init arrays
    for(int i=0; i<nv; i++)
        visited_[i]=-1;
    for(int i=0; i<256; i++)
        labels[i]=i;
    random_shuffle(labels, labels+256);

    // Rotulando multicasts primeiro
    for(auto &node:multicast_){
        int i = (labels[pos++]&252)/4;
        int j = 0;
        for(auto &neighbor:G_.neighbors(node)){
            int item = similar_table_[i][j++];
            label_[neighbor] = item;
            visited_[neighbor]=1;
        }
    }

    // Rotulando o resto
    // cout << "digraph fir16{\n";
    stringstream ss;
    for(auto &e:edges){
        
        int u = e.first;
        int v = e.second;
        int name;

        // se u não foi visitado
        if(visited_[u]==-1){
            name = labels[pos++];  // pega label_ valida e marca como usada
            label_[u] = name;      // rotula u
            visited_[u]=0;         // marca como visitado
        }
        
        if(!G_.is_multicast(u)){
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
        }
        ss << label_[u] << " " << label_[v] << "\n";
        // cout << "\t" << u << "->" << v << " [label_=\"("<< label_[u] << ", " << label_[v] << ")\"]\n";
    }
    // cout << "}\n";
    file = ss.str();
    
    return file;
}