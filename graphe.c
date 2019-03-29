/*
  Structures de type graphe
  Structures de donnees de type liste
  (Pas de contrainte sur le nombre de noeuds des  graphes)
*/

#include <stdio.h>
#include <stdlib.h>

#include "graphe.h"

pnoeud_t chercher_noeud(pgraphe_t g, int label)
{
	pnoeud_t p;

	p = g;

	while ((p != NULL) && (p->label != label))
	{
		p = p->noeud_suivant;
	}
	return p;
}

parc_t existence_arc(parc_t l, pnoeud_t n)
{
	parc_t p = l;

	while (p != NULL)
	{
		if (p->noeud == n)
			return p;
		p = p->arc_suivant;
	}
	return p;
}

void ajouter_arc(pnoeud_t o, pnoeud_t d, int distance) //distance est le poid de l'arc
{
	parc_t parc;

	parc = (parc_t)malloc(sizeof(arc_t));

	if (existence_arc(o->liste_arcs, d) != NULL)
	{
		fprintf(stderr, "ajout d'un arc deja existant\n");
		exit(-1);
	}

	parc->poids = distance;
	parc->noeud = d;
	parc->arc_suivant = o->liste_arcs;
	o->liste_arcs = parc;
	return;
}

void lire_graphe(char *file_name, pgraphe_t *g)
{
	pnoeud_t p = NULL; /* premier noeud du graphe */
	pnoeud_t l = NULL; /* dernier noeud du graphe */
	FILE *f;
	int nb_nodes;
	int i;
	pnoeud_t c;
	int origine, destination, distance;

	printf("fichier %s\n", file_name);
	f = fopen(file_name, "r");
	if (f == NULL)
	{
		fprintf(stderr, "Le fichier %s n'existe pas\n", file_name);
		exit(-1);
	}

	fscanf(f, "%d", &nb_nodes);

	for (i = 0; i < nb_nodes; i++)
	{
		c = (pnoeud_t)malloc(sizeof(noeud_t));
		c->noeud_suivant = NULL;

		if (fscanf(f, "%d", &c->label) == EOF)
		{
			fprintf(stderr, "erreur dans le contenu du fichier label %d\n", c->label);
			exit(-1);
		}

		if (chercher_noeud(p, c->label) != NULL)
		{
			fprintf(stderr, "erreur label deja dans le graphe %d\n", c->label);
			exit(-1);
		}

		if (p == NULL)
		{
			p = c;
			l = c;
		}
		else
		{
			l->noeud_suivant = c;
			l = c;
		}
	}

	while (fscanf(f, "%d %d %d", &origine, &destination, &distance) != EOF)
	{
		pnoeud_t o, d;

		o = chercher_noeud(p, origine);
		if (o == NULL)
		{
			fprintf(stderr, "erreur noeud origine %d\n", origine);
			exit(-1);
		}
		d = chercher_noeud(p, destination);
		if (d == NULL)
		{
			fprintf(stderr, "erreur noeud destination %d\n", destination);
			exit(-1);
		}

		ajouter_arc(o, d, distance);
	}

	*g = p;
}

void ecrire_graphe(pnoeud_t p)
{

	parc_t arc;

	while (p != NULL)
	{
		printf("Noeud %d: ", p->label);
		arc = p->liste_arcs;
		while (arc != NULL)
		{
			printf(" (%d %d) ", arc->noeud->label, arc->poids);
			arc = arc->arc_suivant;
		}
		printf("\n");
		p = p->noeud_suivant;
	}

	return;
}

// ===================================================================
//nos fonctions

int nombre_arcs(pgraphe_t g)
{
	pnoeud_t p = g;
	int taille = 0;

	while (p != NULL)
	{
		parc_t a = p->liste_arcs;
		while (a != NULL)
		{
			taille++;
			a = a->arc_suivant;
		}
		p = p->noeud_suivant;
	}
	return taille;
}

int nombre_sommets(pgraphe_t g)
{
	pnoeud_t p = g;
	int taille = 0;

	while (p != NULL)
	{
		p = p->noeud_suivant;
		taille++;
	}
	return taille;
}

