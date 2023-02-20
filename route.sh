# PARAMETERS
declare -i COUNT=0
declare -i N=256
declare -i ST=4
#   IMPORTANT ONES...  #
declare -i TYPE=2      # 0 sequential, 1 random, 2 smart random
declare -i EX=1        # extra stages
declare -i IN_NET=1    # number of graphs in net
declare -i ROUNDS=1    # how much iterations
declare -i TWOTRIPS=1  # 0 two trips off, 1 two trips on
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
    simple.dot
    )
elif [ -e misc/benchmark/dot/"$arg.dot" ]; then
    GRAPH=("$arg.dot")
else
    echo -e "$(tput setaf 1)The graph '$arg' does not belong to ./misc/benchmark/dot directory.$(tput sgr0)"
    echo -e "$(tput setaf 1)Please, check if the corresponding graph is in the folder.$(tput sgr0)"
    exit 1
fi

# max graphs in net
MAX_IN_NET=(
    4	# Cplx8.dot
    3	# FilterRGB.dot
    4	# Fir16.dot
    8	# arf.dot
    9	# conv3.dot
    3	# cosine1.dot
    2	# cosine2.dot
    5	# ewf.dot
    5	# feedback_points.dot
    5	# fir.dot
    5	# fir1.dot
    6	# fir2.dot
    4	# h2v2_smooth.dot
    16	# horner_bezier_surf.dot
    2	# interpolate_aux.dot
    1	# jpeg_fdct_islow.dot
    1	# jpeg_idct_ifast.dot
    3	# k4n4op.dot
    19	# mac.dot
    8	# motion_vectors.dot
    11	# mults1.dot
    18	# simple.dot
)

# run make
command make -s

# network info
echo "Info:"
echo -e "input/output\t$N\nstage(s)\t$ST\nextra(s)\t$EX\nround(s)\t$ROUNDS\nin net\t\tmax graph(s)"
if [ $TYPE -eq 0 ]; then 
    echo -e "label\t\tsequential" 
elif [ $TYPE -eq 1 ]; then 
    echo -e "label\t\trandom"
else
    echo -e "label\tsmart"
fi
echo -e "num. trips\t$(($TWOTRIPS+1))\n"

# RUN CODE HERE
for ((i=0; i < ${#GRAPH[@]}; i++)) do
    # echo "${GRAPH[i]} ok"
    # ./build/apps/program ${GRAPH[i]} $N $ST $EX $TWOTRIPS ${MAX_IN_NET[i]} $ROUNDS $TYPE > misc/values.txt
    # command python3 src/histogram.py misc/values.txt $EX $ROUNDS ${MAX_IN_NET[i]} ${GRAPH[i]}
    
    
    ./build/apps/program ${GRAPH[i]} $N $ST $EX $TWOTRIPS $IN_NET $ROUNDS $TYPE > misc/values.txt
    # command python3 src/histogram.py misc/values.txt $EX $ROUNDS IN_NET ${GRAPH[i]}

done