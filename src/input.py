import networkx as nx
import random as rand
import os
import sys

def name_rand(G,filename,arg1):
    with open(filename, 'a') as f:
        f.write(str(G.number_of_edges()*arg1)+"\n")
        name=list(range(0,256))
        for it in range(arg1):
            label=dict()
            _str=""
            for edge in G.edges():
                if edge[0] not in label: 
                    item=rand.choice(name)
                    label[edge[0]]=item
                    name.remove(item)
                if edge[1] not in label:
                    item=rand.choice(name)
                    label[edge[1]]=item
                    name.remove(item)
                _str+=str(label[edge[0]])+" "+str(label[edge[1]])+"\n"
            f.write(_str)
        f.close()

def name_seq(G,filename,arg1):
    with open(filename, 'w') as f:
        f.write(str(G.number_of_edges()*arg1)+"\n")
        label=dict()
        name=0
        for it in range(arg1):
            _str=""
            for edge in G.edges():
                if edge[0] not in label: 
                    label[edge[0]]=name
                    name+=1
                if edge[1] not in label:
                    label[edge[1]]=name
                    name+=1
                _str+=str(label[edge[0]])+" "+str(label[edge[1]])+"\n"
            f.write(_str)
        f.close()

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
    with open(filename, 'a') as f:
        f.write(str(G.number_of_edges()*arg1)+"\n")

        labels1=list(range(0,64))
        labels2=[list(range(64,128)), list(range(128, 192))]
        
        for it in range(arg1):
            label=dict()
            visited=[]
            _str=""
        
            for node in G.nodes():
                if G.in_degree(node)<=1:
                    ct+=1
                    name=rand.choice(labels1)
                    label[node]=name
                    labels1.remove(name)
                else:
                    ct+=1
                    name=rand.choice(labels2[0])
                    label[node]=name
                    labels2[0].remove(name)

            for u,v in G.edges():

                if v not in visited:
                    visited.append(v)
                else:
                    ct+=1
                    name=rand.choice(labels2[1])
                    label.update({v:name})
                    labels2[1].remove(name)

                _str+=str(label[u])+" "+str(label[v])+"\n"
            f.write(_str)
        f.close()

def main():

    # READ DOT
    filename='./misc/benchmark/dot/'+sys.argv[4] # MUDAR AQUI

    with open(filename) as f:        
        G = nx.DiGraph(nx.nx_pydot.read_dot(filename))
        name = (filename.split('/')[-1]).replace('.dot','')
        f.close()
    remove = [node for node,degree in dict(G.degree()).items() if degree == 0]
    G.remove_nodes_from(remove)

    # WRITE TXT
    filename='./misc/benchmark/input/graph.txt' # MUDAR AQUI

    arg1=int(sys.argv[1]) # número de grafos que cabem na rede
    arg2=int(sys.argv[2]) # como eu vou dar nome aos nós
    arg3=int(sys.argv[3]) # número de rodadas

    if arg1 > 256//G.number_of_edges() or arg1<0:
        print(f"Erro: não cabem {arg1} grafos na rede 256x256.")
        sys.exit(0)

    for i in range(arg3):
        if arg2==0:
            name_seq(G,filename,arg1)
        elif arg2==1:
            name_rand(G,filename,arg1)
        elif arg2==2:
            name_seq_v2(G,filename,arg1)
        elif arg2==3:
            name_rand_v2(G,filename,arg1)
        else:
            print("Erro, não tem função de nomear definida para este id 'arg2'.")

if __name__ == "__main__":
    main()