#!/bin/bash

echo "set off" >> /tmp/delaiPaquet$$

echo "plot \"delaiPaquet.out\" u 1:2 w lp" >> /tmp/delaiPaquet$$
echo "pause -1" >> /tmp/delaiPaquet$$

gnuplot /tmp/delaiPaquet$$


rm /tmp/delaiPaquet$$
