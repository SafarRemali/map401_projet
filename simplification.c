#include "image.h"
#include "calcul_geometrique.h"
#include "sequence_point.h"
#include "types_macros.h"
#include "simplification.h"
#include <math.h>


Liste_Point lire_contour(FILE *f,int n){

    Liste_Point L=creer_liste_Point_vide();
    
    Point P;
    double x,y;
    
    for(int i=0; i<n; i++){
        fscanf(f,"%lf ",&x);
        fscanf(f,"%lf ",&y);
        P=set_point(x,y);
        L=ajouter_element_liste_Point(L,P); 
    }
    
    return L;
}


Liste_Point simplification_contour(Tableau_Point CONT, int j1, int j2, double d){

    Point A,B;
    //Tableau_Point TP=sequence_points_liste_vers_tableau(CONT);
    Liste_Point L=creer_liste_Point_vide();

    A=CONT.tab[j1];
    B=CONT.tab[j2];

    double dj,dmax=0;
    int k=j1;


    for(int j=j1+1; j<j2; j++){
        dj=distance_point_segment(A,B,CONT.tab[j]);
        if(dmax<dj){
            dmax=dj;
            k=j;
        }
    }

    //free(TP.tab);
    //TP.taille=0;

    if(dmax<=d){
        L=ajouter_element_liste_Point(L,A); 
    }
    else{
        Liste_Point L1=simplification_contour(CONT, j1, k, d);
        Liste_Point L2=simplification_contour(CONT, k, j2, d);
        L=concatener_liste_Point(L1,L2);
        //printf("%d\n",L.taille);
    }
   return L;
    
}

Bezier2 approx_bezier2(Tableau_Point TP, int j1, int j2){
    Bezier2 C;
    int n = j2 - j1;

    C.C0 = TP.tab[j1];
    C.C2 = TP.tab[j2];

    if(n==1){
       C.C1.x = (C.C0.x + C.C2.x)/2. ;
        C.C1.y = (C.C0.y + C.C2.y)/2. ;
        return C;
    }
    
    double a,b;
    double N=(double)n;
    a = 3*N/(pow(N,2)-1);
    b = (1-2*N)/(2*(N+1));

    Point P=set_point(0,0);

    for(int i=1; i<n; i++){
        P=add_point(P,TP.tab[j1+i]);
    }
    P = produit_point_scalaire(P,a);
    Point Q = add_point(C.C0 , C.C2);
    Q = produit_point_scalaire(Q,b);
    C.C1 = add_point(P,Q);
    return C;
}


Liste_Point simplification_Bezier2(Liste_Point CONT, int j1, int j2, double d){

    int n=j2-j1;
    Tableau_Point TP=sequence_points_liste_vers_tableau(CONT);
    Liste_Point L=creer_liste_Point_vide();
    Bezier2 B=approx_bezier2(TP,j1,j2);

    double dmax=0;
    int k=j1;


    for(int j=j1+1; j<j2; j++){
        int i = j - j1;
        double ti= (double)i/(double)n;
        double dj = distance_deg2(B,TP.tab[j],ti);
        if(dmax<dj){
            dmax=dj;
            k=j;
        }
    }
    free(TP.tab);
    TP.taille=0;

    if(dmax<=d){
        L=ajouter_element_liste_Point(L,B.C0);
        L=ajouter_element_liste_Point(L,B.C1); 
        L=ajouter_element_liste_Point(L,B.C2);
    }
    else{
        Liste_Point L1=simplification_Bezier2(CONT, j1, k, d);
        Liste_Point L2=simplification_Bezier2(CONT, k, j2, d);
        L=concatener_liste_Point(L1,L2);
    }
   return L;
}


Bezier3 approx_bezier3(Tableau_Point TP, int j1, int j2){
    Bezier3 C;
    int n = j2 - j1;

    C.C0 = TP.tab[j1];
    C.C3 = TP.tab[j2];

    if(n<3){
        Bezier2 B=approx_bezier2(TP,j1,j2);
        return conversion_deg2_deg3(B);
    }
    
    double a,b,l;
    double N=(double)n;
    a = (-15*pow(N,3.) + 5*pow(N,2.) + 2*N + 4)/(3*(N + 2)*(3*pow(N,2.) + 1));
    b = (10*pow(N,3.)-15*pow(N,2) + N + 2)/(3*(N+2)*(3*pow(N,2) + 1));
    l = 70*N / (3*(pow(N,2) - 1)*(pow(N,2) - 4)*(3*pow(N,2) + 1));

    Point P1 = set_point(0,0);
    Point P2 = set_point(0,0);

    for(int k=1; k<n; k++){
        double K = (double)k;
        double g = 6*pow(K,4.) - 8*N*pow(K,3.) + 6*pow(K,2) - 4*N*K + pow(N,4.) - pow(N,2);
        Point Q = produit_point_scalaire( TP.tab[j1+k] , g );
        P1=add_point(P1,Q) ;
    }

    for(int k=1; k<n; k++){
        double K = (double)(n-k);
        double g = 6*pow(K,4.) - 8*N*pow(K,3.) + 6*pow(K,2) - 4*N*K + pow(N,4.) - pow(N,2);
        Point Q = produit_point_scalaire( TP.tab[j1+k] , g );
        P2=add_point(P2,Q) ;
    }

    
    C.C1=add_point(produit_point_scalaire(C.C0,a),produit_point_scalaire(P1,l));
    C.C1=add_point(C.C1,produit_point_scalaire(C.C3,b));

    C.C2=add_point(produit_point_scalaire(C.C0,b),produit_point_scalaire(P2,l));
    C.C2=add_point(C.C2,produit_point_scalaire(C.C3,a));

    return C;
}


Liste_Point simplification_Bezier3(Liste_Point CONT, int j1, int j2, double d){

    int n=j2-j1;
    Tableau_Point TP=sequence_points_liste_vers_tableau(CONT);
    Liste_Point L=creer_liste_Point_vide();
    Bezier3 B=approx_bezier3(TP,j1,j2);

    double dmax=0;
    int k=j1;


    for(int j=j1+1; j<j2; j++){
        int i = j - j1;
        double ti= (double)i/(double)n;
        double dj = distance_deg3(B,TP.tab[j],ti);
        if(dmax<dj){
            dmax=dj;
            k=j;
        }
    }
    free(TP.tab);
    TP.taille=0;

    if(dmax<=d){
        L=ajouter_element_liste_Point(L,B.C0);
        L=ajouter_element_liste_Point(L,B.C1); 
        L=ajouter_element_liste_Point(L,B.C2);
    }
    else{
        Liste_Point L1=simplification_Bezier3(CONT, j1, k, d);
        Liste_Point L2=simplification_Bezier3(CONT, k, j2, d);
        L=concatener_liste_Point(L1,L2);
    }
   return L;
    
}