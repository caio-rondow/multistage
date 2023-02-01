#include "../include/omega.h"

int main(int argc, char **argv){

    int n=atoi(argv[1]);
    int st=atoi(argv[2]); 
    int ex=atoi(argv[3]);
    bool secondTrip=atoi(argv[4]);
    
    Omega net(n,st,ex);
    int numEdges, count=0;
    vector<pair<int,int>> fail;

    /* first trip */
    cin >> numEdges;
    for(int i=0; i<numEdges; i++){
        int u,v;
        cin >> u >> v;
        bool ans = net.route(u,v);
        if(!ans) 
            fail.push_back(make_pair(u,v));
        count+=ans;
    }
    
    /* second trip */
    if(secondTrip){
        net.clear();
        for(auto &e:fail)
            count += net.route(e.first, e.second);
    }
    
    /* % routed */
    cout << (count*100.0)/numEdges << "\n";

    return 0;
}