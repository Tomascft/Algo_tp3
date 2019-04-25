#include <stdio.h>
#include <stdlib.h>

//#include "graphe.h"
#include "file.h"

int main(int argc, char **argv)
{
  pgraphe_t g;
  pnoeud_t p1, p2;
  int *chemin, *nb_noeud;
  pchemin_t c;

  if (argc != 2)
  {
    fprintf(stderr, "erreur parametre \n");
    exit(-1);
  }

  /*
    la fonction lire_graphe alloue le graphe (matrice,...) 
    et lit les donnees du fichier passe en parametre
  */

  lire_graphe(argv[1], &g);

  /*
    la fonction ecrire_graphe affiche le graphe a l'ecran
  */

  /*int colortab[10];
  for(int i=0;i<10;i++){
    colortab[i]=i+1;
  }
  */
  //colorier_graphe(g,colortab);
  ecrire_graphe(g);
  p1 = g->noeud_suivant;
  p2 = p1->noeud_suivant;
  //g->visite=0;
  //printf("arc sortants:%d\n",degre_sortant_noeud(g,g));
  //afficher_graphe_profondeur(g);
  //afficher_graphe_largeur(g);
  //printf("graphe complet: %d\n",complet(g));

  /*plus_court_chemin(g,1,5,chemin,nb_noeud);

  printf("nb noeuds : %d\n",*nb_noeud);
 
  for(int i = 0; i < *nb_noeud; i++)
  {
    printf("%d\n",chemin[i]);
  }*/

  //printf("distance : %d\n",distance(g,p1,p2));

/*
  c = (pchemin_t) malloc(sizeof(chemin_t));

  c->nb_noeuds = (int) malloc(sizeof(int));
  c->nb_noeuds = 3;
  c->labels = (pnoeud_t *)malloc(sizeof(pnoeud_t) * c->nb_noeuds);
  c->labels[0] = chercher_noeud(g, 1);
  c->labels[1] = chercher_noeud(g, 6);
  c->labels[2] = chercher_noeud(g, 2);
  

  printf("elementaire = %d\n", elementaire(g, *c));

  printf("simple = %d\n", simple(g, *c));

  printf("eulerien = %d\n", eulerien(g, *c));

  printf("hamiltonien = %d\n", hamiltonien(g, *c));*/

  printf("graphe eulerien = %d\n", graphe_eurelien(g));

  printf("graphe hamiltonien = %d\n", graphe_hamiltonien(g));

  printf("excentricite = %d\n", excentricite(g, p1));

  printf("diametre = %d\n", diametre(g));

  return 0;
}
