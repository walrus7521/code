#!/bin/bash 


# ╔═════════════════╦════════════════════════════════════════╗
# ║ Syntax          ║ Result                                 ║
# ╠═════════════════╬════════════════════════════════════════╣
# ║ arr=()          ║ Create empty array                     ║
# ║ arr=(1 2 3)     ║ Initialize array                       ║
# ║ ${arr[2]}       ║ Retrieve third element                 ║
# ║ ${arr[@]}       ║ Retrieve all elements                  ║
# ║ ${!arr[@]}      ║ Retrieve array indices                 ║
# ║ ${#arr[@]}      ║ Calculate array size                   ║
# ║ arr[0]=3        ║ Overwrite 1st element                  ║
# ║ arr+=(4)        ║ Append value(s)                        ║
# ║ str=$(ls)       ║ Save ls output as string               ║
# ║ arr=( $(ls) )   ║ Save ls output as array of files       ║
# ║ ${arr[@]:s:n}   ║ Elements at indices n to s+n           ║
# ║ ${str//ab/c}    ║ For a given string, replace ab with c  ║
# ║ ${arr[@]//ab/c} ║ For each array item, replace ab with c ║
# ╚═════════════════╩════════════════════════════════════════╝

counter=0
while [  $counter -lt 10 ]; do
    echo The counter is $counter
    let counter=counter+1 
done

n=10
for ((i=1; i<=n; i++)) {
    printf '<process>value="%d"</process>\n' $i
}


for i in $( ls ); do
    echo item: $i
done

allThreads=(1 2 4 8 16 32 64 128)
myArray=(1 2 "three" 4 "five")

for t in ${allThreads[@]}; do
    printf 'dude: %d => "%d"\n' $t $t
done




