#include "graphe.h"
#include "algo.h"

int main(void){
  char nom[] = "grapheColorado.csv";
  GRAPHE G;
  T_SOMMET d, a;
  L_ARC L;
  int depart, arrivee;
  G = ouvrirGraphe(nom);
  printf("Le graphe %s est chargé !\n",nom);
  printf("Sommet de départ ?:\n");
  //scanf(&depart); peu pratique pour chronométrer le programme
  printf("Sommet d'arrivée ?:\n");
  //scanf(&arrivee);
  d = G.sommets[5];
  a = G.sommets[100];
  /* Dans le cas des stations de métro il faut décommenter les trois lignes qui suivent
  char depart_nom[100];
  scanf("%s", depart_nom);
  ajouterChoixDepart(G, depart_nom);
  */
  L = plusCourtChemin(G, d, a);
  afficherChemin(L);
  printf("%lf\n", longueurChemin(L));
  printf("%d", arrivee);
  libererGraphe(G);
  return 0;
}
