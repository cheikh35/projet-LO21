/*Auteur : Hamza JAFFALI ; Projet : Manipulation Polynomes*/

#include "polynome.h"
#include <stdio.h>
#include <stdlib.h>

/*Cette fonction prend en paramètre un réel et un entier, constituant respectivement le coefficien et le degré du monome à créer.
Elle renvoie ensuite le monome ainsi généré.*/
Monome creerMonome (float a, int k)
{
/*On déclare un monome m*/
	Monome m;
/*On affecte le coefficient/degré voulu au monome*/
	m.coef = a;
	m.deg = k;
/*On renvoie le monome ainsi généré*/
	return m;
}

/*Cette fonction ne prend aucun paramètre, et renvoie un polynome vide initialisé en tant que polynome nul*/
Polynome creerPolynome ()
{
/*On déclare un polynome p*/
	Polynome p;
/*On initialise p comme un polynome nul (vide)*/
	p.tete = NULL;
	p.last = NULL;
	p.taille = 0;
	p.hdeg = 0;
/*On renvoie le polynome ainsi généré*/
	return p;
}

/*Cette fonction prend en paramètre un polynome et un monome, et ajoute ce monome en tête du polynome. On renvoie ensuite un polynome.
La fonction ne dinstingue pas les cas limites : son utilisation ne se fait que dans des cas "sécurisés"*/
Polynome ajouterMonomeTete (Polynome p, Monome m)
{
    Polynome temp;
    Element *newelem;
    newelem = (Element*) malloc(sizeof(Element));
    newelem->monome = m;
    newelem->prev = NULL;
    temp.tete = newelem;
    temp.taille = p.taille + 1;
    if (p.taille != 0)
    {
        (p.tete)->prev = newelem;
        temp.last = p.last;
        temp.hdeg = p.hdeg;
        newelem->next = p.tete;
    }
    else
    {
        temp.last = newelem;
        temp.hdeg = (newelem->monome).deg;
        newelem->next = NULL;
    }
    return temp;
}

/*Cette fonction prend en paramètre un polynome et un monome, et ajoute ce monome en queue du polynome. On renvoie ensuite un polynome.
La fonction ne dinstingue pas les cas limites : son utilisation ne se fait que dans des cas "sécurisés"*/
Polynome ajouterMonomeQueue (Polynome p, Monome m)
{
    Polynome temp;
    Element *newelem;
    newelem = (Element*) malloc(sizeof(Element));
    newelem->monome = m;
    newelem->next = NULL;
    temp.last = newelem;
    temp.taille = p.taille + 1;
    temp.hdeg = (newelem->monome).deg;
    if (p.taille != 0)
    {
        temp.tete = p.tete;
        newelem->prev = p.last;
		(p.last)->next = newelem;
    }
    else
    {
        temp.tete = newelem;
        newelem->prev = NULL;
    }
    return temp;
}


/* Cette fonction prend en paramètre un polynome p et un monome m. Elle renvoie ensuite un polynome.
Elle ajoute le monome au polynome au début, au milieu ou à la fin de ce dernier en fonction du degré du monome.*/
Polynome ajouterMonome (Polynome p, Monome m)
{
	Element *newelem;
/* On vérifie que le monome n'est pas nul, car dans ce cas l'ajout est inutile*/
	if (m.coef != 0)
	{
/* On déclare un pointeur sur la tête du polynome afin de l'utiliser par la suite pour parcourir le polynome.
On vérfie aussi que le polynome n'est pas nul, car sinon l'ajout est trivial.*/
			Element *temp = p.tete;
			if (p.taille != 0)
			{
/* On compare le degré de notre monome à celui du monome de tête :
si c'est égal, on ajoute les coefficients, s'il est inférieur on ajoute le monome en tête.*/
                		if ((temp->monome).deg == m.deg)
                		{
                		    (temp->monome).coef = (temp->monome).coef + m.coef;
                		    if ((temp->monome).coef == 0)
                            {
                                p = supprimerMonome (p,(temp->monome).deg);
                            }
                		}
                		else
                        {
                            if (m.deg < (temp->monome).deg)
                            {
                                p = ajouterMonomeTete(p, m);
                            }
/* Si le degré du monome m est supérieur à celui de la tête, on commence à parcourir le polynome jusqu'au moment propice pour ajouter le monome.
C'est à dire jusqu'à ce que le degré du monome soit compris entre deux autres monomes de degrés supérieur et inférieur,
ou jusqu'à ce que l'on arrive à la fin du polynome, et donc que le degré du monome est supérieur à tous les autres degrés des monomes du polynome.*/
                            else
                            {
                                while ((temp->monome).deg < m.deg && temp->next != NULL)
                                {
                                    temp = temp->next;
                                }
                                newelem = (Element*) malloc(sizeof(Element));
                                newelem->monome = m;
/* Une fois le pointeur au bon endroit, on regarde dans quel cas, de ceux cités ci-dessus, on se trouve, et on applique le traitement correspondant.*/
                                if ((temp->monome).deg == m.deg)
                                {
                                    (temp->monome).coef = (temp->monome).coef + m.coef;
                                    if ((temp->monome).coef == 0)
                                    {
                                        p = supprimerMonome (p, (temp->monome).deg);
                                    }
                                }
                                else if (((temp->monome).deg) > m.deg)
                                {
                                    newelem->next = temp;
                                    newelem->prev = temp->prev;
                                    (temp->prev)->next = newelem;
                                    temp->prev = newelem;
                                    p.taille++;
                                }
                                else
                                {
                                    p = ajouterMonomeQueue (p, m);
                                }
                            }
                        }
			}
/* Si notre polynome est vide, il suffit d'ajouter en tête ou en queue notre monome au polynome.*/
			else
            {
                p = ajouterMonomeTete(p, m);
            }
	}
/* Il suffit de retourner le polynome ainsi traité (ou pas si l'un des deux paramètres est nul)*/
	return p;
}

