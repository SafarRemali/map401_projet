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

    int val1=0, val2=0;

    if(argc!=3){
        printf("Nombre d'argument invalide\n");
        printf("usage: ./simplification_segment <nom_fichier.contour.txt> <distance seuil> \n");
        return 1;
    }

    fcontour=fopen(argv[1],"r");
    sscanf(argv[2],"%lf",&d);
    
    strcpy(nom_fichier, argv[1]);
    nom_fichier[strlen(nom_fichier)-12]='\0';
    strcat(nom_fichier, "_");
    strcat(nom_fichier,argv[2]);
    strcat(nom_fichier, "_simple.eps");
    fsimp=fopen(nom_fichier,"w");

    fscanf(fcontour,"%d %d",&l,&h);
    
    fprintf(fsimp,"%c!PS-Adobe-3.0 EPSF-3.0\n",'%');
    fprintf(fsimp,"%c%cBoundingBox: 0 0 %d %d\n",'%','%',l,h);

    fscanf(fcontour,"%d ",&nb_contour);

    for(int i=0; i<nb_contour; i++){

        fscanf(fcontour,"%d",&n);

        val1 = val1 + n-1;

        CONT=lire_contour(fcontour,n);
        Tableau_Point TC=sequence_points_liste_vers_tableau(CONT);
        //L=simplification_contour(CONT,0,CONT.taille-1,d);
        L=simplification_contour(TC,0,TC.taille-1,d);
        L=ajouter_element_liste_Point(L,L.first->data);
        TP=sequence_points_liste_vers_tableau(L);

        val2 = val2 + TP.taille -1 ;

        Point P=TP.tab[0];
        fprintf(fsimp,"%d %d moveto\n",(int)P.x,(h-(int)P.y));

        for(int j=1; j<TP.taille; j++){
            P = TP.tab[j];
            fprintf(fsimp,"%d %d lineto\n",(int)P.x,(h-(int)P.y));
        }
        CONT = supprimer_liste_Point(CONT);
        L = supprimer_liste_Point(L);
        free(TP.tab);
        TP.taille = 0;
    }
    fprintf(fsimp,"fill showpage \n");

    //printf("nombre de segment initial : %d\n",val1);

    printf("simplification segment d = %.1lf : %d\n",d,val2);

    fclose(fsimp);
    fclose(fcontour);
    return 0;
}