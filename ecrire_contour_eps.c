#include<stdio.h>
#include<string.h>
#include "image.h"
#include "calcul_geometrique.h"
#include "calcul_contour.h"
#include "sequence_point.h"

int main(int argc, char ** argv){
    
    FILE *f;
    Image I,J;
    char nom_fichier[100];
    Point P;
    Tableau_Point TP;



    if(argc!=2){
        printf("Nombre d'argument invalide\n");
        printf("usage: ./ecrire_contour_eps <nom_fichier.pbm> \n");
        return 1;
    }
   
    I=lire_fichier_image(argv[1]);
    J=calculer_masque_image(I);

    strcpy(nom_fichier, argv[1]);

    nom_fichier[strlen(nom_fichier)-4]='\0';

    strcat(nom_fichier, ".eps");

    f=fopen(nom_fichier,"w");
    
    fprintf(f,"%c!PS-Adobe-3.0 EPSF-3.0\n",'%');
    fprintf(f,"%c%cBoundingBox: 0 0 %d %d\n",'%','%',I.L,I.H);


    Liste_Point l=liste_contour(I,J);
    while(l.taille!=0){
        
        TP =sequence_points_liste_vers_tableau(l);

        P=TP.tab[0];
        fprintf(f,"%d %d moveto\n",(int)P.x,(I.H-(int)P.y));

        for(int i=1; i<TP.taille; i++){
            P=TP.tab[i];
            fprintf(f,"%d %d lineto\n",(int)P.x,(I.H-(int)P.y));
        }
        free(TP.tab);
        l=supprimer_liste_Point(l);
        l=liste_contour(I,J);
    }

    fprintf(f,"fill ");
    fprintf(f,"showpage \n");
    
    fclose(f);
    return 0;
}