#include "../include/dot2graph.h"
#include "../include/digraph.h"
#include "../include/label.h"
#include "../include/omega.h"
#include <chrono>

#define N 128           // number of pes
#define M 4             // number of input/output per pe
#define LABEL_SIZE 256  // number of labels (network input/output size)

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

int main(int argc, char *argv[]){
    
    srand(10);
  
    /* fill all parameters */
    string filename = argv[1];
    int n           = atoi(argv[2]);
    int st          = atoi(argv[3]); 
    int ex          = atoi(argv[4]);
    bool second_trip= atoi(argv[5]);
    int in_net      = atoi(argv[6]);
    int rounds      = atoi(argv[7]);
    int type        = atoi(argv[8]);

    /* create graph, labeler and network */
    Dot2Graph convert;
    Digraph G = convert.read_dot("misc/benchmark/dot/"+filename, in_net);
    // Label labeler(G, type);
    Omega net = Omega(n,st,ex);
    int num_edges=G.number_of_edges();
    int num_nodes=G.number_of_nodes();

    /* init pe matrix */
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
    
    /* pe[i]: [input0, output0, input1, output1, ...] */
    for(int i=0; i<N; i++){
        for(int j=0; j<M; j++){
            pe[i][j] = (j%2==0 ? inputLabel[ipos++] : outputLabel[opos++]);
        }
    }
    
    /* debug values */
    // cout << filename << "\n";
    // debug_pe(pe);
    // debug_edges(G.edges());
    
    /* mapping node to pe */
    int *node2pe = new int[num_nodes];
    for(int i=0; i<num_nodes; i++){
        node2pe[i]=-1;
    }
    
    /* pes in use */
    bool used[N]={false};
    int count=0;
    int failCount=0;
    
    cout << filename << ", " << num_nodes << ", ";

    for(auto &e:G.edges()){
        
        /* get nodes */
        int u=e.first;
        int v=e.second;

        // cout << count++ << ": edge (" << u << "," << v << ")\n";
        /*           
            case isUalloc isValloc
            0       0       0
            1       0       1
            2       2       0
            3       2       1
        */
        int isUalloc = (node2pe[u]==-1?0:2);
        int isValloc = (node2pe[v]==-1?0:1);
        
        // check if there is a loop
        if(u == v){
            // u/v are allocated
            if(isUalloc){
                int outA = pe[ node2pe[u] ][1];
                int outB = pe[ node2pe[u] ][3];
                int inA = pe[ node2pe[v] ][0];
                int inB = pe[ node2pe[v] ][2];
                
                if( !net.route(outA,inA) && !net.route(outA, inB) && !net.route(outB, inA) && !net.route(outB, inB) ){
                    failCount++;
                }

            } else{
                // if not, allocate
                for(int i=0; i<N; i++){
                    if(!used[i]){
                        int outA = pe[i][1];
                        int outB = pe[i][3];
                        int inA = pe[i][0];
                        int inB = pe[i][2];

                        if( net.route(outA,inA) || net.route(outA, inB) || net.route(outB, inA) || net.route(outB, inB) ){
                            used[i] = true;
                            node2pe[u] = i;
                            break;
                        }   
                    }
                }
            }
            continue;
        }


        bool isRouted = false;
        
        switch( isUalloc + isValloc ){

            /* u and v not allocated */
            case 0:
                for(int i=0; i<N; i++){
                    
                    /* if pe i is in use, continue */  
                    if(used[i]) 
                        continue;
                        
                    for(int j=0; j<N; j++){
                        
                        /* if pe j is in use or is the same pe, continue */
                        if(used[j] || i==j)
                            continue;
                        
                        /* if is pe valid, select pe i and j */
                        /* plug output u into input v */
                        int outA = pe[i][1];
                        int outB = pe[i][3];
                        int inA = pe[j][0];
                        int inB = pe[j][2];
                        
                        /* try all connections */
                        if( net.route(outA,inA) || net.route(outA, inB) || net.route(outB, inA) || net.route(outB, inB) ){
                            
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

                    if( net.route(outA,inA) || net.route(outA, inB) || net.route(outB, inA) || net.route(outB, inB) ){
                        
                        used[i] = true;
                        node2pe[u] = i;
                        
                        isRouted = true;
                        break;
                    }
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
                    
                    if( net.route(outA,inA) || net.route(outA, inB) || net.route(outB, inA) || net.route(outB, inB) ){
                        
                        used[j] = true;
                        node2pe[v] = j;
                        
                        isRouted = true;
                        break;   
                    }
                }
                     
            break;
            
            /* both u and v are allocated */
            case 3:
                int outA = pe[ node2pe[u] ][1];
                int outB = pe[ node2pe[u] ][3];
                
                int inA = pe[ node2pe[v] ][0];
                int inB = pe[ node2pe[v] ][2];
                
                if( net.route(outA,inA) || net.route(outA, inB) || net.route(outB, inA) || net.route(outB, inB) ){
                    isRouted=true;
                }
    
            break;
        }

        /* check the result */
        if(!isRouted){
            failCount++;
            // break; // discart this solution...
        }
    }

    cout << ((num_edges-failCount)*100.0)/num_edges << "\n";
    
    // cout << "mapeamento:\n";
    // for(int i=0; i<num_nodes; i++){
    //     cout << "pe[" << node2pe[i] << "] = " << i << "\n";
    // }
    
    // while(rounds--){

    //     vector<pair<int,int>> fail;
    //     stringstream ss;
    //     int count=0;

    //     /* label graph with strategy 'type' */
    //     string file = labeler.label();
        
    //     /* first trip */
    //     for(int i=0; i<num_edges; i++){
    //         int u,v;
    //         ss << file;
    //         ss >> u >> v;
    //         bool ans = net.route(u,v);
    //         if(!ans){
    //             fail.push_back(make_pair(u,v));
    //         }
    //         count+=ans;
    //     }

    //     /* second trip */
    //     if(second_trip){
    //         net.clear();
    //         for(auto &e:fail)
    //             count += net.route(e.first, e.second);
    //     }
        
    //     /* % routed */
    //     float result = (count*100.0)/num_edges;
    //     cout << result << "\n";
    //     if(result == 100.0) return 0;
    //     net.clear();
    // }

    delete[] node2pe;

    return 0;
}
