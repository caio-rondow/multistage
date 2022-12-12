#include "../include/auxf.h"

/*  
    fios da rede
    salva caminho possivel
    numero de entradas/saidas
    numero de estagios
    numero de estagios extra
    quantos fios por switch
    número de permutações para o estagio extra 
    tamanho da janela(com todos os bits ligados)
*/ 
int wire[256][5];
int path[5];
int n, st, ex, radix, L, mask;

bool omega(int entrada, int saida){

    for(int extra=0; extra<L; extra++){

        // Concatena entrada+extra+saida...
        int caminho = saida | (entrada<<(2*(st+ex))) | (extra<<(2*st));

        // marca que encontrou um caminho
        bool encontrou=true;

        for(int j=0; j<st+ex; j++){
        
            // Pega o valor da janela atual
            int i = caminho >> (2*(st+ex-1-j)) & mask;

            encontrou = encontrou & !wire[i][j];

            // Se o caminho não está ocupado
            // senão, permute bit extra
            if(encontrou) path[j]=i;               
            else break;
        } 

        if(encontrou) {
            for(int j=0; j<st+ex; j++)
                wire[path[j]][j]=true;
            return true;
        }
    }

    return false;
}

int main(int argc, char **argv){

    int attempts, ct=0, rounds=atoi(argv[1]);
    
    /* parâmetros rede multiestágio */
    n       = atoi(argv[2]);
    st      = atoi(argv[3]); 
    ex      = atoi(argv[4]); 
    radix   = atoi(argv[5]);
    L       = (ex<1?1:radix<<ex);
    mask    = atoi(argv[6]);

    while(rounds--){

        cin>>attempts;

        for(int i=0; i<attempts; i++){
            int u, v;
            cin>>u>>v;
            ct+=(omega(u,v)?1:0);
        }
        
        double res=(ct*100.0)/attempts;
        cout << res << "\n";

        // reset
        ct=0;
        for(int i=0; i<n; i++)
            for(int j=0; j<st+ex; j++)
                wire[i][j]=0;
    }

    return 0;
}