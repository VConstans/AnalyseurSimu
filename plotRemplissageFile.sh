#!/bin/bash

i=2


#while [ $i -le 5 ]
#do
#	if [ $i -eq 2 ]
#	then
#		echo "plot \"remplissageFile.out\" u 1:$i w lp" >> /tmp/remplissageFile$$
#		i=$(($i+1))
#	else
#		echo "replot \"remplissageFile.out\" u 1:$i w lp" >> /tmp/remplissageFile$$
#		i=$(($i+1))
#	fi
#done
echo "plot \"remplissageFile.out\" u 1:28 w l" >> /tmp/remplissageFile$$
echo "pause -1" >> /tmp/remplissageFile$$

gnuplot /tmp/remplissageFile$$


rm /tmp/remplissageFile$$
