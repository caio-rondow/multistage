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


/*
omega:
    // bitset<8> bite(entrada);
    // bitset<8> bits(saida);

    // cout << "entrada\t\t" << bite << "(" << entrada << ")\n";
    // cout << "saida\t\t" << bits << "(" << saida << ")\n\n";
    // cout << "L " << L << "\n";

        // bitset<2> bitex(extra);
        // bitset<18>bitw(caminho);
        // cout << "extra\t\t........" << bitex << "........\t-----------------\n";
        // cout << "caminho\t\t" << bitw << "\t-----------------\n";

        // bitset<8> biti(i);
        // bitset<8> bite(entrada);
        // bitset<8> bits(saida);
        // bitset<8> biten(encontrou);

        // cout << "estagio " << j << "\t";
        // for(int k=0; k<j+1; k++) cout << "..";
        // cout << biti;
        // for(int k=4; k>=j+1; k--) cout << "..";
        // cout << "\t" << "fio " << i << "\t" << " estado " << wire[i][j] << "\n";

    // cout << "\n";

main:

        // cout << "(" << u << " -> " << v << "):\n";
        // cout << "=========================================================\n\n";
        
        // if(ans) cout << "(" << i << " -> " << i+x << ") encontrou!\n";
        // else cout << "(" << i << " -> " << i+x << ") nao encontrou...\n";

        // cout << "\n =========================================================\n\n";
    
    // print_omega(wire);
    // cout << "n=" << x << ":\t" << res << "%\n";
*/
