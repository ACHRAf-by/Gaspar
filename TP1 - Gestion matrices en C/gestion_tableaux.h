#ifndef GESTION_TABLEAUX_H
#define GESTION_TABLEAUX_H

int** alloc_2D(int dim1, int dim2);
//void  alloc_2D_v2(int** tab, int dim1, int dim2); //NE FONCTIONNE PAS !
void  alloc_2D_v2(int*** tab, int dim1, int dim2);
void  saisir_tab2D(int** tab, int dim1, int dim2);
void  afficher_tab2D(int** tab, int dim1, int dim2);
void  desalloc_tab2D(int*** tab,int dim1);

#endif
