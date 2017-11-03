#!/bin/bash

echo "set off" >> /tmp/paquetTransit$$

echo "plot \"paquetTransit.out\" u 1:2 w lp" >> /tmp/paquetTransit$$
echo "pause -1" >> /tmp/paquetTransit$$

gnuplot /tmp/paquetTransit$$


rm /tmp/paquetTransit$$
