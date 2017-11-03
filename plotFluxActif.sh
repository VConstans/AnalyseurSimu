#!/bin/bash

echo "set off" >> /tmp/fluxActif$$

echo "plot \"fluxActif.out\" u 1:2 w lp" >> /tmp/fluxActif$$
echo "pause -1" >> /tmp/fluxActif$$

gnuplot /tmp/fluxActif$$


rm /tmp/fluxActif$$
