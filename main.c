#include "graphe.h"
#include "algo.h"

int main(){
  char nom[] = "grapheColorado.csv";
  //char nom[] = "graphe1.txt";
  GRAPHE G;
  T_SOMMET d, a;
  L_ARC L;
  /*d.nom = calloc(1, 4*sizeof(char));
  a.nom = calloc(1, 4*sizeof(char));
  d.nom = "Aaa";
  a.nom = "Haa";*/
  
  G = ouvrirGraphe(nom);
  printf("Chargé !\n");
  //afficherGraphe(G);
  d = G.sommets[5];
  //a = G.sommets[10000];
  a = G.sommets[50];
  //printf("mais pk ?\n");
  L = plusCourtChemin(G, d, a);
  afficherChemin(L);
  printf("%lf\n", longueurChemin(L));
  libererGraphe(G);
  return 0;
}
