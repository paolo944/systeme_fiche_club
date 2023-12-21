#include "adherent.h"

int write_ad(struct Adherent *ad, const char *file){
    FILE *fp = fopen(file, "a+");
    if(fp == NULL){
        fprintf(stderr, "erreur pendant l'ouverture du fichier\n");
        return -1;
    }
    
    fprintf(fp, "%s,", ad->nom);
    if(ad->nomParent)
        fprintf(fp, "%s,", ad->nomParent);   
    else
        fprintf(fp,",");

    fprintf(fp, "%s,", ad->prenom);
    switch (ad->creneau)
    {
    case '0':
        fprintf(fp, "Lundi 17h,");
        break;
    case '1':
        fprintf(fp, "Lundi 18h,");
        break;
    case '2':
        fprintf(fp, "Lundi 19h,");
        break;
    case '3':
        fprintf(fp, "Lundi 20h,");
        break;
    case '4':
        fprintf(fp, "Mardi 20h,");
        break;
    case '5':
        fprintf(fp, "Mercredi 13h30,");
        break;
    case '6':
        fprintf(fp, "Samedi 12h45,");
        break;
    case '7':
        fprintf(fp, "Lundi 18h,");
        break;
    case '8':
        fprintf(fp, "Lundi 19h30,");
        break;
    case '9':
        fprintf(fp, "Mercredi 19h,");
        break;
    
    default:
        fprintf(stderr, "Créneau non reconnu\n");
        break;
    }

    if(ad->bonneuil == '1')
        fprintf(fp, "Oui,");
    else
        fprintf(fp, "Non,");
    
    fprintf(fp, "%s,%s,%s,%s,%s", ad->dateDeNaissance,
    ad->adresse, ad->codePostale, ad->telephone,
    ad->mail);

    if(ad->compet == '1')
        fprintf(fp, "Oui\n");
    else
        fprintf(fp, "Non\n");

    fclose(fp);

    return 0;
}

int write_liste_ad(struct Liste_Ad *l, const char *file){
    if(l == NULL)
        return 0;
    struct Liste_Ad_elem *tmp = l->first;
    while(tmp){
        write_ad(tmp->ad, file);
        tmp = tmp->next;
    }
    return 0;
}

struct Adherent *create_ad(char *nom, char *nomParent, char *prenom, char creneau, 
                                char bonneuil, char *dateDeNaissance, char *adresse, 
                                char *codePostale, char *telephone, char *mail, char compet) {
    struct Adherent *newAdherent = malloc(sizeof(struct Adherent));
    if (newAdherent == NULL) {
        // Handle memory allocation error
        return NULL;
    }

    newAdherent->nom = strdup(nom);
    newAdherent->nomParent = strdup(nomParent);
    newAdherent->prenom = strdup(prenom);
    newAdherent->creneau = creneau;
    newAdherent->bonneuil = bonneuil;
    newAdherent->dateDeNaissance = strdup(dateDeNaissance);
    newAdherent->adresse = strdup(adresse);
    newAdherent->codePostale = strdup(codePostale);
    newAdherent->telephone = strdup(telephone);
    newAdherent->mail = strdup(mail);
    newAdherent->compet = compet;

    return newAdherent;
}

struct Liste_Ad *read_csv(const char *file) {
    FILE *fp = fopen(file, "r");
    if (!fp) {
        perror("Unable to open file");
        return NULL;
    }

    struct Liste_Ad *liste = malloc(sizeof(struct Liste_Ad));
    if (!liste) {
        fclose(fp);
        return NULL;
    }
    init_liste(liste);

    char line[256];

    // Skip the first line (header)
    if (!fgets(line, sizeof(line), fp)) {
        // Handle potential error or empty file
        fclose(fp);
        free(liste);
        return NULL;
    }

