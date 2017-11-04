#!/bin/bash

echo "set key off" >> /tmp/utilisationLien$$

echo "plot \"utilisationLien.out\" u 1:2 w boxes notitle" >> /tmp/utilisationLien$$
echo "pause -1" >> /tmp/utilisationLien$$

gnuplot /tmp/utilisationLien$$


rm /tmp/utilisationLien$$
