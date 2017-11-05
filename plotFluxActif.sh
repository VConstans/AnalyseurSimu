#!/bin/bash

echo "set key off" >> /tmp/fluxActif$$
echo "set xlabel \"Temps (en s)\"" >> /tmp/fluxActif$$
echo "set ylabel \"Nombre de flux actifs\"" >> /tmp/fluxActif$$

echo "plot \"fluxActif.out\" u 1:2 w l" >> /tmp/fluxActif$$
echo "pause -1" >> /tmp/fluxActif$$

gnuplot /tmp/fluxActif$$


rm /tmp/fluxActif$$
