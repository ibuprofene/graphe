#include "graphe.h"
#include "algo.h" 

GRAPHE ajouterCorrespondancesUneStation(GRAPHE G){
  /*si deux lignes se croisent à une même station,
    alors il faut ajouter un arc joignant les deux sommets
    de coût 360*/
  int nb_sommets;
  nb_sommets = G.n;
  int i, j;
  T_ARC T;
  for(i=0; i<nb_sommets; i++){
    for(j=0; j<nb_sommets && i!=j ; j++){
      if (!strcmp(G.sommets[i].nom, G.sommets[j].nom)){ // si chaînes identiques
	T.arrivee = chercherSommet(G.sommets[j], G);
	T.cout = 360;
	G.sommets[i].voisins =  ajoutArc(G.sommets[i].voisins, T); //penser à mettre double dans graphe.h
      }
    }
  }
  return G;
}

GRAPHE ajouterChoixDepart(GRAPHE G, char* nom){
  /*si plusieurs lignes passent par la station de départ
    alors on relie les sommets correspondant à cette station
    pour chaque ligne par un arc de poids nul*/
  int nb_sommets;
  nb_sommets = G.n;
  T_ARC T;
  //precedent = calloc(1, sizeof(precedent));
  //actuel = calloc(1, sizeof(actuel));
  int i,j;
  for(i=0; i<nb_sommets; i++){
    for(j=0; j<nb_sommets && i!=j ; j++){
      if (!strcmp(G.sommets[i].nom, nom) && !strcmp(G.sommets[j].nom, nom)){ //si on trouve un arrêt de ce nom
	T.arrivee = chercherSommet(G.sommets[i], G);
	T.cout = 0;
	G.sommets[j].voisins = ajoutArc(G.sommets[j].voisins, T);
      }
    }
  }
  return G;
}

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
    //fgets(mot,511,fichier_graphe);
    fscanf(fichier_graphe, "%d %lf %lf %s", &numero, &latitude, &longitude, mot);
    fgets(nom_sommet, 511, fichier_graphe);
    G.sommets[i].x = latitude;
    G.sommets[i].y = longitude;
    G.sommets[i].nom = calloc(1, strlen(nom_sommet)*sizeof(char) + 1);
    G.sommets[i].nom_station = calloc(1, strlen(mot)*sizeof(char) + 1);
    if (nom_sommet[strlen(nom_sommet)-1]<32)nom_sommet[strlen(nom_sommet)-1]=0;
    while(nom_sommet[0]==' '){
      for(int k = 0; k<strlen(nom_sommet)-1;++k){
	nom_sommet[k] = nom_sommet[k+1];
      }
    nom_sommet[strlen(nom_sommet)-1]='\0';
    }
    strcpy(G.sommets[i].nom, nom_sommet);
    strcpy(G.sommets[i].nom_station, mot);
    //printf("%s\n", G.sommets[i].nom);
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
  for(i = 0; i < taille; i++){
    printf("Sommet: %s de station: %s\n", G.sommets[i].nom, G.sommets[i].nom_station);
    p = G.sommets[i].voisins;
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
    //printf("%d\n",i);
    free(G.sommets[i].nom);
    for(p=G.sommets[i].voisins;!LArcEstVide(p);p=p->suiv){
      supprimerTete(p);
    }
  }
  free(G.sommets);
}
  
