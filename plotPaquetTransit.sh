#!/bin/bash

echo "set xlabel \"Temps (en s)\" ">> /tmp/paquetTransit$$
echo "set ylabel \"Nombre de paquet en transit\" ">> /tmp/paquetTransit$$
echo "set key off">> /tmp/paquetTransit$$

echo "plot \"paquetTransit.out\" u 1:2 w l" >> /tmp/paquetTransit$$
echo "pause -1" >> /tmp/paquetTransit$$

gnuplot /tmp/paquetTransit$$


rm /tmp/paquetTransit$$
