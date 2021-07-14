#ifndef MATRICE_H
#define MATRICE_H

//PARTIE 2
typedef struct
{
	int** coeffs;
	unsigned int nb_lig;
	unsigned int nb_col;
}t_matrice;

t_matrice* 	alloc_matrice_1(int lig, int col);
void 		alloc_matrice_2(t_matrice** mat, int lig, int col);
void        aff_matrice(t_matrice* mat);
void        saisir_matrice(t_matrice* mat);
t_matrice*  mult_matrice(t_matrice* m1, t_matrice* m2);
void        desalloc_matrice(t_matrice** mat);

//PARTIE 3
t_matrice*  ato_matrice(char* str);//ASCII TO MATRICE, comme atof/atoi

#endif