    while (fgets(line, sizeof(line), fp)) {
        // Assuming the CSV format is:
        // nom,prenom,creneau,bonneuil,dateDeNaissance,adresse,codePostale,telephone,mail,compet
        char *nom = strtok(line, ",");
        char *nomParent = strtok(NULL, ",");
        char *prenom = strtok(NULL, ",");
        char creneau = strtok(NULL, ",")[0];
        char bonneuil = strtok(NULL, ",")[0];
        char *dateDeNaissance = strtok(NULL, ",");
        char *adresse = strtok(NULL, ",");
        char *codePostale = strtok(NULL, ",");
        char *telephone = strtok(NULL, ",");
        char *mail = strtok(NULL, ",");
        char compet = strtok(NULL, "\n")[0];

        struct Adherent *ad = create_ad(nom, nomParent, prenom, creneau, bonneuil, dateDeNaissance, 
                                             adresse, codePostale, telephone, mail, compet);
        if (!ad) {
            fprintf(stderr, "erreur pendant l'allocation d'un adhérent de la liste\n");
            return NULL;
        }

        add_last_ad(liste, ad);
    }

    fclose(fp);
    return liste;
}

int init_liste(struct Liste_Ad *l){
    l->first = NULL;
    l->last = NULL;

    return 0;
}

int add_last_ad(struct Liste_Ad *l, struct Adherent *ad){
    struct Liste_Ad_elem *elem = (struct Liste_Ad_elem *)malloc(sizeof(struct Liste_Ad_elem));
    
    if(elem == NULL){
        fprintf(stderr, "erreur pendant l'allocation\n");
        return -1;
    }

    elem->ad = ad;
    elem->next = NULL;
    elem->prev = l->last;
    if(l->last)
        l->last->next = elem;
    else
        l->first = elem;
    l->last = elem;
    return 0;
}

int add_first_ad(struct Liste_Ad *l, struct Adherent *ad){
    struct Liste_Ad_elem *elem = (struct Liste_Ad_elem *)malloc(sizeof(struct Liste_Ad_elem));
    
    if(elem == NULL){
        fprintf(stderr, "erreur pendant l'allocation\n");
        return -1;
    }

    elem->ad = ad;
    elem->next = l->first;
    elem->prev = NULL;
    if(l->first)
        l->first->prev = elem;
    else
        l->last = elem;
    l->first = elem;

    return 0;
}

struct Adherent *PopBack(struct Liste_Ad *l){
    struct Adherent *ad = NULL;

    struct Liste_Ad_elem *tmp = l->last;
    if(tmp == NULL)
        return NULL;
    
    ad = tmp->ad;
    l->last = tmp->prev;
    if(l->last)
        l->last->next = NULL;
    else
        l->first = NULL;
    free(tmp);
    return ad;
}

struct Adherent *PopFront(struct Liste_Ad *l){
    struct Adherent *ad = NULL;

    struct Liste_Ad_elem *tmp = l->first;
    if(tmp == NULL)
        return NULL;
    
    ad = tmp->ad;
    l->first = tmp->next;
    if(l->first)
        l->first->prev = NULL;
    else
        l->last = NULL;
    free(tmp);
    return ad;
}

