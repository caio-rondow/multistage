#include <iostream>
#include <bitset>
#include <bits/stdc++.h>
using namespace std;

int linhaLivre[128][5];
int linha[5];

// int bitExtracted(int number, int k, int p){
//     return (((1 << k) - 1) & (number >> p));
// }

void print_omega(){
    for(int i=0; i<128; i++){
        for(int j=0; j<5; j++){
            cout << linhaLivre[i][j] << " ";
        } cout << "\n";
    }
}

bool omega(int entrada, int saida){
    
    bitset<8> bit_in(entrada);
    bitset<8> bit_out(saida);

    for(int extra=0b00; extra<4; extra+=0b01){

        int caminho= (entrada<<10) | (extra<<8) | saida;
        bitset<18> bitw(caminho);
        bitset<2> bit_ex(extra);

        cout << "entrada: " << entrada << "\t( " << bit_in << " )\n";
        cout << "extra: " << extra << "\t( " << bit_ex << " )\n";
        cout << "saida: " << saida << "\t( " << bit_out << " )\n";
        cout << "caminho: " << caminho << "\t( " << bitw << " )\n\n";

        bool encontrou=true;

        for(int j=0; j<5; j++){
            
            int i = 255 & (caminho >> (2*(4-j)));
            // bitset<8> biti(i);
            // cout << "linha: " << i << "\t( " << biti << " )\n";

            if(i>128){
                cout << printf("Erro, linha %d > 128.\n", i);
                exit(0);
            } 

            if(linhaLivre[i][j]==0){
                linhaLivre[i][j]=1;
            } else{
                encontrou=false;
                break;
            }
        }

        cout << "\n";

        if(encontrou)
            return true;
    }

    return false;
}


int main(){

    int entrada = 0b00000001;
    int saida = 0b00000111;
    
    int attempts=1000;
    for(int i=0; i<attempts; i++){
        bool ans=omega(i*2, 1+(i*2));
        cout << (ans? "encontrou!":"nao encontrou...") << "\n";
    }

    return 0;
}