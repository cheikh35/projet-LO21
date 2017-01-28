/*Auteur : Hamza JAFFALI ; Projet : Manipulation Polynomes*/

#include "polynome.h"
#include <stdio.h>
#include <stdlib.h>

/*Cette fonction prend en param�tre un r�el et un entier, constituant respectivement le coefficien et le degr� du monome � cr�er.
Elle renvoie ensuite le monome ainsi g�n�r�.*/
Monome creerMonome (float a, int k)
{
/*On d�clare un monome m*/
	Monome m;
/*On affecte le coefficient/degr� voulu au monome*/
	m.coef = a;
	m.deg = k;
/*On renvoie le monome ainsi g�n�r�*/
	return m;
}

/*Cette fonction ne prend aucun param�tre, et renvoie un polynome vide initialis� en tant que polynome nul*/
Polynome creerPolynome ()
{
/*On d�clare un polynome p*/
	Polynome p;
/*On initialise p comme un polynome nul (vide)*/
	p.tete = NULL;
	p.last = NULL;
	p.taille = 0;
	p.hdeg = 0;
/*On renvoie le polynome ainsi g�n�r�*/
	return p;
}

/*Cette fonction prend en param�tre un polynome et un monome, et ajoute ce monome en t�te du polynome. On renvoie ensuite un polynome.
La fonction ne dinstingue pas les cas limites : son utilisation ne se fait que dans des cas "s�curis�s"*/
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

/*Cette fonction prend en param�tre un polynome et un monome, et ajoute ce monome en queue du polynome. On renvoie ensuite un polynome.
La fonction ne dinstingue pas les cas limites : son utilisation ne se fait que dans des cas "s�curis�s"*/
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


/* Cette fonction prend en param�tre un polynome p et un monome m. Elle renvoie ensuite un polynome.
Elle ajoute le monome au polynome au d�but, au milieu ou � la fin de ce dernier en fonction du degr� du monome.*/
Polynome ajouterMonome (Polynome p, Monome m)
{
	Element *newelem;
/* On v�rifie que le monome n'est pas nul, car dans ce cas l'ajout est inutile*/
	if (m.coef != 0)
	{
/* On d�clare un pointeur sur la t�te du polynome afin de l'utiliser par la suite pour parcourir le polynome.
On v�rfie aussi que le polynome n'est pas nul, car sinon l'ajout est trivial.*/
			Element *temp = p.tete;
			if (p.taille != 0)
			{
/* On compare le degr� de notre monome � celui du monome de t�te :
si c'est �gal, on ajoute les coefficients, s'il est inf�rieur on ajoute le monome en t�te.*/
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
/* Si le degr� du monome m est sup�rieur � celui de la t�te, on commence � parcourir le polynome jusqu'au moment propice pour ajouter le monome.
C'est � dire jusqu'� ce que le degr� du monome soit compris entre deux autres monomes de degr�s sup�rieur et inf�rieur,
ou jusqu'� ce que l'on arrive � la fin du polynome, et donc que le degr� du monome est sup�rieur � tous les autres degr�s des monomes du polynome.*/
                            else
                            {
                                while ((temp->monome).deg < m.deg && temp->next != NULL)
                                {
                                    temp = temp->next;
                                }
                                newelem = (Element*) malloc(sizeof(Element));
                                newelem->monome = m;
/* Une fois le pointeur au bon endroit, on regarde dans quel cas, de ceux cit�s ci-dessus, on se trouve, et on applique le traitement correspondant.*/
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
/* Si notre polynome est vide, il suffit d'ajouter en t�te ou en queue notre monome au polynome.*/
			else
            {
                p = ajouterMonomeTete(p, m);
            }
	}
/* Il suffit de retourner le polynome ainsi trait� (ou pas si l'un des deux param�tres est nul)*/
	return p;
}

/*Cette fonction prend en param�tre un polynome et suprime le monome en t�te du polynome. Elle renvoie ensutie un polynome.
La fonction ne dinstingue pas les cas limites : son utilisation ne se fait que dans des cas "s�curis�s"*/
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

/* Cette fonction prend en param�tre un polynome p et un entier deg et renvoie un polynome.
Elle suprime le monome voulu du polynome au d�but, au milieu ou � la fin de ce dernier, en fonction du degr� du monome, entr� en param�tre.*/
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

/* Cette fonction prend en param�tre deux polynomes et les ajoute dans un autre polynome.
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

/* Cette fonction prend en param�tre deux polynomes et les multiplie dans un autre polynome.
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

/*Cette fonction prend en param�tre un monome. Elle d�rive une fois ce monome et renvoie le monome ainsi form�.*/
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

/*Cette fonction prend en param�tre un monome et un entier k. On d�rvie k-fois le monome en lui appliquant k-fois la fonction pour d�river une fois le monome.
On renvoie ensuite le monome ainsi form�.*/
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

/*Cette fonction prend en param�tre un polynome. Elle d�rive une fois ce polynome en d�rivant chaque monome s�parement.
On stocke ces monomes d�riv�s dans un polynome et renvoie le polynome ainsi form�.*/
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

/*Cette fonction prend en param�tre un polynome et un entier k. On d�rvie k-fois le polynome en lui appliquant k-fois la fonction pour d�river une fois le polynome.
On stocke puis on renvoie ensuite le polynome ainsi form�.*/
Polynome pderiver (Polynome p, int k)
{
    int i;
    for (i=0; i<k; i++)
    {
        p = pderiverUnefois (p);
    }
    return p;
}

/*Cette fonction prend en param�tre un monome. Elle affiche le monome en fonction des coefficients et des degr�s, en se rapprochant le plus de l'�criture traditionnelle math�matique.*/
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

/*Cette fonction prend en param�tre un polynome. Elle affiche le polynome en se rapprochant le plus de l'�criture traditionnelle math�matique.*/
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

/*Cette fonction ne prend aucun param�tre. Elle renvoie un monome cr�� interactivement avec l'utilisateur.*/
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

/*Cette fonction ne prend aucun param�tre. Elle renvoie un polynome cr�� interactivement avec l'utilisateur.*/
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
