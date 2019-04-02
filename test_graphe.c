#include <stdio.h>
#include <stdlib.h>

#include "graphe.h"

int main (int argc, char **argv)
{
  pgraphe_t g ;
  
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
  
  ecrire_graphe (g) ;      
  //g->visite=0;
  //printf("arc sortants:%d\n",degre_sortant_noeud(g,g));
  afficher_graphe_profondeur(g);

  //printf("graphe complet: %d\n",complet(g));

  return 0;
}
