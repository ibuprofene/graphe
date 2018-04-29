#include "graphe.h"
#include "algo.h" 
/*
GRAPHE ajouterSommet(GRAPHE G, T_SOMMET sommet){
  //G->n = G->n + 1;  
}
GRAPHE supprimerSommet(GRAPHE G, T_SOMMET sommet){
}
GRAPHE ajouterArc(GRAPHE G, T_SOMMET A, T_SOMMET B, int valeur){
}
GRAPHE supprimerArc(GRAPHE G, T_SOMMET A, T_SOMMET B){
}
int valeurArc(GRAPHE G, T_SOMMET A, T_SOMMET B){
}
int voisin(GRAPHE G, T_SOMMET A, T_SOMMET B){
}
T_SOMMET* voisinS(GRAPHE G, T_SOMMET A){
}

T_SOMMET* plusCourtChemin(GRAPHE G, T_SOMMET A, T_SOMMET B){
}
*/

GRAPHE ouvrirGraphe(char *nom){
  FILE *fichier_graphe = fopen(nom, "r");
  if (fichier_graphe == NULL){
    fprintf(stderr, "Ouverture du fichier impossible");
  } //compiler avec clang + MakeFile ! + plusieurs fichiers algo.c graphe.c main.c
  int nb_sommets;
  int nb_arcs;
  int i;
  double latitude;
  double longitude;
  char nom_sommet[128];
  int numero;
  int sommet_depart;
  int sommet_arrivee;
  double valeur;
  char mot[128];
  fscanf(fichier_graphe, "%d %d", &nb_sommets, &nb_arcs);
  printf("%d %d\n", nb_sommets, nb_arcs);
  fgets(mot,511,fichier_graphe);
  GRAPHE G;
  //G = calloc(1,sizeof(G));
  G.n = nb_sommets;
  G.sommets = calloc(nb_sommets, sizeof(T_SOMMET));
  for(i=0; i<nb_sommets; ++i){
    fgets(mot,511,fichier_graphe);
    fscanf(fichier_graphe, "%d %lf %lf %s %s", &numero, &latitude, &longitude, mot, nom_sommet);
    printf("%s\n", nom_sommet);
    G.sommets[i].x = latitude;
    G.sommets[i].y = longitude;
    G.sommets[i].nom = malloc(strlen(nom_sommet)*sizeof(char));
    if (nom_sommet[strlen(nom_sommet)-1]<32) nom_sommet[strlen(nom_sommet)-1]=0;
    strcpy(G.sommets[i].nom, nom_sommet);//Attention au sens ! :p
    
    //Note il faut aussi ajouter la lecture des stations de métro
    //ajouterSommet ...
  }
  fgets(mot,511,fichier_graphe);
  for(i=0; i<nb_arcs; ++i){
    fscanf(fichier_graphe, "%d %d %lf", &sommet_depart, &sommet_arrivee, &valeur);
    /*L_ARC nouveau;
    nouveau = calloc(1,sizeof(*nouveau));
    
    nouveau->val.cout = valeur;
    nouveau->val.arrivee = sommet_arrivee;
    nouveau->suiv = G.sommets[sommet_depart].voisins;*/
    T_ARC T;
    T.cout = valeur;
    T.arrivee = sommet_arrivee;
    G.sommets[sommet_depart].voisins = ajoutLArc(G.sommets[sommet_depart].voisins, T);
    
    /* /!\ CODE A FACTORISER ! /!\ */    
  }
  return G;
}

void afficherGraphe(GRAPHE G){
  int taille = G.n;
  int i;
  L_ARC *p;
  printf("%d",taille);
  for(i = 0; i < taille; i++){
    printf("%s\n", G.sommets[i].nom);
    p = G.sommets[i].voisins;
    while(!LArcEstVide(p)){
	p = p->suiv;
    }
  }
}

