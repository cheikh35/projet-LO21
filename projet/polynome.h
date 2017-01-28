/*Auteur : Hamza JAFFALI ; Projet : Manipulation Polynomes*/

#ifndef hj_POLYNOME_h
#define hj_POLYNOME_h

/*Définition des différents types utilisés*/

typedef struct
{
	float coef;
	int deg;
} Monome;

typedef struct elem
{
	Monome monome;
	struct elem *next;
	struct elem *prev;
} Element;

typedef struct
{
	Element *tete;
	Element *last;

	int taille;
	int hdeg;
} Polynome;

/*Prototypes des différentes fonctions et procédures utilisées*/

Monome creerMonome (float, int);
Monome mderiver (Monome , int);
Monome mderiverUnefois (Monome);
Monome creerMonomeInteraction ();

Polynome creerPolynome ();
Polynome ajouterMonome (Polynome, Monome);
Polynome ajouterMonomeTete (Polynome, Monome);
Polynome ajouterMonomeQueue (Polynome, Monome);
Polynome supprimerMonome (Polynome, int);
Polynome supprimerMonomeTete (Polynome);
Polynome additionner (Polynome, Polynome);
Polynome multiplier (Polynome, Polynome);
Polynome pderiver (Polynome, int);
Polynome pderiverUnefois (Polynome);
Polynome creerPolynomeInteraction ();

void afficherMonome (Monome);
void afficherPolynome (Polynome);

#endif
