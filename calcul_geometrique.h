#ifndef _CALCUL_GEOMETRIQUE
#define _CALCUL_GEOMETRIQUE

#include"types_macros.h"

typedef struct Vecteur_ {
    double x,y;
} Vecteur;

typedef struct Point_ {
    double x,y;
} Point;

typedef struct Bezier2_ {
    Point C0;
    Point C1;
    Point C2;
} Bezier2;

typedef struct Bezier3_ {
    Point C0;
    Point C1;
    Point C2;
    Point C3;
} Bezier3;

// cree le point de coordonee (x,y)
Point set_point (double x, double y);

//somme de P1 et P2
Point add_point (Point P1, Point P2);

//cree le vecteur (x,y)
Vecteur set_vecteur (double x, double y);

// vecteur correspondant au bipoint AB
Vecteur vect_bipoint (Point A, Point B);

//produit point scalaire
Point produit_point_scalaire(Point P, double a);

//somme de V1 et V2
Vecteur add_vecteur (Vecteur V1, Vecteur V2);

//produit scalaire V1 et V2
double produit_scalaire (Vecteur V1, Vecteur V2);

//renvoie la norme de V 
double norme (Vecteur V);

//calcule la distance entre A et B
double distance (Point A, Point B);

//calcule la distance entre un point et un segment
double distance_point_segment(Point A, Point B, Point P);

//calcule du point B(ti)
Point calcul_point_bezier2(Bezier2 B, double t);

//calcule du point B(ti)
Point calcul_point_bezier3(Bezier3 B, double t);

//conversion d'une courbe de degre 2 vers degre 3
Bezier3 conversion_deg2_deg3(Bezier2 B);

//distance point courbe 
double distance_deg2(Bezier2 B, Point P, double t);

//distance point courbe 
double distance_deg3(Bezier3 B, Point P, double t);

#endif /* _CALCUL_GEOMETRIQUE_H_ */
