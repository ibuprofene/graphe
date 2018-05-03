#include "graphe.h"
#include "algo.h" 

GRAPHE ouvrirGraphe(char *nom){
  FILE *fichier_graphe = fopen(nom, "r");
  if (fichier_graphe == NULL){
    fprintf(stderr, "Ouverture du fichier impossible");
  } //compiler avec clang + MakeFile ! + plusieurs fichiers algo.c graphe.c main.c ++ run valgrind pour voir les memory leaks
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
  fgets(mot,511,fichier_graphe);
  
  GRAPHE G;
  G.n = nb_sommets;
  G.sommets = calloc(nb_sommets, sizeof(T_SOMMET));
  
  for(i=0; i<nb_sommets; ++i){
    fgets(mot,511,fichier_graphe);
    fscanf(fichier_graphe, "%d %lf %lf %s %s", &numero, &latitude, &longitude, mot, nom_sommet);
    G.sommets[i].x = latitude;
    G.sommets[i].y = longitude;
    G.sommets[i].nom = calloc(1, strlen(nom_sommet)*sizeof(char) + 1);
    if (nom_sommet[strlen(nom_sommet)-1]<32) nom_sommet[strlen(nom_sommet)-1]=0;
    strcpy(G.sommets[i].nom, nom_sommet);
    //Note il faut aussi ajouter la lecture des stations de métro
    //ajouterSommet ...
  }
  fgets(mot,511,fichier_graphe);
  for(i=0; i<nb_arcs; ++i){
    fgets(mot,511,fichier_graphe);
    fscanf(fichier_graphe, "%d %d %lf", &sommet_depart, &sommet_arrivee, &valeur);
    T_ARC T;
    T.cout = valeur;
    T.arrivee = sommet_arrivee;
    G.sommets[sommet_depart].voisins = ajoutArc(G.sommets[sommet_depart].voisins, T);
    
    /* /!\ CODE A FACTORISER ! /!\ */    
  }
  fclose(fichier_graphe);
  return G;
}

void afficherGraphe(GRAPHE G){
  int taille = G.n;
  int i;
  L_ARC p;
  //printf("%d",taille);
  for(i = 0; i < taille; i++){
    printf("Sommet: %s\n", G.sommets[i].nom);
    p = G.sommets[i].voisins;
    //printf("%d\n", LArcEstVide(p));
    while(!LArcEstVide(p)){
      printf("A pour voisin %d avec un cout de %lf\n", p->val.arrivee, p->val.cout);
      p = p->suiv;
    }
  }
}

L_ARC supprimerTete(L_ARC l){
  if (LArcEstVide(l)){return NULL;}
  else {
    L_ARC p;
    p=l->suiv;
    free(l);
    return p;
  }
}

void libererGraphe(GRAPHE G){
  int i;
  L_ARC p;
  for(i=0; i<G.n; ++i){
    printf("%d\n",i);
    free(G.sommets[i].nom);
    for(p=G.sommets[i].voisins;!LArcEstVide(p);p=p->suiv){
      supprimerTete(p);
    }
  }
  free(G.sommets);
}
  
