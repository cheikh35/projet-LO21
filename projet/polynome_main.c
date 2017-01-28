#include "polynome.h"
#include <stdio.h>
#include <stdlib.h>

int main()
{
    /*On déclare et initialise toutes les variables utiles pour la suite*/
    char choix2=0;
    int choix=0, place=0, place2=0, i, diff=0, deg;
    /*On déclare un tableau de polynômes de taille 10 : on ne peut manipuler que 10 polynômes à la fois.*/
    Polynome P[10], p;
    printf ("Bienvenue dans le programme de manipulation de polynomes.\n");
    /*On initialise le tableau de polynômes avec des polynômes nuls.*/
    for (i=0;i<10;i++)
    {
        P[i] = creerPolynome ();
    }
    /*Le programme continue de s'exécuter tant que l'utilisateur n'a pas choisi l'option 10 : Quitter le programme.*/
    while (choix != 10)
    {
        choix = 0;
        /*On affiche le menu principal et on demande à l'utilisateur d'entrer une valeur correcte pour poursuivre.*/
        printf ("Que voulez-vous faire ?\n\t1. Creer un nouveau polynome\n\t2. Supprimer un polynome\n\t3. Ajouter un monome a un polynome\n\t4. Supprimer un monome a un polynome\n\t5. Additionner deux polynomes\n\t6. Multiplier deux polynomes\n\t7. Deriver un polynome\n\t8. Afficher un polynome\n\t10. Quitter le programme\nChoix : ");
        do
        {
            scanf ("%d",&choix);
        } while (choix !=1 && choix !=2 && choix !=3 && choix !=4 && choix !=5 && choix !=6 && choix !=7 && choix !=8 && choix !=10);
        printf("\n");
    	switch (choix)
    	{
    	    /*Cas 1 : Creer un nouveau polynome*/
            case 1 :
            {
                p = creerPolynomeInteraction ();
                printf ("\nDans quelle place voulez-vous memoriser votre polynome ? (1 a 10) : ");
                do
                {
                    scanf ("%d",&place);
                } while (place !=1 && place !=2 && place !=3 && place !=4 && place !=5 && place !=6 && place !=7 && place !=8 && place !=9 && place !=10);
                P[place-1] = p;
                printf("\nPolynome : ");
                afficherPolynome (P[place-1]);
                printf ("\nAppuyez sur une touche pour continuer ... \n");
                getchar();
                getchar();
                place = 0;
            } break;
            /*Cas 2 : Supprimer un polynome*/
            case 2 :
            {
                printf ("Dans quelle place se trouve le polynome à supprimer ? (1 a 10) : ");
                do
                {
                    scanf ("%d",&place);
                } while (place !=1 && place !=2 && place !=3 && place !=4 && place !=5 && place !=6 && place !=7 && place !=8 && place !=9 && place !=10);
                while ((P[place-1]).taille !=0)
                {
                    P[place-1] = supprimerMonomeTete (P[place-1]);
                }
                place = 0;
            } break;
            /*Cas 3 : Ajouter un monome a un polynome*/
            case 3 :
            {
                printf ("Dans quelle place se trouve le polynome auquel on doit ajouter un monome ? (1 a 10) : ");
                do
                {
                    scanf ("%d",&place);
                } while (place !=1 && place !=2 && place !=3 && place !=4 && place !=5 && place !=6 && place !=7 && place !=8 && place !=9 && place !=10);
                P[place-1] = ajouterMonome (P[place-1], creerMonomeInteraction ());
                place = 0;
            } break;
            /*Cas 4 : Supprimer un monome a un polynome*/
            case 4 :
            {
                printf ("Dans quelle place se trouve le polynome auquel on doit supprimer un monome ? (1 a 10) : ");
                do
                {
                    scanf ("%d",&place);
                } while (place !=1 && place !=2 && place !=3 && place !=4 && place !=5 && place !=6 && place !=7 && place !=8 && place !=9 && place !=10);
                printf ("Quel est le degre du monome a supprimer ? : ");
                scanf("%d",&deg);
                P[place-1] = supprimerMonome (P[place-1] , deg);
                place = 0;
            } break;
            /*Cas 5 : Additionner deux polynomes*/
            case 5 :
            {
                printf ("Dans quelle place se trouve le premier polynome ? (1 a 10) : ");
                do
                {
                    scanf ("%d",&place);
                } while (place !=1 && place !=2 && place !=3 && place !=4 && place !=5 && place !=6 && place !=7 && place !=8 && place !=9 && place !=10);
                printf ("Dans quelle place se trouve le second polynome ? (1 a 10) : ");
                do
                {
                    scanf ("%d",&place2);
                } while (place2 !=1 && place2 !=2 && place2 !=3 && place2 !=4 && place2 !=5 && place2 !=6 && place2 !=7 && place2 !=8 && place2 !=9 && place2 !=10);
                p = additionner (P[place-1], P[place2-1]);
                printf("\nSomme : ");
                afficherPolynome (p);
                place = 0; place2= 0;
                printf("Souhaitez-vous conserver ce polynome ? (o/n) : ");
                do
                {
                scanf("%c",&choix2);
                } while (choix2 != 'o' && choix2 != 'n');
                if (choix2 == 'o')
                {
                    printf ("Dans quelle place voulez-vous memoriser votre polynome ? (1 a 10) : ");
                    do
                    {
                        scanf ("%d",&place);
                    } while (place !=1 && place !=2 && place !=3 && place !=4 && place !=5 && place !=6 && place !=7 && place !=8 && place !=9 && place !=10);
                    P[place-1] = p;
                    place = 0;
                }
                choix2 = 0;
            } break;
            /*Cas 6 : Multiplier deux polynomes*/
            case 6 :
            {
                printf ("Dans quelle place se trouve le premier polynome ? (1 a 10) : ");
                do
                {
                    scanf ("%d",&place);
                } while (place !=1 && place !=2 && place !=3 && place !=4 && place !=5 && place !=6 && place !=7 && place !=8 && place !=9 && place !=10);
                printf ("Dans quelle place se trouve le second polynome ? (1 a 10) : ");
                do
                {
                    scanf ("%d",&place2);
                } while (place2 !=1 && place2 !=2 && place2 !=3 && place2 !=4 && place2 !=5 && place2 !=6 && place2 !=7 && place2 !=8 && place2 !=9 && place2 !=10);
                p = multiplier (P[place-1], P[place2-1]);
                printf("\nProduit : ");
                afficherPolynome (p);
                place = 0; place2= 0;
                printf("Souhaitez-vous conserver ce polynome ? (o/n) : ");
                do
                {
                    scanf("%c",&choix2);
                } while (choix2 != 'o' && choix2 != 'n');
                if (choix2 == 'o')
                {
                    printf ("Dans quelle place voulez-vous memoriser votre polynome ? (1 a 10) : ");
                    do
                    {
                        scanf ("%d",&place);
                    } while (place !=1 && place !=2 && place !=3 && place !=4 && place !=5 && place !=6 && place !=7 && place !=8 && place !=9 && place !=10);
                    P[place-1] = p;
                    place = 0;
                }
                choix2 = 0;
            } break;
            /*Cas 7 : Deriver un polynome*/
            case 7 :
            {
                printf ("Dans quelle place se trouve le polynome a deriver ? (1 a 10) : ");
                do
                {
                    scanf ("%d",&place);
                } while (place !=1 && place !=2 && place !=3 && place !=4 && place !=5 && place !=6 && place !=7 && place !=8 && place !=9 && place !=10);
                printf("Combien de fois voulez-vous deriver ce polynome ?");
                do
                {
                    scanf("%d",&diff);
                } while (diff<=0);
                p = pderiver (P[place-1], diff);
                printf ("\n%d-eme derivee : ",diff);
                afficherPolynome (p);
                place = 0;
                printf ("Souhaitez-vous conserver ce polynome ? (o/n) : ");
                do
                {
                    scanf("%c",&choix2);
                } while (choix2 != 'o' && choix2 != 'n');
                if (choix2 == 'o')
                {
                    printf ("Dans quelle place voulez-vous memoriser votre polynome ? (1 a 10) : ");
                    do
                    {
                        scanf ("%d",&place);
                    } while (place !=1 && place !=2 && place !=3 && place !=4 && place !=5 && place !=6 && place !=7 && place !=8 && place !=9 && place !=10);
                    P[place-1] = p;
                    place = 0;
                }
                choix2 = 0; diff = 0;
            } break;
            /*Cas 8 : Afficher un polynome*/
            case 8 :
            {
                printf ("Dans quelle place se trouve le polynome a afficher ? (1 a 10) : ");
                do
                {
                    scanf ("%d",&place);
                } while (place !=1 && place !=2 && place !=3 && place !=4 && place !=5 && place !=6 && place !=7 && place !=8 && place !=9 && place !=10);
                printf ("\nPolynome %d : ",place);
                afficherPolynome (P[place-1]);
                place = 0;
                printf ("\nAppuyez sur une touche pour continuer ... \n");
                getchar();
                getchar();
            } break;
            /*Cas 10 : Quitter le programme*/
            case 10 :
            {
                printf ("Merci pour votre utilisation.");
                printf ("\nAppuyez sur une touche pour quitter ... \n");
                getchar();
                getchar();
            }
        }
    system("clear");
    }
    return 0;
}
