count=1000
#command python3 dot2txt.py

for FILE in ./results/random/*; do 
    #echo $FILE
    var=$(command ./a.out < $FILE)
    
    echo $var >> values.txt

done 