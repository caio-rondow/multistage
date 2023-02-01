import networkx as nx
import random as rand
import os
import sys
import matplotlib.pyplot as plt
import numpy as np
import pandas as pd


def main():

    filename=sys.argv[1]
    ex = sys.argv[2]
    rounds = sys.argv[3]
    in_net = sys.argv[4]
    graphname=sys.argv[5].split('.')[0]

    # Read the .txt file and store the values in a list
    with open(filename) as f:
        values = f.readlines()
    values = [float(x.strip()) for x in values]

    # printing info...
    print()
    print(pd.DataFrame(values).value_counts())
    print(pd.DataFrame(values).describe())

    # Create a histogram using the values
    n, bins, patches = plt.hist(values, bins=11, histtype='bar', edgecolor='black', linewidth=1.2)
    hist, bin_edges = np.histogram(values, bins=11)
    plt.xticks(bin_edges[:-1] + (bin_edges[1] - bin_edges[0])/2)

    # Add labels to the top of each bar
    for i in range(len(patches)):
        patch = patches[i]
        patch_height = patch.get_height()
        plt.annotate(str(int(patch_height)), 
                    (patch.get_x() + patch.get_width()/2., patch_height), 
                    ha='center', va='center', xytext=(0, 10), 
                    textcoords='offset points')
        
    plt.xlabel('% roteada')
    plt.ylabel('frequencia')
    plt.title(f'Rotulamento aleatorio - {ex} extra')
    
    figure = plt.gcf()  
    figure.set_size_inches(12,10)

    path = "misc/results/histograms/"+rounds+"aleatorio"
    
    if not os.path.exists(path):
        os.makedirs(path)
    
    plt.savefig(f"{path}/{in_net}{graphname}_{ex}ex.png", dpi=300, bbox_inches='tight')
    #plt.show()


if __name__ == "__main__":
    main()