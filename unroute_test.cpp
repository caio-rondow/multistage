#include <iostream>
#include "include/omega.h"
using namespace std;

bool assert_equal_after_unroute(Omega&net, const vector<pair<int,int>>&net_input){

    vector<vector<int>> old_circuit = net.copy_circuit();
    vector<vector<int>> old_free    = net.copy_free();

    /* route */
    for(int i=0; i<net_input.size(); i++){
        int input = net_input[i].first;
        int output = net_input[i].second;
        net.route(input, output);
    }

    /* unroute */
    for(int i=0; i<net_input.size(); i++){
        int input = net_input[i].first;
        int output = net_input[i].second;
        net.unroute(input, output);
    }

    vector<vector<int>> new_circuit = net.copy_circuit();
    vector<vector<int>> new_free    = net.copy_free();

    /* compare */
    for(int i=0; i<1024; i++){
        for(int j=0; j<14; j++){
            if(old_circuit[i][j] != new_circuit[i][j] || old_free[i][j] != new_free[i][j]){
                return false;
            }
        }
    }
    return true;
}

int main(){

    Omega net(4,4,1);

    vector<pair<int,int>> test1 = { 
        make_pair(0,0), make_pair(0,1), make_pair(0,2), make_pair(0,3),
        make_pair(1,0), make_pair(1,1), make_pair(1,2), make_pair(1,3),
        make_pair(2,0), make_pair(2,1), make_pair(2,2), make_pair(2,3),
        make_pair(3,0), make_pair(3,1), make_pair(3,2), make_pair(3,3)
    };

    cout << "test 1 - assert net after unroute: " << (assert_equal_after_unroute(net, test1) == true ? "ok\n" : "not ok\n");

    return 0;
}