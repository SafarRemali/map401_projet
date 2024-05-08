#!/bin/bash

for i in IMAGES_TESTS/*.pbm
do
    echo $i
    time ./ecrire_contour $i 
    echo " "
done