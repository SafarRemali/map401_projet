#############################################################################
# Fichier Makefile 
# UE MAP401 - DLST - UGA - 2020/2021
#############################################################################
# utilisation des variables internes $@ $< $^ $*
# $@ : correspond au nom de la cible
# $< : correspond au nom de la premiere dependance
# $^ : correspond � toutes les d�pendances
# $* : correspond au nom du fichier sans extension 
#       (dans les regles generiques uniquement)
#############################################################################
# information sur la regle executee avec la commande @echo
# (une commande commancant par @ n'est pas affichee a l'ecran)
#############################################################################


#############################################################################
# definition des variables locales
#############################################################################

# compilateur C
CC = clang

# chemin d'acces aux librairies (interfaces)
INCDIR = .

# chemin d'acces aux librairies (binaires)
LIBDIR = .

# options pour l'�dition des liens
LDOPTS = -L$(LIBDIR) -lm

# options pour la recherche des fichiers .o et .h
INCLUDEOPTS = -I$(INCDIR)

# options de compilation
COMPILOPTS = -g -Wall $(INCLUDEOPTS)

# liste des executables
EXECUTABLES = ecrire_contour ecrire_contour_eps simplification_segment simplification_bezier2 simplification_bezier3 visible


#############################################################################
# definition des regles
#############################################################################

########################################################
# la régle par défaut
all : $(EXECUTABLES)

########################################################
# regle generique : 
#  remplace les regles de compilation separee de la forme
#	module.o : module.c module.h
#		$(CC) -c $(COMPILOPTS) module.c
%.o : %.c %.h
	@echo ""
	@echo "---------------------------------------------"
	@echo "Compilation du module "$*
	@echo "---------------------------------------------"
	$(CC) -c $(COMPILOPTS) $<

########################################################
# regles explicites de compilation separee de modules
# n'ayant pas de fichier .h ET/OU dependant d'autres modules
image.o : image.c image.h types_macros.h
	@echo ""
	@echo "---------------------------------------------"
	@echo "Compilation du module image"
	@echo "---------------------------------------------"
	$(CC) -c $(COMPILOPTS) $<

calcul_geometrique.o : calcul_geometrique.c calcul_geometrique.h types_macros.h
	@echo ""
	@echo "---------------------------------------------"
	@echo "Compilation du module calcul_geometrique"
	@echo "---------------------------------------------"
	$(CC) -c $(COMPILOPTS) $<

sequence_point.o : sequence_point.c sequence_point.h calcul_geometrique.h
	@echo ""
	@echo "---------------------------------------------"
	@echo "Compilation du module sequence_point"
	@echo "---------------------------------------------"
	$(CC) -c $(COMPILOPTS) $<

calcul_contour.o : calcul_contour.c calcul_contour.h calcul_geometrique.h image.h sequence_point.h types_macros.h
	@echo ""
	@echo "---------------------------------------------"
	@echo "Compilation du module calcul_contour"
	@echo "---------------------------------------------"
	$(CC) -c $(COMPILOPTS) $<

simplification.o : simplification.c simplification.h calcul_geometrique.h image.h sequence_point.h types_macros.h
	@echo ""
	@echo "---------------------------------------------"
	@echo "Compilation du module simplification"
	@echo "---------------------------------------------"
	$(CC) -c $(COMPILOPTS) $<

ecrire_contour.o : ecrire_contour.c calcul_contour.h calcul_geometrique.h image.h sequence_point.h
	@echo ""
	@echo "---------------------------------------------"
	@echo "Compilation du module ecrire_contour"
	@echo "---------------------------------------------"
	$(CC) -c $(COMPILOPTS) $<		

ecrire_contour_eps.o : ecrire_contour_eps.c calcul_contour.h calcul_geometrique.h image.h sequence_point.h 
	@echo ""
	@echo "---------------------------------------------"
	@echo "Compilation du module ecrire_contour_eps"
	@echo "---------------------------------------------"
	$(CC) -c $(COMPILOPTS) $<	

simplification_segment.o : simplification_segment.c simplification.h calcul_geometrique.h image.h sequence_point.h 
	@echo ""
	@echo "---------------------------------------------"
	@echo "Compilation du module simplification_segment"
	@echo "---------------------------------------------"
	$(CC) -c $(COMPILOPTS) $<

simplification_bezier2.o : simplification_bezier2.c simplification.h calcul_geometrique.h image.h sequence_point.h 
	@echo ""
	@echo "---------------------------------------------"
	@echo "Compilation du module simplification_bezier2"
	@echo "---------------------------------------------"
	$(CC) -c $(COMPILOPTS) $<

simplification_bezier3.o : simplification_bezier3.c simplification.h calcul_geometrique.h image.h sequence_point.h 
	@echo ""
	@echo "---------------------------------------------"
	@echo "Compilation du module simplification_bezier3"
	@echo "---------------------------------------------"
	$(CC) -c $(COMPILOPTS) $<

########################################################
# regles explicites de creation des executables

ecrire_contour : ecrire_contour.o calcul_contour.o calcul_geometrique.o image.o sequence_point.o
	@echo ""
	@echo "---------------------------------------------"
	@echo "Creation de l'executable "$@
	@echo "---------------------------------------------"
	$(CC) $^ $(LDOPTS) -o $@

ecrire_contour_eps : ecrire_contour_eps.o calcul_contour.o calcul_geometrique.o image.o sequence_point.o
	@echo ""
	@echo "---------------------------------------------"
	@echo "Creation de l'executable "$@
	@echo "---------------------------------------------"
	$(CC) $^ $(LDOPTS) -o $@

simplification_segment : simplification_segment.o simplification.o calcul_geometrique.o image.o sequence_point.o
	@echo ""
	@echo "---------------------------------------------"
	@echo "Creation de l'executable "$@
	@echo "---------------------------------------------"
	$(CC) $^ $(LDOPTS) -o $@

simplification_bezier2 : simplification_bezier2.o simplification.o calcul_geometrique.o image.o sequence_point.o
	@echo ""
	@echo "---------------------------------------------"
	@echo "Creation de l'executable "$@
	@echo "---------------------------------------------"
	$(CC) $^ $(LDOPTS) -o $@

simplification_bezier3 : simplification_bezier3.o simplification.o calcul_geometrique.o image.o sequence_point.o
	@echo ""
	@echo "---------------------------------------------"
	@echo "Creation de l'executable "$@
	@echo "---------------------------------------------"
	$(CC) $^ $(LDOPTS) -o $@

#suppression des .o pour la lisibilité 
visible:
	rm *.o

# regle pour "nettoyer" le r�pertoire
clean:
	rm -fR $(EXECUTABLES) *.o 
