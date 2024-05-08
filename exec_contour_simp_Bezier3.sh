#!/bin/bash

if [ "$#" -eq "2" ] 
then
    ./ecrire_contour $1.pbm
    ./simplification_bezier3 $1.contour.txt $2
    
else
    echo "usage: ./exec_contour_simp_Bezier3.sh nom_fichier distance_seuil"
fi