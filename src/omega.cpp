#include "../include/omega.h"

Omega::Omega(int _n, int _st, int _ex, int _radix, int _mask):
n(_n), st(_st), ex(_ex), radix(_radix), mask(_mask){
    L=pow(4,ex);
    inword = vector<vector<int>>(MAX_ST);
    outword = vector<int>(MAX_ST,-1);
    clear();
}

void Omega::set_omega(int stage, int extra, int in){
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
                result = result && (circuit[i][j]==in_switch); 
        }

        // se encontrou um caminho...
        if(result){
            // cout << input << "\n";

            for(int j=0; j<st+ex; j++){
                i = (word >> (2*(st+ex) - 2*(j+1))) & mask;
                in_switch = (word >> (2*(2*st+ex-1)-2*j)) & 3;
                // marca o caminho que fez em circuit
                free[i][j] = true;
                circuit[i][j] = in_switch;

                // cout << i << "\n";
            } //cout << "\n";
            // cout << word << "\n";
            /* marca na tabela qual caminho eu fiz para input/output */
            cout << "input x output: " << input << " x " << output << " -> word " << word << "\n";
            inword[input].push_back(word);
            outword[output]=word;

            return true;
        }
    }

    return false;
}

void Omega::unroute(int word){

    if(word == -1)
        return;

    for(int j=0; j<st+ex; j++){
        int i = (word >> (2*(st+ex) - 2*(j+1))) & mask;
        free[i][j]=false;
        circuit[i][j]=false;
    }
}

void Omega::dealloc(PE elem){

    /* se o pe ja está desalocado */
    if(elem.node == -1)
        return;

    int *input = elem.input;
    int *output = elem.output;
    int n = elem.n;
    int m = elem.m;

    cout << "input:\n";
    for(int i=0; i<n; i++){
        
        int in = output[i];
        int size = inword[in].size();

        for(int j=0; j<size; j++){
            int word = inword[in][j];

            cout << in << " " << word << "\n";
            unroute(word);
        }

        inword[in].erase(inword[in].begin(), inword[in].end());
    }

    cout << "output:\n";
    for(int i=0; i<m; i++){
        int word = outword[input[i]];
        unroute(word);
        cout << input[i] << " " << word << "\n";
        output[i]=-1;
    }

}

void Omega::clear(){ // reseta a rede
    for(int i=0; i<n; i++){
        for(int j=0; j<st+ex; j++){
            free[i][j]=false;
            circuit[i][j]=false;
        }
    }
}

void Omega::print_network(){
    for(int i=0; i<n; i++){
        for(int j=0; j<st+ex; j++){
            cout << free[i][j] << " ";
        } cout << "\n";
    } 
}