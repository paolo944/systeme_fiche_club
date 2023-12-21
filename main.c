#include "adherent.h"

int main(int argc, char **argv){

    struct Liste_Ad *l = read_csv("bdd.csv");

    read_terminal(l);

    print_liste_ad(l);

    write_liste_ad(l, "bdd.csv");

    free_liste(l);

    return 0;
}