
typedef struct a *parc_t ;

/*
  definition des types noeud et pointeur de noeud
  un graphe est constitué d'une liste de noeuds
*/

typedef struct n
{
  int        label ; // label du noeud/sommet
  parc_t     liste_arcs ; // arcs sortants du noeud
  struct n   *noeud_suivant ; // noeud/sommet suivant du graphe
  
} noeud_t, *pnoeud_t ;

/*
  definition des types arc et pointeur d'arc
  Les arcs sortant d'un noeud sont chainés
  Pour chaque arc, il y a un poids qui peut par exemple correspondre
  a une distance
*/

typedef struct a {
  
                  int         poids ; // poids de l arc
                  pnoeud_t    noeud ; // identificateur du noeud destinataire
                  struct a *  arc_suivant ; // arc suivant
  
} arc_t, *parc_t ;



typedef struct c {
  
                  int         nb_noeuds; // Taille du chemin
                  pnoeud_t    noeud; // identificateur du noeud

                  struct c *  chemin_suivant ; // chemin suivant
  
} chemin_t, *pchemin_t ;

/*
  pgraphe_t: pointeur vers le premier noeud d'un graphe
*/

typedef pnoeud_t pgraphe_t ;


typedef pchemin_t pdeb_chemin_t ;


/*
  DEFINIR LE TYPE chemin_t (examen 2017)
*/

void lire_graphe (char * file_name, pgraphe_t *g) ;

void ecrire_graphe (pnoeud_t p) ;

int nombre_arcs (pgraphe_t g) ;

int nombre_sommets (pgraphe_t g) ;

int degre_sortant_noeud (pgraphe_t g, pnoeud_t n) ;

int degre_entrant_noeud (pgraphe_t g, pnoeud_t n) ;

int degre_maximal_graphe (pgraphe_t g) ;

int degre_minimal_graphe (pgraphe_t g) ;

int independant (pgraphe_t g) ;

int complet (pgraphe_t g) ;

int regulier (pgraphe_t g) ;

void afficher_graphe_profondeur (pgraphe_t g) ;

void colorier_graphe (pgraphe_t g, int *couleurs) ;

void afficher_graphe_largeur (pgraphe_t g) ;

int plus_court_chemin (pgraphe_t g, int origine, int destination, int *chemin,
		       int *nb_noeuds) ;

/*
  placer les fonctions de l'examen 2017 juste apres
*/

int elementaire(pgraphe_t g, chemin_t c);

int simple(pgraphe_t g, chemin_t c);