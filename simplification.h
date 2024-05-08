#ifndef _SIMPLIFICATION
#define _SIMPLIFICATION

#include "image.h"
#include "calcul_geometrique.h"
#include "sequence_point.h"
#include "types_macros.h"

//lis un contour de taille n deouis le fichier *f
Liste_Point lire_contour(FILE *f, int n);

//Liste_Point simplification_contour(Liste_Point CONT, int j1, int j2, double d);

//algorithme de simplification par segments de douglas peucker
Liste_Point simplification_contour(Tableau_Point CONT, int j1, int j2, double d);

//aproxime un tableau de point par une courbe de bezier2
Bezier2 approx_bezier2(Tableau_Point TP, int j1, int j2);

//algorithme de simplification par bezier2 de douglas peucker
Liste_Point simplification_Bezier2(Liste_Point CONT, int j1, int j2, double d);

//aproxime un tableau de point par une courbe de bezier3
Bezier3 approx_bezier3(Tableau_Point TP, int j1, int j2);

//algorithme de simplification par bezier3 de douglas peucker
Liste_Point simplification_Bezier3(Liste_Point CONT, int j1, int j2, double d);

#endif