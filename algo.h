#ifndef ALGO
#define ALGO
#include "graphe.h"

L_ARC ajoutArc(L_ARC L, T_ARC A);
L_ARC creerLArc();
L_ARC copieLArc(L_ARC L1, L_ARC L2);
int minimum(double *pcc, long int *C, int n);
int chercherSommet(T_SOMMET x, GRAPHE G);//Par son nom
int LArcEstVide(L_ARC L);
L_ARC plusCourtChemin(GRAPHE G, T_SOMMET d, T_SOMMET a);
#endif
