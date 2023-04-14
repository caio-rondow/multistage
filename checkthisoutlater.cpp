#include <iostream>
#include <algorithm>
#include <vector>
#define N 128           // number of pes
#define M 4             // number of input/output per pe
#define LABEL_SIZE 256  // number of labels (network input/output size)
using namespace std;

bool route(int input, int output){
    return rand()%2;
}

void debug_pe(int pe[][M]){
    for(int i=0; i<N; i++){
        for(int j=0; j<M; j++){
            cout << pe[i][j] << " ";
        }
        cout << "\n";
    }  
}

void debug_edges(const vector<pair<int,int>>&edges){
    for(auto &e:edges){
        cout << e.first << " " << e.second << "\n";
    }
}

int main(){
    
    // srand(time(0));
    
    /* init pe matrix*/
    int pe[N][M];
    int inputLabel[LABEL_SIZE];
    int outputLabel[LABEL_SIZE];
    
    for(int i=0; i<LABEL_SIZE; i++){
        inputLabel[i]=i;
        outputLabel[i]=i;
    }
    
    random_shuffle(inputLabel, inputLabel+LABEL_SIZE);
    random_shuffle(outputLabel, outputLabel+LABEL_SIZE);
    int ipos=0;
    int opos=0;
    
    /* pe[i]: [input0, output0, input1, output1, ...]*/
    for(int i=0; i<N; i++){
        for(int j=0; j<M; j++){
            pe[i][j] = (j%2==0 ? inputLabel[ipos++] : outputLabel[opos++]);
        }
    }
    
    /* init graph edges */
    vector<pair<int,int>> edges;
    pair<int,int> edgeAB = make_pair(0,1);
    pair<int,int> edgeBC = make_pair(1,2);
    edges.push_back(edgeAB);
    edges.push_back(edgeBC);
    
    /* debug values */
    // debug_pe(pe);
    // debug_edges(edges);
    
    /* mapping node to pe */
    int node2pe[3];
    for(int i=0; i<N; i++){
        node2pe[i]=-1;
    }
    
    /* pes in use */
    bool used[N]={false};
    
    for(auto &e:edges){
        
        /* get nodes */
        int u=e.first;
        int v=e.second;
        
        /*           
            case isUalloc isValloc
            0       0       0
            1       0       1
            2       2       0
            3       2       1
        */
        int isUalloc = (node2pe[u]==-1?0:2);
        int isValloc = (node2pe[v]==-1?0:1);
        cout << "case " << isUalloc << isValloc << " : " << isValloc+isUalloc << "\n";
        
        bool isRouted = false;
        
        switch( isUalloc + isValloc ){
            /* u and v not allocated */
            case 0:
                for(int i=0; i<N; i++){
                    
                    /* if pe i is in use, continue */  
                    if(used[i]) 
                        continue;
                        
                    for(int j=0; j<N; j++){
                        
                        /* if pe j is in use, continue */
                        if(used[j] || i==j)
                            continue;
                        
                        
                        /* if can route, select pe i and j */
                        int outA = pe[i][1];
                        int outB = pe[i][3];
                        
                        int inA = pe[j][0];
                        int inB = pe[j][2];
                        
                        /* try all connections */
                        if( route(outA,inA) || route(outA, inB) || route(outB, inA) || route(outB, inB) ){
                            
                            used[i] = true;
                            used[j] = true;
                            node2pe[u] = i;
                            node2pe[v] = j;
                            
                            isRouted = true;
                            break;
                            
                        }
                    }
                    
                    if(isRouted)
                        break;
                }
                
                if(!isRouted){
                    cout << "could not route u to v.\n";
                } else{
                    cout << "u and v allocated in " << node2pe[u] << " " << node2pe[v] << "\n";
                }
            
                break;
            
            /* u not allocated, but v is */
            case 1:
                for(int i=0; i<N; i++){
                    if(used[i] || i==node2pe[v])
                        continue;
                        
                    int outA = pe[i][1];
                    int outB = pe[i][3];
                    
                    int inA = pe[ node2pe[v] ][0];
                    int inB = pe[ node2pe[v] ][2];

                    if( route(outA,inA) || route(outA, inB) || route(outB, inA) || route(outB, inB) ){
                        
                        used[i] = true;
                        node2pe[u] = i;
                        
                        isRouted = true;
                        break;
                        
                    }
                }
                
                if(!isRouted){
                    cout << "could not route u to v.\n";
                } else{
                    cout << "u and v allocated in " << node2pe[u] << " " << node2pe[v] << "\n";
                }    
            
                break;
            
            /* u allocated, but v isn't */    
            case 2:
                for(int j=0; j<N; j++){
                    if(used[j] || node2pe[u]==j)
                        continue;
                        
                    int outA = pe[ node2pe[u] ][1];
                    int outB = pe[ node2pe[u] ][3];
                    
                    int inA = pe[j][0];
                    int inB = pe[j][2];
                    
                    if( route(outA,inA) || route(outA, inB) || route(outB, inA) || route(outB, inB) ){
                        
                        used[j] = true;
                        node2pe[v] = j;
                        
                        isRouted = true;
                        break;
                        
                    }
                }
                
                if(!isRouted){
                    cout << "could not route u to v.\n";
                } else{
                    cout << "u and v allocated in " << node2pe[u] << " " << node2pe[v] << "\n";
                }   
            
                break;
            
            /* both u and v are allocated */
            case 3:
                int outA = pe[ node2pe[u] ][1];
                int outB = pe[ node2pe[u] ][3];
                
                int inA = pe[ node2pe[v] ][0];
                int inB = pe[ node2pe[v] ][2];
                
                if( route(outA,inA) || route(outA, inB) || route(outB, inA) || route(outB, inB) ){
                    cout << "u and v allocated in " << node2pe[u] << " " << node2pe[v] << "\n";
                } else{
                    cout << "could not route u to v.\n";
                }
    
                break;
        }
    }
      
    return 0;
}