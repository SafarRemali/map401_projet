#!/bin/bash

if [ "$#" -eq "2" ] 
then
    ./ecrire_contour $1.pbm
    ./simplification_segment $1.contour.txt $2
    
else
    echo "usage: ./exec_contour_simp_segment.sh nom_fichier distance_seuil"
fi