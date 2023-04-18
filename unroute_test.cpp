#include <iostream>
#include "include/omega.h"
using namespace std;

int main(){

    Omega net(8,4,1);

    /* CONFIGURAÇÃO DA ARQUITETURA */
    vector<PE> arc;
    for(int i=0; i<8; i++){
        arc.push_back(PE(1,1));
    }

    /* ROTULAÇÃO */
    int input_label[8];
    int output_label[8];
    for(int i=0; i<8; i++){
        input_label[i]=i;
        output_label[i]=i;
    }
    random_shuffle(input_label, input_label+8);
    random_shuffle(output_label, output_label+8);
    int k=0;
    for(int i=0; i<8; i++){
        arc[i].input[0]  = input_label[k];
        arc[i].output[0] = output_label[k];
        k++;
    } 


    for(int i=0; i<8; i++){
        cout << "PE " << i << "\n";
        cout << "input: ";
        cout << arc[i].input[0] << " ";
        cout << "output: ";  
        cout << arc[i].output[0] << " ";
        cout << "\n\n";
    } 

    /* POSICIONAMENTO E ROTEAMENTO */
    arc[0].node = 0;
    arc[1].node = 1;
    arc[2].node = 2;
    arc[3].node = 3;
    arc[4].node = 4;
    arc[5].node = 5;
    arc[6].node = 6;
    arc[7].node = 7;

    net.route( arc[0].output[0], arc[1].input[0] );
    net.print_network(); cout << "\n";
    net.route( arc[1].output[0], arc[1].input[0] );
    net.print_network(); cout << "\n";
    // net.route( arc[1].output[0], arc[2].input[0] );
    // net.print_network(); cout << "\n";
    // net.route( arc[1].output[0], arc[3].input[0] );
    // net.print_network(); cout << "\n";

    net.dealloc(arc[1]);
    net.print_network(); cout << "\n";

    return 0;
}