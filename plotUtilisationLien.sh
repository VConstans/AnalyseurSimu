#!/bin/bash

echo "set key off" >> /tmp/utilisationLien$$

i=1
nbLigne=`wc -l utilisationLien.out | cut -d " " -f 1`

echo -n "set xtics(" >> /tmp/utilisationLien$$

while [ $i -le $nbLigne ]
do
	label=`head -n $i utilisationLien.out | tail -n 1 | cut -d " " -f 1`
	echo -n "\"$label\" $((i-1))" >> /tmp/utilisationLien$$

	if [ $i -ne $nbLigne ]
	then
		echo -n "," >> /tmp/utilisationLien$$
	fi
	i=$(($i+1))

done

echo ")" >> /tmp/utilisationLien$$

echo "plot \"utilisationLien.out\" u 1:2 w boxes notitle" >> /tmp/utilisationLien$$
echo "pause -1" >> /tmp/utilisationLien$$

gnuplot /tmp/utilisationLien$$


rm /tmp/utilisationLien$$
