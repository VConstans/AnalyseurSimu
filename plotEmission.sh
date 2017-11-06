#!/bin/bash

echo "set xlabel \"Temps (en s)\"" >> /tmp/emission$$
echo "set ylabel \"Nombre de paquets émis\"" >> /tmp/emission$$
echo "set key off" >> /tmp/emission$$

echo "plot \"emission.out\" u 1:2 w l" >> /tmp/emission$$
echo "pause -1" >> /tmp/emission$$

gnuplot /tmp/emission$$


rm /tmp/emission$$
