#!/bin/bash

# Parâmetros para dot2txt(gerar entrada da rede)
in_net=$1   # número de grafos na rede (Fir16 são 63 arestas -> cabem 4 grafos na rede: 63*4=252 arestas)
name=$2     # 0: nomeia sequencial, 1: nomeia aleatório
rounds=$3   # número de vezes que eu vou rodar

# Parâmetros para omega.cpp:
declare -i N=256        # número de entrada/saida da rede
declare -i st=4         # número de estágios na rede 
declare -i ex=1         # número de estágios extras na rede
declare -i radix=4      # quantos fios por switchs
declare -i mask=255     # Se N=256, Log2(N)=8 e mask = 1111 1111 

# Gerando entrada
> "./misc/benchmark/txt/Fir16.txt"
filename="./misc/benchmark/txt/Fir16.txt"
command python3 ./src/dot2txt.py $in_net $name $rounds

# Roteando na rede
command g++ ./src/omega.cpp 
res=$(command ./a.out $rounds $N $st $ex $radix $mask  < $filename)

# Saida...
echo -n "Roteou $res% - $in_net grafo(s) "

if (($name == 0)); then 
    echo "- sequêncial."
else 
    echo "- aleatório." 
fi