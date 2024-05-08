#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include "types_macros.h"
#include "calcul_geometrique.h"

Point set_point (double x, double y){
    Point p;
    p.x = x;
    p.y = y;
    return p;
}

Point add_point (Point P1, Point P2){
    Point p;
    p.x = P1.x + P2.x;
    p.y = P1.y + P2.y;
    return p;
}

Vecteur set_vecteur (double x, double y){
    Vecteur v;
    v.x = x;
    v.y = y;
    return v;
}

Vecteur vect_bipoint (Point A, Point B){
    Vecteur v;
    v.x = B.x - A.x;
    v.y = B.y - A.y;
    return v;
}

Point produit_point_scalaire(Point P, double a){
    Point Q;
    Q.x = a * P.x;
    Q.y = a * P.y;
    return Q;
}

Vecteur add_vecteur (Vecteur V1, Vecteur V2){
    Vecteur v;
    v.x = V1.x + V2.x;
    v.y = V1.y + V2.y;
    return v;
}

double produit_scalaire (Vecteur V1, Vecteur V2){
    return V1.x*V2.x + V1.y*V2.y ;
}

double norme (Vecteur V){
    return sqrt(V.x*V.x + V.y*V.y) ;
}

double distance (Point A, Point B){
    return sqrt((A.x-B.x)*(A.x-B.x) + (A.y-B.y)*(A.y-B.y));
}

double distance_point_segment(Point A, Point B, Point P){
    Vecteur AP=vect_bipoint(A,P);
    Vecteur AB=vect_bipoint(A,B);

    if(norme(AB)==0){
        return norme(AP);
    }

    double l = produit_scalaire(AP,AB)/produit_scalaire(AB,AB);

    if (l<0){
        return norme(AP);
    }
    else if (l>1){
        return norme(vect_bipoint(P,B));
    }
    else {
        Point Q = set_point(A.x+l*(B.x-A.x),A.y+l*(B.y-A.y));
        return norme(vect_bipoint(Q,P));
    }
}

Point calcul_point_bezier2(Bezier2 B, double t){
    double x,y;
    x = B.C0.x * pow(1-t,2) + 2*B.C1.x *t*(1-t) + B.C2.x*pow(t,2) ;
    y = B.C0.y * pow(1-t,2) + 2*B.C1.y *t*(1-t) + B.C2.y*pow(t,2) ;
    Point P=set_point(x,y);
    return P;
}

Point calcul_point_bezier3(Bezier3 B, double t){
    double x,y;
    x = pow(1-t,3)*B.C0.x + 3*t*pow(1-t,2) * B.C1.x + 3*pow(t,2)*(1-t)*B.C2.x + pow(t,3) * B.C3.x ;
    y = pow(1-t,3)*B.C0.y + 3*t*pow(1-t,2) * B.C1.y + 3*pow(t,2)*(1-t)*B.C2.y + pow(t,3) * B.C3.y ;
    Point P=set_point(x,y);
    return P;
}

Bezier3 conversion_deg2_deg3(Bezier2 B){
    Bezier3 C;
    C.C0 = B.C0 ;
    Point Q = produit_point_scalaire(B.C1,2.);
    Q = add_point(B.C0,Q);
    C.C1 = produit_point_scalaire(Q,1./3.) ;
    C.C2 = produit_point_scalaire(add_point(B.C2,produit_point_scalaire(B.C1,2.)),1./3.);
    C.C3 = B.C2 ;
    return C;
}

double distance_deg2(Bezier2 B, Point P, double t){
    Point Q=calcul_point_bezier2(B,t);
    return distance(P,Q);
}

double distance_deg3(Bezier3 B, Point P, double t){
    Point Q=calcul_point_bezier3(B,t);
    return distance(P,Q);
}