/*Cette fonction prend en paramètre un polynome et suprime le monome en tête du polynome. Elle renvoie ensutie un polynome.
La fonction ne dinstingue pas les cas limites : son utilisation ne se fait que dans des cas "sécurisés"*/
Polynome supprimerMonomeTete (Polynome p)
{
    Element *temp;
    temp = p.tete;
    if (p.taille == 1)
    {
        free(temp);
		temp = NULL;
		return creerPolynome();
    }
    else
    {
        ((temp)->next)->prev = NULL;
        p.tete = (p.tete)->next;
        free (temp);
		temp = NULL;
        p.taille--;
        return p;
    }
}

/* Cette fonction prend en paramètre un polynome p et un entier deg et renvoie un polynome.
Elle suprime le monome voulu du polynome au début, au milieu ou à la fin de ce dernier, en fonction du degré du monome, entré en paramètre.*/
Polynome supprimerMonome (Polynome p, int deg)
{
        Element *temp;
        temp = p.tete;
        if (p.taille != 0)
        {
            if (deg == (temp->monome).deg)
            {
                p = supprimerMonomeTete (p);
                return p;
            }
            else
            {
                while ((temp->monome).deg < deg && temp != NULL)
                {
                    temp = temp->next;
                }
                if ((temp->monome).deg == deg)
                {
                    (temp->prev)->next = temp->next;
                    if (temp->next!=NULL)(temp->next)->prev = temp->prev;
                    else
                    {
                        p.last = temp->prev;
                        p.hdeg = ((temp->prev)->monome).deg;
                    }
                    free(temp);
                    temp = NULL;
                    p.taille--;
                    return p;
                }
                else
                {
                    return p;
                }
            }
        }
        return p;
}

/* Cette fonction prend en paramètre deux polynomes et les ajoute dans un autre polynome.
On renvoie ensuite ce deriner polynome.*/
Polynome additionner (Polynome p, Polynome q)
{
    Polynome a;
    float som_coef;
    Element *data1, *data2;
    data1 = p.tete;
    data2 = q.tete;
    a = creerPolynome ();
    if (p.taille !=0 && q.taille !=0)
    {
        while (data1 != NULL && data2 != NULL)
        {
            if ((data1->monome).deg == (data2->monome).deg)
            {
                som_coef = (data1->monome).coef + (data2->monome).coef;
                if (som_coef != 0)
                {
                    a = ajouterMonome (a, creerMonome(som_coef,(data1->monome).deg));
                }
                data1 = data1->next;
                data2 = data2->next;
            }
            else
            {
                if ((data1->monome).deg < (data2->monome).deg)
                {
                    a = ajouterMonome (a, creerMonome((data1->monome).coef,(data1->monome).deg));
                    data1 = data1->next;
                }
                else
                {
                    a = ajouterMonome (a, creerMonome((data2->monome).coef,(data2->monome).deg));
                    data2 = data2->next;
                }
            }
        }
        if (data1 == NULL)
        {
            while (data2 != NULL)
            {
                a = ajouterMonome(a,creerMonome((data2->monome).coef,(data2->monome).deg));
                data2 = data2->next;
            }
        }
        else
        {
            while (data1 != NULL)
            {
                a = ajouterMonome(a,creerMonome((data1->monome).coef,(data1->monome).deg));
                data1 = data1->next;
            }
        }
    }
    else
    {
        if (p.taille == 0)
        {
            a = q;
        }
        else
        {
            a = p;
        }
    }
    return a;
}

