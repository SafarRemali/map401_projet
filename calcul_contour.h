#ifndef _CALCUL_CONTOUR
#define _CALCUL_CONTOUR

#include "image.h"
#include "calcul_geometrique.h"
#include "sequence_point.h"
#include "types_macros.h"


typedef enum {Nord ,Est ,Sud ,Ouest } Orientation;

//ecrit le point P a l'ecran
void afficher_point(Point p);

//renvoie le sommet gauche du premier pixiel noir, (-1,-1) si l'image est vide
Point tete_image(Image I);

//determine l'orientation suivante en fonction de l'orientation actuelle
Orientation tourner_a_gauche(Orientation O);

//determine l'orientation suivante en fonction de l'orientation actuelle
Orientation tourner_a_droit(Orientation O);

//traite les cas de répartition des pixel pour determiner le chemin correcte
Orientation determiner_direction(Image I, Point P, Orientation O);

//modifie le point P en fonction de l'orientation et de la répartition des pixels 
void avancer(Image I, Point *P, Orientation O);

//calcule un contour d'une image en fonction du masque et modifie l'image masque en consequence
Liste_Point liste_contour(Image I, Image m);

//renvoie le nombre de segment d'un contour L
int calcul_contour(Liste_Point L);

//ecrit le contour dans L a l'ecran
void ecrire_contour(Liste_Point L);

//renvoie le nombre de contour dans une image
int nombre_contour(Image I, Image J);

#endif