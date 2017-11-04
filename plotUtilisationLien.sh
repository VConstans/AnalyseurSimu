#!/bin/bash

echo "set off" >> /tmp/utilisationLien$$

echo "plot \"utilisationLien.out\" u 1:2 w lp" >> /tmp/utilisationLien$$
echo "pause -1" >> /tmp/utilisationLien$$

gnuplot /tmp/utilisationLien$$


rm /tmp/utilisationLien$$
