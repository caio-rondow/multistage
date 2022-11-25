#!/bin/bash

arg1=$1 # Fir16 são 63 arestas -> cabem 4 grafos na rede: 63*4=252 arestas
arg2=$2 # 0: nomeia sequencial, 1: nomeia aleatório
filename="./misc/benchmark/txt/Fir16.txt"

command python3 ./src/dot2txt.py $arg1 $arg2
#command g++ ./src/omega.cpp 
res=$(command ./a.out < $filename)

echo -n "Roteou $res% - $arg1 grafo(s) "

if (($arg2 == 0)); then 
    echo "- sequêncial."
else 
    echo "- aleatório." 
fi