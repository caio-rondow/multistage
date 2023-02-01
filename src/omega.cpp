#include "../include/omega.h"

Omega::Omega(int _n, int _st, int _ex, int _radix, int _mask):
n(_n), st(_st), ex(_ex), radix(_radix), mask(_mask){
    L=pow(4,ex);
}

void Omega::setOmega(int stage, int extra, int in){
    st=stage;
    ex=extra;
    n=in;
    mask=in-1;
    L=pow(4,ex);
}

bool Omega::route(int input, int output){

    int i, in_switch;

    for(int extra=0; extra<L; extra++){

        // supondo que encontrei um caminho
        bool result=true;

        // concatena palavra: entrada+extra+saida
        int word = output | (input<<(2*st+2*ex)) | (extra<<(2*st));

        // para todos os estagios...
        for(int j=0; j<st+ex; j++){
            
            // pega o valor da janela atual
            i = (word >> (2*(st+ex)- 2*(j+1))) & mask;

            // checa o estado atual do switch do estagio j
            in_switch = (word >> (2*(2*st+ex-1)-2*j)) & 3;

            // se o caminho esta ocupado
            // senão, permute um bit extra
            if(free[i][j]) 
                result = result && (wire[i][j]==in_switch); 
        }

        // se encontrou um caminho...
        if(result){
            for(int j=0; j<st+ex; j++){
                i = (word >> (2*(st+ex)- 2*(j+1))) & mask;
                in_switch = (word >> (2*(2*st+ex-1)-2*j)) & 3;
                // marca o caminho que fez em wire
                free[i][j] = true;
                wire[i][j] = in_switch;
            }
            return true;
        }
    }

    return false;
}

void Omega::clear(){ // reseta a rede
    for(int i=0; i<n; i++){
        for(int j=0; j<st+ex; j++){
            free[i][j]=false;
            wire[i][j]=false;
        }
    }
}