int degre_sortant_noeud(pgraphe_t g, pnoeud_t n)
{
	/*
    Cette fonction retourne le nombre d'arcs sortants 
    du noeud n dans le graphe g.
  */
	int degre = 0;
	pnoeud_t b = g;
	while (b != NULL)
	{
		if (b == n)
		{
			parc_t a = n->liste_arcs;
			while (a != NULL)
			{
				degre++;
				a = a->arc_suivant;
			}

			return degre;
		}
		b = b->noeud_suivant;
	}
	return -1;
}

int degre_entrant_noeud(pgraphe_t g, pnoeud_t n)
{
	/*
    Cette fonction retourne le nombre d'arcs entrants 
    dans le noeud n dans le graphe g
  */
	int degre = 0;

	pnoeud_t p = g;
	while (p != NULL)
	{
		parc_t a = p->liste_arcs;
		while (a != NULL)
		{
			if (a->noeud == n)
			{
				degre++;
			}
			a = a->arc_suivant;
		}
		p = p->noeud_suivant;
	}
	return degre;
}

int degre_maximal_graphe(pgraphe_t g)
{
	/*
    Max des degres des noeuds du graphe g
  */
	pnoeud_t p = g;
	int max = 0, tmp;

	while (p != NULL)
	{
		tmp = degre_sortant_noeud(g, p); // + degre_entrant_noeud(g,p);
		if (tmp > max)
		{
			max = tmp;
		}
		p = p->noeud_suivant;
	}

	return max;
}

int degre_minimal_graphe(pgraphe_t g)
{
	pnoeud_t p = g;
	int min = 999, tmp;

	while (p != NULL)
	{
		tmp = degre_sortant_noeud(g, p); // + degre_entrant_noeud(g,p);
		if (tmp > min)
		{
			min = tmp;
		}
		p = p->noeud_suivant;
	}
	return min;
}

int independant(pgraphe_t g)
{
	/* Les aretes du graphe n'ont pas de sommet en commun. On verra plus tard ce qu'il faut faire*/
	pnoeud_t p = g;
	int tmp, taille = 0;

	while (p != NULL)
	{
		tmp = degre_entrant_noeud(g, p) + degre_sortant_noeud(g, p);
		if (tmp > 2)
		{
			return 0; //Faux
		}
		if (tmp == 2 && p->label != p->liste_arcs->noeud->label)
		{
			return 0;
		}
		p = p->noeud_suivant;
	}

	return 1; //Vrai
}

int complet(pgraphe_t g)
{
	/* Toutes les paires de sommet du graphe sont jointes par un arc */
	pnoeud_t p = g;
	int taille = nombre_sommets(g);
	int nbarc;

	while (p != NULL)
	{
		parc_t a = p->liste_arcs;
		nbarc = 0;
		while (a != NULL)
		{
			if (a->noeud != p)
			{
				nbarc++;
			}
			a = a->arc_suivant;
		}
		if (nbarc != taille - 1)
			return 0;

		p = p->noeud_suivant;
	}

	return 1;
}

int regulier(pgraphe_t g)
{
	/* 
     graphe regulier: tous les noeuds ont le meme degre
     g est le ponteur vers le premier noeud du graphe
     renvoie 1 si le graphe est régulier, 0 sinon
  */
	pnoeud_t p = g;
	int degre = degre_entrant_noeud(g, p) + degre_sortant_noeud(g, p);
	int tmp;

	p = p->noeud_suivant;
	while (p != NULL)
	{
		if (degre != degre_entrant_noeud(g, p) + degre_sortant_noeud(g, p))
		{
			return 0;
		}
		p = p->noeud_suivant;
	}

	return 1;
}

void afficher_graphe_profondeur(pgraphe_t g)
{
	/*
    afficher les noeuds du graphe avec un parcours en profondeur
  */
	pnoeud_t p = g;

	while (p != NULL)
	{

		printf("Noeud %d: ", p->label);
		parc_t arc = p->liste_arcs;
		while (arc != NULL)
		{
			printf(" (%d %d) ", arc->noeud->label, arc->poids);
			arc = arc->arc_suivant;
		}
		printf("\n");
		p = p->noeud_suivant;
	}
}

void colorier_graphe(pgraphe_t g, int *couleurs)
{
	/*
    coloriage du graphe g
    Les couleurs des noeuds du graphe sont dans le tableau couleurs
  */

	return;
}

