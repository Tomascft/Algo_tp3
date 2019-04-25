/*
  Structures de type graphe
  Structures de donnees de type liste
  (Pas de contrainte sur le nombre de noeuds des  graphes)
*/

#include <stdio.h>
#include <stdlib.h>

#include "graphe.h"
#include "file.h"

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
		printf("Noeud %d (%d)): ", p->label, p->couleur);
		arc = p->liste_arcs;
		while (arc != NULL)
		{
			printf(" (%d(%d)  %d) ", arc->noeud->label, arc->noeud->couleur, arc->poids);
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
	int tmp;

	while (p != NULL)
	{
		tmp = degre_entrant_noeud(g, p) + degre_sortant_noeud(g, p);
		if (tmp > 3)
		{
			return 0; //Faux
		}
		if (tmp == 3 && (p->label != p->liste_arcs->noeud->label && p->label != p->liste_arcs->arc_suivant->noeud->label))
			return 0;
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
		if (nbarc < taille - 1)
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
	p->visite = 1;

	printf("%d ", p->label);
	parc_t tmp = p->liste_arcs;

	while (tmp != NULL)
	{

		if (tmp->noeud->visite == 0)
		{

			afficher_graphe_profondeur(tmp->noeud);
		}
		tmp = tmp->arc_suivant;
	}
}

void colorier_graphe(pgraphe_t g, int *couleurs)
{
	/*
    coloriage du graphe g
    Les couleurs des noeuds du graphe sont dans le tableau couleurs
  */
	//int n=nombre_sommets(g);
	pnoeud_t p = g;
	while (p != NULL)
	{
		p->couleur = *couleurs;
		p = p->noeud_suivant;
	}
	p = g;
	while (p != NULL)
	{
		int c = 0;
		parc_t a = p->liste_arcs;
		while (a != NULL)
		{
			if (a->noeud->couleur == p->couleur && a->noeud != p)
				c++;
			a = a->arc_suivant;
		}
		p->couleur = *(couleurs + c);
		p = p->noeud_suivant;
	}
	return;
}

void afficher_graphe_largeur(pgraphe_t g)
{
	/*
    afficher les noeuds du graphe avec un parcours en largeur
  */
	printf("Parcour largeur: ");
	pnoeud_t p = g;
	while (p != NULL)
	{
		pfile_t f = creer_file();
		int i;
		i = deposer_file(f, p);
		if (i == 1)
		{
		}
		while (!file_vide(f))
		{
			pnoeud_t tmp = retirer_file(f);
			if (tmp->visite == 0)
			{
				printf("%d ", tmp->label);
				tmp->visite = 1;
				parc_t a = tmp->liste_arcs;
				while (a != NULL)
				{
					if (a->noeud->visite == 0)
					{
						i = deposer_file(f, a->noeud);
					}
					a = a->arc_suivant;
				}
			}
		}
		p = p->noeud_suivant;
	}
	printf("\n\n");
	return;
}

void init(pgraphe_t g, int origine)
{
	pnoeud_t p = g;

	while (p != NULL)
	{
		p->poid = 99;
		if (p->label == origine)
		{
			p->poid = 0;
		}
		p->visite = 0;
		p = p->noeud_suivant;
	}
}

pnoeud_t trouve_min(pgraphe_t g)
{
	int min = 100;
	pnoeud_t tmp = NULL;
	pnoeud_t p = g;

	while (p != NULL)
	{

		if (p->poid < min && p->visite == 0)
		{
			min = p->poid;
			tmp = p;
		}
		p = p->noeud_suivant;
	}
	return tmp;
}

void maj_distances(parc_t a, pnoeud_t s2)
{
	if (a->noeud->poid > s2->poid + a->poids)
	{
		a->noeud->poid = s2->poid + a->poids;
		a->noeud->precedent_chemin = s2;
	}
}

void ecrire_poids(pgraphe_t g)
{
	pnoeud_t p = g;

	while (p != NULL)
	{
		printf("poids : %d visite : %d\n", p->poid, p->visite);
		p = p->noeud_suivant;
	}
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
	pnoeud_t tmp = p;
	parc_t a;

	int taille = nombre_sommets(g);
	int tab[taille];
	int i;

	init(p, origine);

	while (tmp != NULL)
	{
		tmp = trouve_min(p);
		if (tmp != NULL)
		{
			tmp->visite = 1;
			a = tmp->liste_arcs;
			while (a != NULL)
			{
				maj_distances(a, tmp);
				a = a->arc_suivant;
			}
		}
	}

	i = 0;
	p = chercher_noeud(g, destination);
	while (p != NULL && p->label != origine)
	{
		tab[i] = p->label;
		i++;
		if (p->label == 99)
		{
			return 0;
		}
		p = p->precedent_chemin;
	}
	if (p == NULL)
	{
		return 0;
	}
	tab[i] = origine;

	*nb_noeuds = i + 1;
	int j = 0;
	//chemin = (int *)malloc(sizeof(int) * (i + 1));
	for (i = *nb_noeuds - 1; i >= 0; i--)
	{
		chemin[j] = tab[i];
		//printf("%d\n", tab[i]);
		j++;
	}
	return 1;
}

int elementaire(pgraphe_t g, chemin_t c)
{

	pnoeud_t p = g;

	while (p != NULL)
	{
		p->visite = 0;
		p = p->noeud_suivant;
	}

	for (int i = 0; i < c.nb_noeuds; i++)
	{
		p = c.labels[i];
		if (p->visite == 1)
		{
			return 0;
		}
		p->visite = 1;
	}

	return 1;
}

int simple(pgraphe_t g, chemin_t c)
{
	pnoeud_t p = g;
	parc_t a = p->liste_arcs;

	while (p != NULL)
	{
		a = p->liste_arcs;
		while (a != NULL)
		{
			a->visite = 0;
			a = a->arc_suivant;
		}
		p = p->noeud_suivant;
	}

	for (int i = 0; i < c.nb_noeuds - 1; i++)
	{
		p = c.labels[i];
		a = existence_arc(p->liste_arcs, c.labels[i + 1]);
		if (a == NULL)
		{
			return -1; // Le chemin est faux
		}
		if (a->visite == 1)
		{
			return 0;
		}
		a->visite = 1;
	}

	return 1;
}

int eulerien(pgraphe_t g, chemin_t c)
{
	pnoeud_t p = g;
	parc_t a;
	int i = 0;

	while (p != NULL)
	{
		a = p->liste_arcs;
		while (a != NULL)
		{
			a->visite = 0;
			a = a->arc_suivant;
		}
		p = p->noeud_suivant;
	}

	for (i = 0; i < c.nb_noeuds - 1; i++)
	{
		p = c.labels[i];
		a = existence_arc(p->liste_arcs, c.labels[i + 1]);
		a->visite = 1;
	}

	p = g;
	while (p != NULL)
	{
		a = p->liste_arcs;
		while (a != NULL)
		{
			if (a->visite != 1)
			{
				return 0;
			}
			a = a->arc_suivant;
		}
		p = p->noeud_suivant;
	}

	return 1;
}

int hamiltonien(pgraphe_t g, chemin_t c)
{
	pnoeud_t p = g;
	int i = 0;

	while (p != NULL)
	{
		p->visite = 0;
		p = p->noeud_suivant;
	}

	for (i = 0; i < c.nb_noeuds; i++)
	{
		p = c.labels[i];
		p->visite = 1;
	}

	p = g;
	while (p != NULL)
	{
		if (p->visite != 1)
		{
			return 0;
		}
		p = p->noeud_suivant;
	}

	return 1;
}

int check_dedans(pnoeud_t *tab, int taille, pnoeud_t p)
{
	int i = 0;

	for (i = 0; i < taille; i++)
	{
		if (tab[i] == p)
		{
			return 1;
		}
	}

	return 0;
}

int check_dedans_arc(parc_t *tab, int taille, parc_t p)
{
	int i = 0;

	for (i = 0; i < taille; i++)
	{
		if (tab[i] == p)
		{
			return 1;
		}
	}

	return 0;
}

int graphe_connexe(pgraphe_t g)
{
	afficher_graphe_profondeur(g);
	pnoeud_t p = g;
	while (p != NULL)
	{
		if (p->visite == 0)
			return 0;
		p = p->noeud_suivant;
	}
	return 1;
}

int degree_noeud(pgraphe_t g, pnoeud_t n)
{
	int degree = 0;
	parc_t a = n->liste_arcs;
	while (a != NULL)
	{
		pnoeud_t p = g;
		while (p != NULL)
		{
			if (p->label == a->noeud->label)
			{
				parc_t tmp1 = p->liste_arcs;
				while (tmp1 != NULL)
				{
					if (tmp1->noeud->label == n->label)
					{
						degree++;
						break;
					}
					tmp1 = tmp1->arc_suivant;
				}
				break;
			}
			p = p->noeud_suivant;
		}
		a = a->arc_suivant;
	}
	return degree;
}

int graphe_eurelien(pgraphe_t g)
{
	if (!graphe_connexe(g))
		return 0;
	//int deg_imp = 0; //degré impair
	pnoeud_t p = g;
	while (p != NULL)
	{
		/*	if (degree_noeud(g,p) % 2 != 0)
			deg_imp++;
		p = p->noeud_suivant;*/
		if (degre_entrant_noeud(g, p) != degre_sortant_noeud(g, p))
		{
			return 0;
		}
		p = p->noeud_suivant;
	}
	return 1;
	/*
	if (deg_imp == 2 || deg_imp == 0)
		return 1;
	else
		return 0;*/
}

int graphe_hamiltonien(pgraphe_t g)
{
	if (!graphe_connexe(g))
		return 0;
	pnoeud_t p = g;
	int n = nombre_sommets(g);

	while (p != NULL)
	{
		if (degree_noeud(g, p) < n / 2)
		{
			return 0;
		}
		p = p->noeud_suivant;
	}

	return 1;
	/*
	pnoeud_t p = g, isole;
	int a = 0; 
	parc_t tmp;

	if (independant(g))
	{
		return 0;
	}

	while (p != NULL)
	{
		if (degre_entrant_noeud(g, p) == 0)
		{
			a++;
			isole = p;
		}
		if (a == 2) //Si il y a 2 noeuds non accesibles alors il ne peut pas y avoir de chemin hamiltonien
		{
			return 0;
		}

		p = p->noeud_suivant;
	}

	int flag = 0;

	if (a == 1)
	{
		p = isole;
		isole->precedent_chemin = NULL;
		while (p != NULL && flag != 1)
		{
			p->visite = 1;
			tmp = p->liste_arcs;
			while (tmp != NULL && tmp->visite != 0)
			{
				tmp = tmp->arc_suivant;
			}
			if (tmp == NULL)
			{
				pnoeud_t test = g;
				flag = 1;
				while (test != NULL)
				{
					if (test->visite == 0)
					{
						flag = 0;
					}
					test = test->noeud_suivant;
				}
				p->visite = 0;
				tmp = p->liste_arcs;
				while (tmp != NULL)
				{
					tmp->visite = 0;
					tmp = tmp->arc_suivant;
				}
				p = p->precedent_chemin;
			}
			else
			{
				tmp->noeud->precedent_chemin = p;
				p = tmp->noeud;
				tmp->visite = 1;
			}
		}
		return flag;
	}
	else
	{
		pnoeud_t h = g;
		p = h;
		while (p != NULL)
		{
			p->precedent_chemin = NULL;
			while (p != NULL && flag != 1)
			{
				p->visite = 1;
				tmp = p->liste_arcs;
				while (tmp != NULL && tmp->visite != 0)
				{
					tmp = tmp->arc_suivant;
				}
				if (tmp == NULL)
				{
					pnoeud_t test = g;
					flag = 1;
					while (test != NULL)
					{
						if (test->visite == 0)
						{
							flag = 0;
						}
						test = test->noeud_suivant;
					}
					p->visite = 0;
					tmp = p->liste_arcs;
					while (tmp != NULL)
					{
						tmp->visite = 0;
						tmp = tmp->arc_suivant;
					}
					p = p->precedent_chemin;
				}
				else
				{
					tmp->noeud->precedent_chemin = p;
					p = tmp->noeud;
					tmp->visite = 1;
				}
			}
			if (flag == 1)
			{
				return 1;
			}
			p = g;
			while (p != NULL)
			{
				p->visite = 0;
				p = p->noeud_suivant;
			}
			h = h->noeud_suivant;
			p = h;
		}
	}

	return 1;*/
}

int distance(pgraphe_t g, pnoeud_t x, pnoeud_t y)
{
	pnoeud_t p = g;
	pnoeud_t tmp = p;
	parc_t a;

	init(p, x->label);

	while (tmp != NULL)
	{
		tmp = trouve_min(p);
		if (tmp != NULL)
		{
			tmp->visite = 1;
			a = tmp->liste_arcs;
			while (a != NULL)
			{
				maj_distances(a, tmp);
				a = a->arc_suivant;
			}
		}
	}
	return y->poid;
}

int excentricite(pgraphe_t g, pnoeud_t n)
{
	// Pour chaque noeud du graphe on regarde ca distance avec n
	int max = -1, tmp;
	pnoeud_t p = g;

	while (p != NULL)
	{
		tmp = distance(g, n, p);
		if (tmp > max)
		{
			max = tmp;
		}
		p = p->noeud_suivant;
	}

	return max;
}

int diametre(pgraphe_t g)
{
	pnoeud_t p = g;
	int max = -1, tmp;

	while (p != NULL)
	{
		tmp = excentricite(g, p);
		if (tmp > max)
		{
			max = tmp;
		}
		p = p->noeud_suivant;
	}

	return max;
}
