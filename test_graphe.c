#include <stdio.h>
#include <stdlib.h>

//#include "graphe.h"
#include "file.h"


int main (int argc, char **argv)
{
  pgraphe_t g ;
  pnoeud_t p1,p2;
  int *chemin, *nb_noeud;
  
  if (argc != 2)
    {
      fprintf (stderr, "erreur parametre \n") ;
      exit (-1) ;
    }

  /*
    la fonction lire_graphe alloue le graphe (matrice,...) 
    et lit les donnees du fichier passe en parametre
  */
  
  
  lire_graphe (argv [1], &g) ;

  /*
    la fonction ecrire_graphe affiche le graphe a l'ecran
  */  

  /*int colortab[10];
  for(int i=0;i<10;i++){
    colortab[i]=i+1;
  }
  */
  //colorier_graphe(g,colortab);
  ecrire_graphe (g) ;
  p1 = g->noeud_suivant;
  p2 = p1->noeud_suivant;  
  //g->visite=0;
  //printf("arc sortants:%d\n",degre_sortant_noeud(g,g));
  //afficher_graphe_profondeur(g);
  //afficher_graphe_largeur(g);
  //printf("graphe complet: %d\n",complet(g));


  plus_court_chemin(g,1,5,chemin,nb_noeud);

  printf("nb noeuds : %d\n",*nb_noeud);
  for(int i = 0; i < *nb_noeud; i++)
  {
    printf("%d\n",chemin[i]);
  }

  //printf("distance : %d\n",distance(g,p1,p2));

  return 0;
}
