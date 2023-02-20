#include "../include/dot2graph.h"
#include "../include/digraph.h"
#include "../include/label.h"
#include "../include/omega.h"
#include <chrono>

int main(int argc, char *argv[]){
    
    srand(time(0));
  
    /* fill all parameters */
    string filename=argv[1];
    int n=atoi(argv[2]);
    int st=atoi(argv[3]); 
    int ex=atoi(argv[4]);
    bool second_trip=atoi(argv[5]);
    int in_net=atoi(argv[6]);
    int rounds=atoi(argv[7]);
    int type=atoi(argv[8]);
    
    /* create graph, labeler and network */
    Dot2Graph convert;
    Digraph G = convert.read_dot("misc/benchmark/dot/"+filename, in_net);
    Label labeler(G, type);
    Omega net(n, st, ex);
    int num_edges=G.number_of_edges();

    while(rounds--){

        vector<pair<int,int>> fail;
        stringstream ss;
        int count=0;

        /* label graph with strategy 'type' */
        string file = labeler.label();

        /* first trip */
        for(int i=0; i<num_edges; i++){
            int u,v;
            ss << file;
            ss >> u >> v;
            bool ans = net.route(u,v);
            if(!ans)
                fail.push_back(make_pair(u,v));
            count+=ans;
        }

        /* second trip */
        if(second_trip){
            net.clear();
            for(auto &e:fail)
                count += net.route(e.first, e.second);
        }
        
        /* % routed */
        float result = (count*100.0)/num_edges;
        cout << result << "\n";
        if(result == 100.0) return 0;
        net.clear();
    }

    // auto end = std::chrono::high_resolution_clock::now();
    // auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    // std::cout << "Duration: " << duration.count() << " microseconds" << std::endl;

    return 0;
}