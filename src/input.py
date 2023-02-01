import networkx as nx
import random as rand
import os
import sys

def name_seq_v2(G,filename,arg1):
    ct=0
    
    with open(filename, 'w') as f:
        f.write(str(G.number_of_edges()*arg1)+"\n")
        label=dict()
        name=0
        for it in range(arg1):
            visited=[]
            _str=""

            for node in G.nodes():
                if G.in_degree(node)<=1:
                    ct+=1
                    label[node]=name
                    name+=1
                else:
                    ct+=1
                    label[node]=name+64
                    name+=1
            
            for u,v in G.edges():
                if v not in visited:
                    visited.append(v)
                else:
                    ct+=1
                    value=label[v]-64+128
                    label.update({v:value})
                    
                _str+=str(label[u])+" "+str(label[v])+"\n"
            f.write(_str)
        f.close()

def name_rand_v2(G,filename,arg1):
    
    ct=0
    with open(filename, 'w') as f:

        #labels1=list(range(0,64))
        #labels2=[list(range(64,128)), list(range(128, 192))]
        
        labels=list(range(0,256))
        label=dict()
        f.write(str(G.number_of_edges()*arg1)+"\n")

        for it in range(arg1):
            visited=[]
            _str=""
        
            for node in G.nodes():
                if G.in_degree(node)<=1:
                    ct+=1
                    #name=rand.choice(labels1)
                    name=rand.choice(labels)
                    label[node]=name
                    labels.remove(name)
                    #labels1.remove(name)
                else:
                    ct+=1
                    # name=rand.choice(labels2[0])
                    name=rand.choice(labels)
                    label[node]=name
                    labels.remove(name)
                    # labels2[0].remove(name)

            for u,v in G.edges():
                if v not in visited:
                    visited.append(v)
                else:
                    ct+=1
                    # name=rand.choice(labels2[1])
                    name=rand.choice(labels)
                    label.update({v:name})
                    # labels2[1].remove(name)
                    labels.remove(name)

                _str+=str(label[u])+" "+str(label[v])+"\n"
            f.write(_str)
        f.close()

def rotula(visited , labels, label, v):
    # marca como visitado
    visited[v]=0

    # rotula v
    nameV = rand.choice(labels)
    label[v] = nameV
    labels.remove(nameV)

def name_rand_v3(G,filename,arg1):
    rand.seed(1)
    # for e in G.edges(): print(e)
    with open(filename+".txt", 'w') as f:

        f.write(str(G.number_of_edges()*arg1)+"\n")

        for it in range(arg1):
            input=""
            visited=dict()
            label=dict()
            labels=list(range(256))

            # percorre o grafo e vê quem tem multicast
            multicast_nodes = [node for node in G.nodes() if G.out_degree(node)>1]

            # para cada nó multicast
            for node in multicast_nodes:
                # pega os vizinhos, e escolhe os nomes
                neighbors = list(G.neighbors(node))
                name = rand.choice(labels)&252
                permutations = [name, name+1, name+2, name+3]
                neighbors_name = rand.sample(permutations, len(neighbors))
                
                # para cada vizinho, rotule-o
                for neighbor, name in zip(neighbors,neighbors_name):
                    label[neighbor] = name
                    if name in labels:
                        labels.remove(name)
                    
                    # marca como visitado de multicast
                    visited[neighbor] = None
            
            print("digraph Fir16 {")
            for (u,v) in G.edges(): 
                
                # Se vertice não foi visitado, visita e rotula
                if u not in visited:
                    rotula(visited, labels, label, u)
                if v not in visited:
                    rotula(visited, labels, label, v)            

                # se o vertice de saida não for um nó de saida do multicast
                if visited[v]!=None: 

                    # indica o grau de entrada do vértice v
                    visited[v]+=1
            
                    # mais de 1 entrada, mude de nome
                    if visited[v]>=2:
                        # pega os rotulos
                        newLabel = rand.choice(labels)
                        oldLabel = label[v]

                        # atualiza lista de rotulos
                        label.update({v:newLabel})
                        labels.append(oldLabel)
                        labels.remove(newLabel)
                input+=str(label[u])+" "+str(label[v])+"\n"
                print(f"\t{u}->{v} [label=\"({label[u]}, {label[v]})\"]")
            print("}")
            f.write(input)
        f.close()


def name_by_histogram(G, src='', filename='', arg1=1):
   
    src='A0' # mudar isso aqui dps (esse src é do fir16)
    # Create table
    table=[None for i in range(256)]

    pos=0
    for i in range(4):
        for j in range(4):
            for k in range(16):
                table[pos]=(i*16)+(j*64)+k
                pos+=1

    # for i in range(256):
    #     print('/{:08b}'.format(table[i]))
    # print()

    # get traversal path (dfs)
    path = list(nx.edge_dfs(G,source=src,orientation='reverse'))

    # Name graph
    label={}
    visited={}
    pos=0
    ct=0
    with open(filename, 'w') as f:
        f.write(str(G.number_of_edges()*arg1)+"\n")
        _str=""
        for (input, output, ignore) in path:
            
            if output not in visited:
                label[output]=table[pos]
                pos+=1
                ct+=1
                visited[output]=0
            elif visited[output]==0:
                visited[output]+=1
            elif visited[output]>=1:
                label.update({output:table[pos]})
                pos+=1
                ct+=1
                visited[output]+=1

            if input not in visited:
                label[input]=table[pos]
                pos+=1
                ct+=1
                visited[input]=0
            
            #_str+=input+":"+str(label[input])+" | "+str(output)+":"+str(label[output])+"\n"
            _str+=str(label[input])+" "+str(label[output])+"\n"
        f.write(_str)
        f.close()

    #print(ct)
    pass

def main():

    # print(sys.argv[4])
    # READ DOT
    filename='./misc/benchmark/dot/'+sys.argv[4] 

    with open(filename) as f:        
        G = nx.DiGraph(nx.nx_pydot.read_dot(filename))
        name = (filename.split('/')[-1]).replace('.dot','')
        f.close()
    remove = [node for node,degree in dict(G.degree()).items() if degree == 0]
    G.remove_nodes_from(remove)

    # WRITE TXT
    filename='./misc/benchmark/input/graph' # MUDAR AQUI

    arg1=int(sys.argv[1]) # número de grafos que cabem na rede
    arg2=int(sys.argv[2]) # como eu vou dar nome aos nós
    arg3=int(sys.argv[3]) # número de rodadas

    if arg1 > 256//G.number_of_edges() or arg1<0:
        print(f"Erro: não cabem {arg1} grafos na rede 256x256.")
        sys.exit(0)

    for i in range(arg3):
        if arg2==0:
            name_seq_v2(G,filename+str(i)+".txt",arg1)
        elif arg2==1:
            name_rand_v2(G,filename+str(i)+".txt",arg1)
        elif arg2==2:
            name_rand_v3(G,filename+str(i)+".txt",arg1)
        else:
            print("Erro, não tem função de nomear definida para este id 'arg2'.")

if __name__ == "__main__":
    main()