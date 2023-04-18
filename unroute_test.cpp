#include <iostream>
#include "include/omega.h"
using namespace std;

int main(){

    Omega net(4,4,1);
    vector<PE> arc;

    for(int i=0; i<4; i++){
        arc.push_back(PE(2,2));
    }

    int input_label[8];
    int output_label[8];
    for(int i=0; i<8; i++){
        input_label[i]=i;
        output_label[i]=i;
    }
    random_shuffle(input_label, input_label+8);
    random_shuffle(output_label, output_label+8);

    int k=0;
    for(int i=0; i<4; i++){
        for(int j=0; j<2; j++){  
            arc[i].input[j] = input_label[k];
            arc[i].output[j] = output_label[k];
            k++;
        }
    } 

    net.route(0,1);
    net.print_network();

    return 0;
}