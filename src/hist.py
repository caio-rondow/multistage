import networkx as nx
import random as rand
import os
import sys
import matplotlib.pyplot as plt
import numpy as np
import pandas as pd


def main():

    filename=sys.argv[1]

    with open(filename, 'r') as f:
        lines = [line.rstrip() for line in f] 
        h = dict(enumerate(list(map(float, lines))))
        f.close()

    source =  pd.DataFrame.from_dict(h,orient='index',columns=['resultado'])
    print(source.describe())

    hist=dict()

    sorted_h=list(h.values())
    sorted_h.sort()    

    for value in sorted_h:
        if value < 69:
            try:
                hist['65-68%']+=1
            except:
                hist['65-68%']=1       

        elif value < 72:
            try:
                hist['69-71%']+=1
            except:
                hist['69-71%']=1
    
        elif value < 75:
            try:
                hist['72-74%']+=1
            except:
                hist['72-74%']=1

        elif value < 78:
            try:
                hist['75-77%']+=1
            except:
                hist['75-77%']=1
        
    print(hist)
    
    df =  pd.DataFrame.from_dict(hist,orient='index',columns=['Roteado'])
    print(df.to_string())

    plt.bar(list(hist.keys()), list(hist.values()))

    plt.title('Histograma 100000 grafos aleatórios')
    plt.xlabel('Roteado (%)')
    plt.ylabel('Quantidade')
    
    plt.show()

if __name__ == "__main__":
    main()