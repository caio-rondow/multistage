#include "../include/auxf.h"

int wire[256][5];

bool omega(int entrada, int saida){
    
    for(int extra=0b00; extra<4; extra+=0b01){

        // Concatena entrada+extra+saida...
        int caminho=(entrada<<10) | (extra<<8) | saida;

        // marca que encontrou um caminho
        bool encontrou=true;

        for(int j=0; j<5; j++){
            
            // Pega o valor da janela atual
            int i = 255 & (caminho >> (2*(4-j)));

            assert_values(entrada,extra,saida,caminho,i);

            if(wire[i][j]==0){ // Se o caminho não está ocupado, ocupe
                wire[i][j]=1;
            } else{ // senão, marca que não encontrou e permute extra
                encontrou=false;
                break;
            }
        }

        if(encontrou) 
            return true;
    }

    return false;
}

int main(int argc, char **argv){

    int attempts, ct=0;

    cin>>attempts;
    for(int i=0; i<attempts; i++){
        int u, v;
        cin>>u>>v;
        ct+=(omega(u,v)?1:0);
    }

    // print_omega(wire);
    cout << (ct*100.0)/attempts;

    return 0;
}