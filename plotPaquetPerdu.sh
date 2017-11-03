#!/bin/bash

echo "set off" >> /tmp/paquetPerdu$$

echo "plot \"paquetPerdu.out\" u 1:2 w lp" >> /tmp/paquetPerdu$$
echo "pause -1" >> /tmp/paquetPerdu$$

gnuplot /tmp/paquetPerdu$$


rm /tmp/paquetPerdu$$
