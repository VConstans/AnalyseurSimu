#!/bin/bash

echo "plot \"paquetTransit.out\" u 1:2 w l" >> /tmp/paquetTransit$$
echo "pause -1" >> /tmp/paquetTransit$$

gnuplot /tmp/paquetTransit$$


rm /tmp/paquetTransit$$
