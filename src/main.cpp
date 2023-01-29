#include "../include/omega.h"

int main(int argc, char **argv){

    int n=atoi(argv[1]);
    int st=atoi(argv[2]); 
    int ex=atoi(argv[3]);
    
    Omega net(n,st,ex);
    int numEdges, count=0;

    cin >> numEdges;
    for(int i=0; i<numEdges; i++){
        int u,v;
        cin >> u >> v;
        count += net.route(u,v);
    }

    cout << (count*100.0)/numEdges << "\n";

    return 0;
}