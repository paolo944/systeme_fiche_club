#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef ADHERENT_H
#define ADHERENT_H

struct Adherent
{
    char *nom;
    char *nomParent;
    char *prenom;
    char creneau; //Numéro du créneau correspondant
    char bonneuil; //1 si de Bonneuil 0 sinon
    char *dateDeNaissance;
    char *adresse;
    char *codePostale;
    char *telephone;
    char *mail;
    char compet; //1 si oui 0 sinon
};

struct Liste_Ad_elem
{
    struct Adherent *ad;
    struct Liste_Ad_elem *next;
    struct Liste_Ad_elem *prev;
};

//Liste doublement chaînée
struct Liste_Ad
{
    struct Liste_Ad_elem *first;
    struct Liste_Ad_elem *last;
};

//Ecris le contenu de la structure Adherent ad dans un fichier csv file
int write_ad(struct Adherent *ad, char const *file);

//Ecris la liste des adhérents de un fichier file csv
int write_liste_ad(struct Liste_Ad *l, const char *file);

//Créer et retourne une structure d'adhérent avec les informations données
struct Adherent *create_ad(char *nom, char *nomParent, char *prenom, char creneau, 
                                char bonneuil, char *dateDeNaissance, char *adresse, 
                                char *codePostale, char *telephone, char *mail, char compet);

//Lis un fichier csv et initialise une liste d'adhérents
struct Liste_Ad *read_csv(const char *file);

//Initialise une liste d'adhérents
int init_liste(struct Liste_Ad *l);

//Ajoute l'adhérent ad à la fin de la liste l
int add_last_ad(struct Liste_Ad *l, struct Adherent *ad);

//Ajoute l'adhérent au début de la liste l
int add_first_ad(struct Liste_Ad *l, struct Adherent *ad);

//Retourne le dernier adhérent de la liste et le supprime de celle-ci
struct Adherent *PopBack(struct Liste_Ad *l);

//Retourne le premier adhérent de la liste et le supprime de celle-ci
struct Adherent *PopFront(struct Liste_Ad *l);

//Affiche l'adhérent ad donnée à la fonction
int print_ad(struct Adherent *ad);

//Affiche la liste des adhérents contenus dans la liste
int print_liste_ad(struct Liste_Ad *l);

//Libère la mémoire de l'adhérent ad donnée à la fonction
int free_ad(struct Adherent *ad);

//Libère la liste l donnée à la fonction
int free_liste(struct Liste_Ad *l);

//Lis les informations d'un utilisateur dans le terminal et les ajoute à la liste donnée
void read_terminal(struct Liste_Ad *liste);

#endif