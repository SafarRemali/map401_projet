#include<stdio.h>
#include<string.h>

#include "simplification.h" 
#include "image.h"
#include "calcul_geometrique.h"
#include "sequence_point.h"

int main(int argc, char** argv ){
    FILE *fcontour;
    FILE *fsimp;
    char nom_fichier[150];
    int nb_contour,n;
    Liste_Point CONT,L;
    Tableau_Point TP;
    double d;
    int l,h;
    int seg=0;

    if(argc!=3){
        printf("Nombre d'argument invalide\n");
        printf("usage: ./simplification_bezier2 <nom_fichier.contour.txt> <distance seuil> \n");
        return 1;
    }

    fcontour=fopen(argv[1],"r");
    sscanf(argv[2],"%lf",&d);
    
    strcpy(nom_fichier, argv[1]);
    nom_fichier[strlen(nom_fichier)-12]='\0';
    strcat(nom_fichier, "_");
    strcat(nom_fichier,argv[2]);
    strcat(nom_fichier, "_bezier2.eps");
    fsimp=fopen(nom_fichier,"w");

    fscanf(fcontour,"%d %d",&l,&h);
    
    fprintf(fsimp,"%c!PS-Adobe-3.0 EPSF-3.0\n",'%');
    fprintf(fsimp,"%c%cBoundingBox: 0 0 %d %d\n",'%','%',l,h);

    fscanf(fcontour,"%d ",&nb_contour);

    for(int i=0; i<nb_contour; i++){

        fscanf(fcontour,"%d",&n);

        CONT=lire_contour(fcontour,n);
        L=simplification_Bezier2(CONT,0,CONT.taille-1,d);
        L=ajouter_element_liste_Point(L,L.first->data);
        TP=sequence_points_liste_vers_tableau(L);

        Bezier2 C;
        C.C0 = TP.tab[0];
        fprintf(fsimp,"%.1lf %.1lf moveto\n",C.C0.x,(double)h-C.C0.y);


        int j=0;
        while(j<TP.taille-1){
            
            C.C1=TP.tab[j+1]; C.C2=TP.tab[j+2];
            Bezier3 B = conversion_deg2_deg3(C);
            fprintf(fsimp,"%.1lf %.1lf  %.1lf %.1lf  ",B.C1.x,(double)h-B.C1.y,B.C2.x,(double)h-B.C2.y);
            fprintf(fsimp,"%.1lf %.1lf curveto\n",B.C3.x,(double)h-B.C3.y);
            j=j+3;
            C.C0=TP.tab[j];
            seg=seg+1;
        }
        L=supprimer_liste_Point(L);
        free(TP.tab);
        TP.taille=0;
    }
    printf("simplification Bezier2 d = %.1lf : %d\n",d,seg);
    fprintf(fsimp,"fill showpage \n");

    fclose(fsimp);
    fclose(fcontour);

    return 0;
}