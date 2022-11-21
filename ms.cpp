#include <iostream>
#include <bitset>
#include <bits/stdc++.h>
using namespace std;

int linhaLivre[256][5];

void print_omega(){
    for(int i=0; i<256; i++){
        for(int j=0; j<5; j++){
            cout << linhaLivre[i][j] << " ";
        } cout << "\n";
    }
}

// int slide_window(int n, int winSize, int p){
//     return (((1 << winSize) - 1) & (n >> p));
// }

bool omega(int entrada, int saida){
    
    bitset<8> bit_in(entrada);
    bitset<8> bit_out(saida);

    for(int extra=0b00; extra<4; extra+=0b01){

        int caminho= (entrada<<10) | (extra<<8) | saida;
        bitset<18> bitw(caminho);
        bitset<2> bit_ex(extra);

        bool encontrou=true;

        for(int j=0; j<5; j++){
            
            int i = 255 & (caminho >> (2*(4-j)));
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

            if(linhaLivre[i][j]==0){
                linhaLivre[i][j]=1;
            } else{
                encontrou=false;
                break;
            }
        }

        if(encontrou)
            return true;
    }

    return false;
}

int main(){

    int attempts=500;
    for(int i=0; i<attempts; i++){
        bool ans=omega(i*2, 1+(i*2));
        cout << "(" << i*2 << "," << 1+(i*2) << ") "
             << (ans?"encontrou!":"nao encontrou...") << "\n";
    }

    return 0;
}
