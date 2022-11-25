#include <iostream>
#include <bitset>
#include <bits/stdc++.h>
using namespace std;

/* AUX FUNCTIONS */
int log_radix_N(int N, int radix){
    return (N > radix - 1)
            ? 1 + log_radix_N(N / radix, radix)
            : 0;
}

int slide_window(int n, int winSize, int p){
    return (((1 << winSize) - 1) & (n >> p));
}

void print_omega(int wire[256][5]){
    for(int i=0; i<256; i++){
        for(int j=0; j<5; j++){
            cout << wire[i][j] << " ";
        } cout << "\n";
    } cout << "\n";
}

void assert_values(int entrada, int extra, int saida, int caminho, int i){

    bitset<8> bit_in(entrada);
    bitset<8> bit_out(saida);
    bitset<18> bitw(caminho);
    bitset<2> bit_ex(extra);
    bitset<8> biti(i);

    if(i>256){
        cout << "entrada: " << entrada << "\t( " << bit_in << " )\n";
        cout << "extra: " << extra << "\t( " << bit_ex << " )\n";
        cout << "saida: " << saida << "\t( " << bit_out << " )\n";
        cout << "caminho: " << caminho << "\t( " << bitw << " )\n";
        cout << "linha: " << i << "\t( " << biti << " )\n\n";

        cout << printf("Erro, linha %d > 256.\n", i);
        exit(0);
    } 
}