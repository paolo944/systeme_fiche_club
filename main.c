#include "adherent.h"

int main(int argc, char **argv){

    struct Liste_Ad *l = read_csv("bdd.csv");

    free_liste(l);

    read_terminal(l);

    print_liste_ad(l);

    return 0;
}