#!/bin/bash

i=2
nbColonne=`head -n 1 remplissageFile.out`
nbColonne=$(($nbColonne+1))

echo "set xlabel \"Temps (en s)\"" >> /tmp/remplissageFile$$
echo "set ylabel \"Nombre de paquets\"" >> /tmp/remplissageFile$$

while [ $i -le $nbColonne ]
do
	if [ $i -eq 2 ]
	then
		echo "plot \"remplissageFile.out\" u 1:$i every $1 w l title \"noeud $(($i-1))\"" >> /tmp/remplissageFile$$
		i=$(($i+1))
	else
		echo "replot \"remplissageFile.out\" u 1:$i every $1 w l title \"noeud $(($i-1))\" " >> /tmp/remplissageFile$$
		i=$(($i+1))
	fi
done
echo "pause -1" >> /tmp/remplissageFile$$

gnuplot /tmp/remplissageFile$$


rm /tmp/remplissageFile$$
