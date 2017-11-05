#!/bin/bash

echo "set xlabel \"Temps (en s)\"" >> /tmp/paquetPerdu$$
echo "set ylabel \"Nombre de paquets perdus\"" >> /tmp/paquetPerdu$$
echo "set key off" >> /tmp/paquetPerdu$$

echo "plot \"paquetPerdu.out\" u 1:2 w l" >> /tmp/paquetPerdu$$
echo "pause -1" >> /tmp/paquetPerdu$$

gnuplot /tmp/paquetPerdu$$


rm /tmp/paquetPerdu$$
