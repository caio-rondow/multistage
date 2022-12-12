#!/bin/bash

# Parâmetros para dot2txt(gerar entrada da rede)
graph=$1    # grafo que vai ser roteado (.dot)
in_net=$2   # número de grafos na rede (Fir16 são 63 arestas -> cabem 4 grafos na rede: 63*4=252 arestas)
name=$3     # 0: nomeia sequencial, 1: nomeia aleatório
rounds=$4   # número de vezes que eu vou rodar

# Parâmetros para omega.cpp:
declare -i N=256        # número de entrada/saida da rede
declare -i st=4         # número de estágios na rede 
declare -i ex=1         # número de estágios extras na rede
declare -i radix=4      # quantos fios por switchs
declare -i mask=255     # Se N=256, Log2(N)=8 -> mask = 1111 1111 = 255

# Gerando entrada
> "./misc/benchmark/input/graph.txt"
filename="./misc/benchmark/input/graph.txt"
strval="all"

if [ $graph == $strval ]; then

    for FILE in ./misc/benchmark/dot/*; do
        > "./misc/benchmark/input/graph.txt"
        FILE=$(echo $FILE| cut -d'/' -f 5)

        command python3 ./src/input.py $in_net $name $rounds $FILE
        res=$(command ./a.out $rounds $N $st $ex $radix $mask  < $filename)
        echo -n "$FILE |$res|$in_net"

        if (($name == 0)); then 
            echo "|sequencial|$ex"
        elif (($name == 1)); then
            echo "|aleatório|$ex"
        elif (($name == 2)); then
            echo "|T2 sequencial|$ex"
        else
            echo "|T2 aleatório|$ex"
        fi
    done
else 
    command python3 ./src/input.py $in_net $name $rounds "$graph.dot"

    # Roteando na rede
    # command g++ ./src/omega.cpp # Fazer o makefile...
    res=$(command ./a.out $rounds $N $st $ex $radix $mask  < $filename)

    # Saida...
    echo -n "Roteou $res% - $in_net grafo(s) "

    if (($name == 0)); then 
        echo "- sequencial - $ex estágios extras."
    elif (($name == 1)); then
        echo "- aleatório - $ex estágios extras."
    elif (($name == 2)); then
        echo "- T2 sequencial - $ex estágios extras."
    else
        echo "- T2 aleatório - $ex estágios extras."
    fi
fi
