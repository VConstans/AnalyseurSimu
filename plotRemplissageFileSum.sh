#!/bin/bash

echo "set key outside" >> /tmp/remplissageFile$$

echo "plot \"remplissageFile.out\" u 1:2 w lp" >> /tmp/remplissageFile$$
echo "pause -1" >> /tmp/remplissageFile$$

gnuplot /tmp/remplissageFile$$


rm /tmp/remplissageFile$$
