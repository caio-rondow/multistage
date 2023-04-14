#include "../include/omega.h"

Omega::Omega(int _n, int _st, int _ex, int _radix, int _mask):
n(_n), st(_st), ex(_ex), radix(_radix), mask(_mask){
    L=pow(4,ex);
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
            vector<pair<int,int>> path;
            for(int j=0; j<st+ex; j++){
                i = (word >> (2*(st+ex) - 2*(j+1))) & mask;
                in_switch = (word >> (2*(2*st+ex-1)-2*j)) & 3;
                // marca o caminho que fez em circuit
                free[i][j] = true;
                circuit[i][j] = in_switch;
                path.push_back( make_pair(i,j) );
                // cout << i << "\n";
            } //cout << "\n";
            // cout << word << "\n";
            /* marca na tabela qual caminho eu fiz para input/output */
            used_path[word] = path;
            return true;
        }
    }

    return false;
}

void Omega::unroute(int input, int output){

    int word;
    bool isPath = false;
    for(int extra=0; extra<L; extra++){
        word = output | (input<<(2*st+2*ex)) | (extra<<(2*st));
        if(used_path.find(word) != used_path.end()){
            // cout << word << " is in the hash table...\n";
            isPath = true;
            break;
        }
    }

    if(isPath){
        vector<pair<int,int>> path = used_path[word];
        for(auto &p:path){
            int i = p.first;
            int j = p.second;
            circuit[i][j] = false;
            free[i][j] = false;
        }
    }

    // /* check every extra */
    // for(int extra=0; extra<L; extra++){
        
    //     /* check for all multicasts */
    //     for(int i=0; i<256; i++){
    //         word = i | (input<<(2*st+2*ex)) | (extra<<(2*st));
            
    //         /* if found, remove route */
    //         if(used_path.find(word) != used_path.end()){
    //             for(auto &path:used_path[word]){
                    
    //                 int i = path.first;
    //                 int j = path.second;

    //                 circuit[i][j] = false;
    //                 free[i][j] = false;
    //             }
    //         }
    //     }
    // }
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

vector<vector<int>> Omega::copy_circuit(){

    vector<vector<int>> copy_circuit(MAX_IN,vector<int>(MAX_ST));
    for(int i=0; i<MAX_IN; i++){
        for(int j=0; j<MAX_ST; j++){
            copy_circuit[i][j] = circuit[i][j];
        }
    }
    return copy_circuit;
}

vector<vector<int>> Omega::copy_free(){

    vector<vector<int>> copy_free(MAX_IN,vector<int>(MAX_ST));
    for(int i=0; i<MAX_IN; i++){
        for(int j=0; j<MAX_ST; j++){
            copy_free[i][j] = free[i][j];
        }
    }
    return copy_free;
}