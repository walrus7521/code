#!/bin/bash 

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


