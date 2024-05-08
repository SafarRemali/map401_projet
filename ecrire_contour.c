#include<stdio.h>
#include<string.h>
#include "image.h"
#include "calcul_geometrique.h"
#include "calcul_contour.h"
#include "sequence_point.h"

int main(int argc, char ** argv){
    
    FILE *f;
    Image I,J,i,j;
    char nom_fichier[100];
    Point P;
    Tableau_Point TP;
    int cont,seg;



    if(argc!=2){
        printf("Nombre d'argument invalide\n");
        printf("usage: ./ecrire_contour <nom_fichier.pbm> \n");
        return 1;
    }
   
    I=lire_fichier_image(argv[1]);
    J=calculer_masque_image(I);

    i=lire_fichier_image(argv[1]);
    j=calculer_masque_image(I);

    strcpy(nom_fichier, argv[1]);
    nom_fichier[strlen(nom_fichier)-4]='\0';
    strcat(nom_fichier, ".contour.txt");
    f=fopen(nom_fichier,"w");
    
    fprintf(f,"%d %d\n",I.L,I.H);

    cont=nombre_contour(i,j);
    fprintf(f,"%d\n\n",cont);
    printf("contour %d\n",cont);
    supprimer_image(&i);
    supprimer_image(&j);

    Liste_Point l=liste_contour(I,J);
    seg=0;
    while(l.taille!=0){
        TP.taille=0;
        TP =sequence_points_liste_vers_tableau(l); // modifie ici afin de reduire le temp d'excution
        fprintf(f,"%d\n",TP.taille);
        seg = seg + TP.taille;

        for(int k=0; k<TP.taille; k++){
            P=TP.tab[k];
            fprintf(f,"%.1lf %.1lf\n",P.x,P.y);
        }
        fprintf(f,"\n");
        l=supprimer_liste_Point(l);
        l=liste_contour(I,J);
    }

    printf("segment %d\n",seg);
    supprimer_image(&I);
    supprimer_image(&J);

    fclose(f);
    return 0;
}