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
vector<pair<int,int>> edges;
int wire[256][5];
int path[5];
int n, st, ex, radix, L, mask;

int hist[16][4];

void print_dataframe(){
    cout << "df = pd.DataFrame(\n[";
    for(int i=0; i<16; i++){
        bitset<4> idx(i);
        cout << "\t['" << idx << "', ";
        for(int j=0; j<4; j++){
            if (j<3) cout << hist[i][j] << ", ";
            else cout << hist[i][j] << "]";
        } 
        if(i==15) cout << "],\n";
        else cout << ",\n";
    } cout << "columns=['sufix', '00', '01', '10', '11'])\nprint(df)\n";

    for(int i=0; i<16; i++)      
        for(int j=0; j<4; j++)
            hist[i][j]=0;
}

bool omega(int entrada, int saida){

    bitset<4>a(entrada);
    bitset<2>b(saida>>6);

    int in=(int)(a.to_ulong());
    int out=(int)(b.to_ulong());
    
    hist[in][out]+=1;
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
            bitset<8> bite(entrada);
            bitset<8> bits(saida);
            bitset<2> bitext(extra);
            cout << "encontrou " << bite << " "<< bitext << " " << bits << " - " << in << " " << out << "\n";
            for(int j=0; j<st+ex; j++)
                wire[path[j]][j]=true;
            return true;
        }
    }

    cout << "nao encontrou " << entrada << " " << saida << "\n";
    edges.push_back(make_pair(entrada, saida));
    return false;
}

int main(int argc, char **argv){

    int attempts, ct=0, rounds=atoi(argv[1]);

    /* parâmetros rede multiestágio */
    n       = atoi(argv[2]);
    st      = atoi(argv[3]); 
    ex      = atoi(argv[4]); 
    radix   = atoi(argv[5]);
    L       = (ex<1?1:(radix/2)<<ex);
    mask    = atoi(argv[6]);

    while(rounds--){

        cin>>attempts;

        // primeira passada
        for(int i=0; i<attempts; i++){
            int u, v;
            cin>>u>>v;
            ct+=(omega(u,v)?1:0);
        }

        print_dataframe();
        double res=(ct*100.0)/attempts;
        cout << res << "\n";

        // // reset
        // clear_omega(wire, n, st+ex);

        // // segunda passada
        // int second=edges.size();
        // for(int i=0; i<second; i++){
        //     int u=edges[i].first, v=edges[i].second;
        //     ct+=(omega(u,v)?1:0);
        // }

        // //print_dataframe();
        
        // double res=(ct*100.0)/attempts;
        // cout << res << " arestas 2a passada " << second << "/" << attempts << "\n";

        // reset
        ct=0;
        clear_omega(wire, n, st+ex);
    }   

    for(int i=0; i<16; i++){
        cout << i << " ";
        for(int j=0; j<4; j++){
            cout << hist[i][j] << " ";
        } cout << "\n";
    }

    return 0;
}