int print_ad(struct Adherent *ad){
    if(ad == NULL){
        return -1;
    }

    fprintf(stdout, "Nom: %s\n", ad->nom);
    if(ad->nomParent)
        fprintf(stdout, "Nom Parents: %s\n", ad->nomParent);   

    fprintf(stdout, "Prénom: %s\n", ad->prenom);
    switch (ad->creneau)
    {
    case '0':
        fprintf(stdout, "Lundi 17h\n");
        break;
    case '1':
        fprintf(stdout, "Lundi 18h\n");
        break;
    case '2':
        fprintf(stdout, "Lundi 19h\n");
        break;
    case '3':
        fprintf(stdout, "Lundi 20h\n");
        break;
    case '4':
        fprintf(stdout, "Mardi 20h\n");
        break;
    case '5':
        fprintf(stdout, "Mercredi 13h30\n");
        break;
    case '6':
        fprintf(stdout, "Samedi 12h45\n");
        break;
    case '7':
        fprintf(stdout, "Lundi 18h\n");
        break;
    case '8':
        fprintf(stdout, "Lundi 19h30\n");
        break;
    case '9':
        fprintf(stdout, "Mercredi 19h\n");
        break;
    
    default:
        fprintf(stderr, "Créneau non reconnu\n");
        break;
    }

    if(ad->bonneuil == '1')
        fprintf(stdout, "Bonneuil: Oui\n");
    else
        fprintf(stdout, "Bonneui: Non\n");
    
    fprintf(stdout, "Date de naissance: %s\n\
    Adresse: %s\n\
    Code postale: %s\n\
    Telephone: %s\n\
    Mail: %s\n", ad->dateDeNaissance,
    ad->adresse, ad->codePostale, ad->telephone,
    ad->mail);

    if(ad->compet == '1')
        fprintf(stdout, "Compétition: Oui\n");
    else
        fprintf(stdout, "Compétition: Non\n");

    return 0;
}

int print_liste_ad(struct Liste_Ad *l){
    struct Liste_Ad_elem *tmp = l->first;
    while(tmp){
        print_ad(tmp->ad);
        fprintf(stdout, "\n");
        tmp = tmp->next;
    }
    return 0;
}

int free_ad(struct Adherent *ad){
    if(ad == NULL)
        return 0;
    free(ad->nom);
    if(ad->nomParent)
        free(ad->nomParent);
    free(ad->prenom);
    free(ad->dateDeNaissance);
    free(ad->adresse);
    free(ad->mail);
    free(ad);
    return 0;
}

int free_liste(struct Liste_Ad *l){
    if(l == NULL || l->first == NULL)
        return 0;
    struct Liste_Ad_elem *tmp = l->first;
    struct Liste_Ad_elem *tmp2 = NULL;
    while(tmp){
        free_ad(tmp->ad);
        tmp2 = tmp;
        tmp = tmp->next;
        free(tmp2);
    }
    free(l);
    return 0;
}

static void trimNewline(char *str) {
    int len = strlen(str);
    if (len > 0 && str[len - 1] == '\n') {
        str[len - 1] = '\0';
    }
}

void read_terminal(struct Liste_Ad *liste) {
    char nom[100], nomParent[100], prenom[100], dateDeNaissance[100], adresse[200], mail[100], codePostale[6], telephone[11];;
    char creneau, bonneuil, compet;

    printf("Entrez nom: ");
    fgets(nom, sizeof(nom), stdin);
    trimNewline(nom);

    printf("Entrez nom parent: ");
    fgets(nom, sizeof(nomParent), stdin);
    trimNewline(nomParent);
    
    printf("Entrez prenom: ");
    fgets(prenom, sizeof(prenom), stdin);
    trimNewline(prenom);

    printf("Entrez creneau: ");
    scanf(" %c", &creneau); // Note the space before %c to skip any whitespace

    printf("Entrez bonneuil (1 pour oui, 0 pour non): ");
    scanf(" %c", &bonneuil);

    printf("Entrez date de naissance: ");
    scanf("%99s", dateDeNaissance);

    printf("Entrez adresse: ");
    scanf("%199s", adresse);

    printf("Entrez code postale: ");
    scanf("%6s", codePostale);

    printf("Entrez telephone: ");
    scanf("%11s", telephone);

    printf("Entrez mail: ");
    scanf("%99s", mail);

    printf("Enter compet (1 for yes, 0 for no): ");
    scanf(" %c", &compet);

    struct Adherent *ad = create_ad(nom, nomParent, prenom, creneau, bonneuil, dateDeNaissance, 
                                         adresse, codePostale, telephone, mail, compet);
    if (ad == NULL) {
        fprintf(stderr, "Failed to create adherent\n");
        return;
    }

    add_last_ad(liste, ad);
}