void afficher_graphe_largeur(pgraphe_t g)
{
	/*
    afficher les noeuds du graphe avec un parcours en largeur
  */

	return;
}

int plus_court_chemin(pgraphe_t g, int origine, int destination, int *chemin,
											int *nb_noeuds)
{
	/* 
     Calcul de la longueur du plus court chemin
     entre origine et destination
     La variable chemin contient les noeuds du chemin le plus court
     nb_noeuds indique le nombre de noeuds du chemin
  */

	pnoeud_t p = g;
	pnoeud_t or, dest;

	if (origine == destination)
	{
		*nb_noeuds = 1;
		chemin[0] = origine;
		return 1;
	}

	while (p != NULL)
	{
		if (p->label == origine)
		{
			or = p;
		}
		if (p->label == destination)
		{
			dest = p;
		}
		p = p->noeud_suivant;
	}

	return 0;
}

int elementaire(pgraphe_t g, chemin_t c)
{
	int taille = c.nb_noeuds;
	int tab[taille];

	for (int i = 0; i < taille; i++)
	{
		tab[i] = 0;
	}

	for (int i = 0; i < c.nb_noeuds; i++)
	{
		if (tab[c.labels[i]] == 1)
		{
			return 0;
		}
		tab[c.labels[i]] = 1;
	}

	return 1;
}

int simple(pgraphe_t g, chemin_t c)
{
	int taille = c.nb_noeuds - 1;
	int tab[taille][2];

	for (int i = 0; i < taille; i++)
	{
		tab[i][0] = c.labels[i];
		tab[i][1] = c.labels[i + 1];

		for (int j = 0; j < i; j++)
		{
			if (tab[i][0] == tab[j][0] && tab[i][1] == tab[j][1])
			{
				return 0;
			}
		}
	}
	return 1;
}

int eulerien(pgraphe_t g, chemin_t c)
{
	int taille = nombre_arcs(g);
	parc_t tab[taille];
	pnoeud_t p = g;
	int i = 0;

	while (p != NULL)
	{
		parc_t a = p->liste_arcs;
		while (a != NULL)
		{
			tab[i] = a;
			a = a->arc_suivant;
			i++;
		}
		p = p->noeud_suivant;
	}

	for (i = 0; i < c.nb_noeuds - 1; i++)
	{
		p = chercher_noeud(g, c.labels[i]);
		parc_t a = p->liste_arcs;
		while (a != NULL && a->noeud->label != c.labels[i + 1])
		{
			a = a->arc_suivant;
		}
		for (int j = 0; j < taille; j++)
		{
			if (tab[j] == a)
			{
				tab[j] = NULL;
			}
		}
	}

	for (i = 0; i < taille; i++)
	{
		if (tab[i] != NULL)
		{
			return 0;
		}
	}

	return 1;
}

int hamiltonien(pgraphe_t g, chemin_t c) // Ca utilise bcp de boucles, moyen d'opti ?
{
	int taille = nombre_sommets(g);
	int tab[taille];
	pnoeud_t p = g;
	int i = 0, j = 0;

	while (p != NULL)
	{
		tab[i] = p->label;
		p = p->noeud_suivant;
		i++;
	}

	for (i = 0; i < c.nb_noeuds; i++)
	{
		for (int j = 0; j < taille; j++)
		{
			if (tab[j] == c.labels[i])
			{
				tab[j] = -1;
			}
		}
	}

	for (i = 0; i < taille; i++)
	{
		if (tab[i] != -1)
		{
			return 0;
		}
	}
	return 1;
}

int graphe_eurelien(pgraphe_t g)
{

	return 0;
}

int graphe_hamiltonien(pgraphe_t g)
{
	pnoeud_t p = g;
	
	int a = 0;

	while (p != NULL)
	{
		if (degre_entrant_noeud(g, p) == 0)
		{
			a++;
		}
		if (a == 2)	//Si il y a 2 noeuds non accesibles alors il ne peut pas y avoir de chemin hamiltonien
		{
			return 0;
		}
		p = p->noeud_suivant;
	}
	

	//TODO : Pour chaque noeud, on essaye de visiter tout les autres noeuds du graphe. Si a un moment on y arrive return 1
	//Possibilité d'opti : On compte le nombre de noeud non accesibles: 1 alors on est obligé de commencer par lui. 2 return 0
	return 0;
}