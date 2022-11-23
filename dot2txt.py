import networkx as nx
import random as rand

def name_sequential(G):
    filename='Fir16_seq.txt'
    
    k=0

    nGrafos = 256//G.number_of_edges()

    with open(filename,'w') as f:
        f.write(str(G.number_of_edges()*nGrafos)+"\n")

        for i in range(nGrafos):
            label=dict()
            a,b=257,0

            for node in G.nodes():

                a = min(a,k)
                b = max(b,k)

                neighbors = list(nx.neighbors(G,node))
                
                if node not in label:
                    label[node]=k
                    k+=1

                for neighbor in neighbors:
                    if neighbor not in label:
                        label[neighbor]=k
                        k+=1
                    _str=str(label[node])+" "+str(label[neighbor])+"\n"
                    
                    f.write(_str)
            #f.write("INTERVAL: ["+str(a)+" "+str(b)+")\n\n")

def name_random(G, filename):

    k=list(range(0,256))

    nGrafos = 256//G.number_of_edges()

    with open(filename,'w') as f:
        f.write(str(G.number_of_edges()*nGrafos)+"\n")

        for i in range(nGrafos):
            
            label=dict()

            for node in G.nodes():
                neighbors = list(nx.neighbors(G,node))
                
                if node not in label:
                    value=rand.choice(k)
                    label[node]=value
                    k.remove(value)
                    
                for neighbor in neighbors:
                    if neighbor not in label:
                        value=rand.choice(k)
                        label[neighbor]=value
                        k.remove(value)

                    _str=str(label[node])+" "+str(label[neighbor])+"\n"
                    
                    f.write(_str)
        #f.write("Sobraram "+str(256-(G.number_of_nodes()*nGrafos))+" nomes.\n")

def main():
    filename='./Fir16.dot'

    with open(filename) as f:        
        G = nx.DiGraph(nx.nx_pydot.read_dot(filename))
        name = (filename.split('/')[-1]).replace('.dot','')
        f.close()
    remove = [node for node,degree in dict(G.degree()).items() if degree == 0]
    G.remove_nodes_from(remove)

    #name_sequential(G)
    for i in range(0,1000):
        filename='./results/random/'+str(i)+"_Fir16.txt"
        name_random(G,filename)

if __name__ == "__main__":
    main()