#include <float.h>

#include "algo.h"

L_ARC creerLArc(){
  return NULL;
}

L_ARC ajoutArc(L_ARC L, T_ARC A){
  L_ARC n;
  n = (L_ARC) calloc(1, sizeof(*n));
  if (n==NULL) {
      fprintf(stderr, "Erreur fatale, mémoire insuffisante");
      exit(1);
    }
  n->val = A;
  n->suiv = L;
  return n;
}

double chercherCout(L_ARC L, int sommet){//Combien cela coute-t-il d'aller au sommet ?
   while(!LArcEstVide(L)){
    if(L->val.arrivee == sommet){
       return L->val.cout;
    }
    L = L->suiv;
  }
  fprintf(stderr, "Erreur sommet inexistant");
  exit(1);
}

L_ARC copieLArc(L_ARC L1, L_ARC L2){//copie de L1 dans L2
  while(!LArcEstVide(L1)){
    L2 = ajoutArc(L2, L1->val);
    L1 = L1->suiv;
  }
  return L2;
}

int minimum(double *pcc, int *C, int n){
  int i;
  double m = DBL_MAX;
  int indice_m=-1;//a faire optimiser ceci ! 
  for(i=0; i<n; i++){
    if (C[i] != -1){
      if (pcc[i] < m){
	indice_m = i;
	m = pcc[i];
      }
    }
  }
  if(indice_m == -1){
    fprintf(stderr, "Erreur de minimum, liste vide ou chemin inexistant");
    exit(1);
  }
  else{
    return indice_m;
  }
}
int chercherSommet(T_SOMMET x, GRAPHE G){
  int i;
  char nom[256];
  strcpy(nom, x.nom);
  int taille = G.n;
  for(i=0; i<taille; ++i){
    if (!strcmp(G.sommets[i].nom, nom))
      return i;
  }
  fprintf(stderr, "Ce sommet n'existe pas !");
  exit(1);
}

int LArcEstVide(L_ARC L){
  if (L==NULL)
    return 1;
  else
    return 0;
 }

int appartient(int *S, int a){
  if (S[a] == a){
    return 1;
  }
  else{
    return 0;
  }
}

double longueurChemin(L_ARC L){
  double l = 0;
  while(!LArcEstVide(L)){
    l+=L->val.cout;
    L = L->suiv;
  }
  return l;
}

void afficherChemin(L_ARC L){
  while(!LArcEstVide(L)){
    printf("%d\n",L->val.arrivee);
    L = L->suiv;
  }
}
  
L_ARC plusCourtChemin(GRAPHE G, T_SOMMET d, T_SOMMET a){
  int taille = G.n;
  int d_int;
  int a_int;
  double *pcc = NULL;
  T_ARC arc;
  pcc = calloc(taille, sizeof(*pcc));
  if (pcc==NULL) {
      fprintf(stderr, "Erreur fatale, mémoire insuffisante pour pcc");
      exit(1);
    }
  int *pere = NULL;
  pere = calloc(taille, sizeof(*pere));
  if (pere==NULL) {
      fprintf(stderr, "Erreur fatale, mémoire insuffisante pere");
      exit(1);
    }
  int *C = NULL;
  int *S = NULL;
  C = calloc(taille, sizeof(*C));
  S = calloc(taille, sizeof(*C));
  if (C==NULL) {
      fprintf(stderr, "Erreur fatale, mémoire insuffisante");
      exit(1);
    }
  int i,j,k;
  double cout;
  L_ARC p;
  
  for(i=0; i<taille; ++i){
    C[i] = i;
    S[i] = -1;
    pcc[i] = DBL_MAX;
    pere[i] = -1;
  }
  
  d_int = chercherSommet(d, G);
  a_int = chercherSommet(a, G);
  pcc[d_int] = 0;  
  do{
    j = minimum(pcc, C, taille); 
    C[j] = -1;
    S[j] = j;
    p = G.sommets[j].voisins;
    while(!LArcEstVide(p)){
      k = p->val.arrivee;
      cout = p->val.cout;
      if (pcc[k] > pcc[j] + cout){
	pcc[k] = pcc[j] + cout;
	pere[k] = j;
      }
      p = p->suiv;
    }
  }while(!appartient(S, a_int) && pcc[j] != DBL_MAX);
  L_ARC resultat;
  resultat = calloc(1, sizeof(*resultat));  
  while(a_int != d_int){
    //printf("%d\n", pere[a_int]);
    arc.arrivee = pere[a_int];
    arc.cout = chercherCout(G.sommets[a_int].voisins,pere[a_int]); 
    resultat = ajoutArc(resultat, arc);
    a_int = pere[a_int];
  }
  free(pcc);
  free(pere);
  free(C);
  free(S);
  return resultat;
}