/* Cette fonction prend en paramètre deux polynomes et les multiplie dans un autre polynome.
On renvoie ensuite ce deriner polynome.*/
Polynome multiplier (Polynome p, Polynome q)
{
    Polynome a;
    float prod_coef;
    int som_deg;
    Element *data1, *data2;
    data1 = p.tete;
    data2 = q.tete;
    a = creerPolynome ();
    if (p.taille !=0 && q.taille !=0)
    {
        while (data1 != NULL)
        {
            while (data2 != NULL)
            {
                prod_coef = (data1->monome).coef * (data2->monome).coef;
                som_deg = (data1->monome).deg + (data2->monome).deg;
                a = ajouterMonome (a, creerMonome (prod_coef,som_deg));
                data2 = data2->next;
            }
            data1 = data1->next;
            data2 = q.tete;
        }
    }
    return a;
}

/*Cette fonction prend en paramètre un monome. Elle dérive une fois ce monome et renvoie le monome ainsi formé.*/
Monome mderiverUnefois (Monome m)
{
    if (m.coef != 0)
    {
        m.coef = m.coef * m.deg;
        if (m.deg != 0)
        {
            m.deg--;
        }
    }
    return m;
}

/*Cette fonction prend en paramètre un monome et un entier k. On dérvie k-fois le monome en lui appliquant k-fois la fonction pour dériver une fois le monome.
On renvoie ensuite le monome ainsi formé.*/
Monome mderiver (Monome m, int k)
{
    int i=0;
    while (m.coef !=0 && i<k)
    {
        m = mderiverUnefois (m);
        i++;
    }
    return m;
}

/*Cette fonction prend en paramètre un polynome. Elle dérive une fois ce polynome en dérivant chaque monome séparement.
On stocke ces monomes dérivés dans un polynome et renvoie le polynome ainsi formé.*/
Polynome pderiverUnefois (Polynome p)
{
    Polynome a;
    Element *temp;
    a = creerPolynome ();
    temp = p.tete;
    while (temp != NULL)
    {
        a = ajouterMonome (a, mderiverUnefois(temp->monome));
        temp = temp->next;
    }
    return a;
}

/*Cette fonction prend en paramètre un polynome et un entier k. On dérvie k-fois le polynome en lui appliquant k-fois la fonction pour dériver une fois le polynome.
On stocke puis on renvoie ensuite le polynome ainsi formé.*/
Polynome pderiver (Polynome p, int k)
{
    int i;
    for (i=0; i<k; i++)
    {
        p = pderiverUnefois (p);
    }
    return p;
}

/*Cette fonction prend en paramètre un monome. Elle affiche le monome en fonction des coefficients et des degrés, en se rapprochant le plus de l'écriture traditionnelle mathématique.*/
void afficherMonome (Monome m)
{
    if (m.deg == 0)
    {
        printf ("%.2f",m.coef);
    }
    else
    {
        if (m.deg == 1)
        {
            if (m.coef == 1)
			{
				printf ("x");
			}
			else
			{
				printf ("%.2fx",m.coef);
			}
        }
        else
        {

			if (m.coef == 1)
			{
				printf ("x^%d",m.deg);
			}
			else
			{
				printf ("%.2fx^%d",m.coef,m.deg);
			}
        }
    }
}

/*Cette fonction prend en paramètre un polynome. Elle affiche le polynome en se rapprochant le plus de l'écriture traditionnelle mathématique.*/
void afficherPolynome (Polynome p)
{
    if (p.taille != 0)
	{
		Element *temp;
    	temp = p.tete;
    	while (temp->next != NULL)
    	{
    	    afficherMonome (temp->monome);
    	    printf(" + ");
    	    temp = temp->next;
    	}
    	afficherMonome (temp->monome);
    	printf ("\n");
	}
	else
	{
		printf("Le polynome est nul");
	}
}

/*Cette fonction ne prend aucun paramètre. Elle renvoie un monome créé interactivement avec l'utilisateur.*/
Monome creerMonomeInteraction ()
{
    Monome m;
    float coefficient;
    int degre;
    printf("Entrez le degre du monome : ");
    scanf("%d",&degre);
    printf("Entrez le coefficient du monome : ");
    scanf("%f",&coefficient);
    m = creerMonome(coefficient, degre);
    printf("\n");
    return m;
}

/*Cette fonction ne prend aucun paramètre. Elle renvoie un polynome créé interactivement avec l'utilisateur.*/
Polynome creerPolynomeInteraction()
{
    Polynome p;
    char choix = 0;
    p = creerPolynome();
    do
    {
	p = ajouterMonome (p, creerMonomeInteraction());
	printf("Voulez-vous ajouter un autre monome au polynome ? (o/n) : ");
	do
        {
	    scanf("%c",&choix);
        } while (choix != 'o' && choix != 'n');
    } while (choix == 'o');
    printf("Votre polynome a bien ete cree. \n");
    return p;
}
