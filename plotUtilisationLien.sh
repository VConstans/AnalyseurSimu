#!/bin/bash

echo "set key off" >> /tmp/utilisationLien$$
echo "set style fill solid border -1" >> /tmp/utilisationLien$$
echo "set ylabel \"Temps d'utilisation des liens (en s)\"" >> /tmp/utilisationLien$$
echo "set xlabel \"Liens\"" >> /tmp/utilisationLien$$

echo "plot \"utilisationLien.out\" u 1:2 w boxes notitle" >> /tmp/utilisationLien$$
echo "pause -1" >> /tmp/utilisationLien$$

gnuplot /tmp/utilisationLien$$


rm /tmp/utilisationLien$$
