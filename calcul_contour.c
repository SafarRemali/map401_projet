#include<stdio.h>
#include "image.h"
#include "calcul_geometrique.h"
#include "calcul_contour.h"
#include "sequence_point.h"
#include "types_macros.h"

void afficher_orientation(Orientation O){
    switch (O)
    {
    case Est:
        printf("E\n");
        break;
    case Ouest:
        printf("O\n");
        break;
    case Sud:
        printf("S\n");
        break;
    case Nord:
        printf("N\n");
        break;
    default:
        printf("WTF\n");
        break;
    }
}

void afficher_point(Point P){
    printf("(%.1lf,%.1lf)",P.x,P.y);
}

Point tete_image(Image I){
    Point p;
    int h=hauteur_image(I);
    int l=largeur_image(I);
 
    for (int y=1; y<=h; y++){
        for (int x=1; x<=l; x++){
            if (get_pixel_image(I,x,y)==NOIR) {
                
                p=set_point((double)(x-1),(double)(y-1));
                return p;
            }
        }
    }
    p=set_point(-1,-1);
    return p;
}

Orientation tourner_a_gauche(Orientation O){
    switch (O)
    {
    case Nord :
        return Ouest ;
    case Sud :
        return Est ;
    case Est :
        return Nord ;
    case Ouest :
        return Sud ;
    }
}

Orientation tourner_a_droit(Orientation O){

    switch (O)
    {
    case Nord :
        return Est ;
    case Sud :
        return Ouest ;
    case Est :
        return Sud ;
    case Ouest :
        return Nord ;
    }
}

Orientation determiner_direction(Image I, Point P, Orientation O){

    Pixel pg,pd;
    
    switch (O)
    {
        case Est:
            pg=get_pixel_image(I,(int)(P.x+1),(int)(P.y));
            pd=get_pixel_image(I,(int)(P.x+1),(int)(P.y+1));
            break;

        case Ouest:
            pg=get_pixel_image(I,(int)(P.x),(int)(P.y+1));
            pd=get_pixel_image(I,(int)(P.x),(int)(P.y));
            break;

        case Nord:
            pg=get_pixel_image(I,(int)(P.x),(int)(P.y));
            pd=get_pixel_image(I,(int)(P.x+1),(int)(P.y));
            break;

        case Sud:
            pg=get_pixel_image(I,(int)(P.x+1),(int)(P.y+1));
            pd=get_pixel_image(I,(int)(P.x),(int)(P.y+1));
            break;
    }

    if(pg==BLANC && pd==BLANC) return tourner_a_droit(O);
    if(pg==NOIR ) return tourner_a_gauche(O);
    return O;
}

void avancer(Image I, Point *P, Orientation O){
    switch (O)
    {
    case Nord :
        P->y = P->y - 1;
        break;
    case Sud :
        P->y = P->y +1;
        break;
    case Est :
        P->x = P->x +1;
        break;
    case Ouest :
        P->x = P->x -1;
        break;
    }
}

Liste_Point liste_contour(Image I,Image m){
    
    Liste_Point L=creer_liste_Point_vide();
    Point tete=tete_image(m);
    Point p=tete;
    Orientation O=Est;

    if (tete.x==-1 && tete.y==-1) {
        return L;
    }

    L=ajouter_element_liste_Point(L,tete);
    set_pixel_image(m,(int)(tete.x)+1,(int)(tete.y)+1,BLANC);
    
    O=determiner_direction(I,p,O);
    if(O==Est){ set_pixel_image(m,(int)(p.x)+1,(int)(p.y)+1,BLANC);}
    avancer(I,&p,O);
    L=ajouter_element_liste_Point(L,p);

    while(p.x!=tete.x || p.y!=tete.y){
        O=determiner_direction(I,p,O);
        if(O==Est) set_pixel_image(m,(int)(p.x)+1,(int)(p.y)+1,BLANC);
        avancer(I,&p,O);
        L=ajouter_element_liste_Point(L,p); 
    }
    return L;
}

int calcul_contour(Liste_Point L){
    Tableau_Point TP = sequence_points_liste_vers_tableau(L);
    printf("%d\n",TP.taille-1);

    return TP.taille-1;
}

void ecrire_contour(Liste_Point L){

	Tableau_Point TP = sequence_points_liste_vers_tableau(L);
	int k;
	int nP = TP.taille;

	printf("%d points : [", nP);
	for (k = 0; k < nP; k++)
	{	
		Point P = TP.tab[k]; 
		afficher_point(P);
	} 
	printf("]\n");
	
	free(TP.tab); 
}


int nombre_contour(Image I, Image J){
    int contour=0;
    Liste_Point l=liste_contour(I,J);
    while(l.taille!=0){
        contour++;
        l=liste_contour(I,J);
    }
    return contour;
}
