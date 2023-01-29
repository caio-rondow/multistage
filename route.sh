# PARAMETERS
declare -i COUNT=0
declare -i N=256
declare -i ST=4
#   IMPORTANT ONES...  #
declare -i TYPE=1      # 0 sequential, 1 random
declare -i EX=2        # extra stages
declare -i IN_NET=2    # number of graphs in net
declare -i ROUNDS=1000 # how much iterations
# ==================== #

arg=$1      # simulate a single graph
str="all"   # simulate all graphs

# .dot GRAPHS
if [[ "$#" == 0 || "$arg" == "$str" ]]; then
    GRAPH=(
    Cplx8.dot
    FilterRGB.dot
    Fir16.dot
    arf.dot
    conv3.dot
    cosine1.dot
    cosine2.dot
    ewf.dot
    feedback_points.dot
    fir.dot
    fir1.dot
    fir2.dot
    h2v2_smooth.dot
    horner_bezier_surf.dot
    interpolate_aux.dot
    jpeg_fdct_islow.dot
    jpeg_idct_ifast.dot
    k4n4op.dot
    mac.dot
    motion_vectors.dot
    mults1.dot
    removed_Fir16.dot
    simple.dot
    )
elif [ -e misc/benchmark/dot/"$arg.dot" ]; then
    GRAPH=("$arg.dot")
else
    echo -e "$(tput setaf 1)The graph '$arg' does not belong to ./misc/benchmark/dot directory.$(tput sgr0)"
    echo -e "$(tput setaf 1)Please, check if the corresponding graph is in the folder.$(tput sgr0)"
    exit 1
fi

# run make
make -f makefile -s

# network info
echo "Info:"
echo -e "input/output\t$N\nstage(s)\t$ST\nextra(s)\t$EX\nround(s)\t$ROUNDS\n"

for ((i=0; i < ${#GRAPH[@]}; i++)) do

    echo -e "graph: ${GRAPH[i]}\n"

    # label graph
    command find ./misc/benchmark/input/ -type f -print0 | xargs -0 rm
    command python3 ./src/input.py $IN_NET $TYPE $ROUNDS ${GRAPH[i]}

    # route labeled graphs
    > misc/results/outputs/values.txt
    for FILE in ./misc/benchmark/input/*; do
        command bin/main.out < $FILE $N $ST $EX >> misc/results/outputs/values.txt
        echo "$COUNT"
        COUNT+=1
    done | pv -l -s $ROUNDS > /dev/null

    # create a histogram
    command python3 src/hist.py misc/results/outputs/values.txt $EX $ROUNDS $IN_NET ${GRAPH[i]}
done