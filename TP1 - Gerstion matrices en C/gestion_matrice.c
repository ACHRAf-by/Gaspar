#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "gestion_matrice.h"
#include "gestion_tableaux.h"

/**********************************************************************/
t_matrice* alloc_matrice_1(int lig, int col)
{
	t_matrice* mat = NULL;
	int i = 0,j=0;
	
	mat = (t_matrice*)malloc(sizeof(t_matrice));
	
	if(mat == NULL )
	{
		fprintf(stderr,"Echec alloc_matrice_1() pas assez de memoire\n");
		return NULL;
	}
	
	mat->nb_lig = lig;
	mat->nb_col = col;
	
	//allocation dynamique des coeffs
	mat->coeffs = (int**)malloc(mat->nb_lig*sizeof(int*));
	for(i=0; i<mat->nb_lig ; i++)
	{
		mat->coeffs[i] = (int*)malloc(mat->nb_col*sizeof(int));
		for(j=0; j<mat->nb_col ; j++)
		{
			mat->coeffs[i][j] = -1;
		}
	}

	return mat;
}

/* AUTRE VERSION POSSIBLE A CONNAITRE */
void alloc_matrice_2(t_matrice** mat, int lig, int col)
{
	int i = 0,j=0;

	*mat = (t_matrice*)malloc(sizeof(t_matrice));
	
	if(*mat == NULL )
	{
		fprintf(stderr,"Echec alloc_matrice_2() pas assez de memoire\n");
		return;
	}
	
	(*mat)->nb_lig = lig;
	(*mat)->nb_col = col;

	//allocation dynamique des coeffs
	(*mat)->coeffs = (int**)malloc((*mat)->nb_lig*sizeof(int*));
	for(i=0; i<(*mat)->nb_lig ; i++)
	{
		(*mat)->coeffs[i] = (int*)malloc((*mat)->nb_col*sizeof(int));
		for(j=0; j<(*mat)->nb_col ; j++)
		{
			(*mat)->coeffs[i][j] = -1;
		}
	}

	return;
}

/**********************************************************************/
void aff_matrice(t_matrice* mat)
{
	if(mat == NULL )
	{
		fprintf(stderr,"Echec aff_matrice() impossible\n");
		return;
	}
	
	afficher_tab2D(mat->coeffs,mat->nb_lig, mat->nb_col);

	return;
}

/**********************************************************************/
void saisir_matrice(t_matrice* mat)
{
	if(mat == NULL )
	{
		fprintf(stderr,"Echec saisir_matrice() impossible\n");
		return;
	}
	
	saisir_tab2D(mat->coeffs,mat->nb_lig, mat->nb_col);

	return;
}

/**********************************************************************/
t_matrice*  mult_matrice(t_matrice* m1, t_matrice* m2)
{
	t_matrice* m = NULL;
	int i,j,k;
	
	if(m1 == NULL || m2 == NULL || m1->nb_col != m2->nb_lig )
	{
		fprintf(stderr,"Echec multiplication impossible\n");
		return NULL;
	}
	
	m = alloc_matrice_1(m1->nb_lig,m2->nb_col);

	for(i=0;i < m->nb_lig;i++)
	{
		for(j=0;j < m->nb_col;j++)
		{
			m->coeffs[i][j] = 0;
			for(k=0; k < m1->nb_col ;k++)
			{
				m->coeffs[i][j] += m1->coeffs[i][k] * m2->coeffs[k][j];
			}
		}
	}
	
	return m;
}

/**********************************************************************/
void desalloc_matrice(t_matrice** mat)
{
	int i=0;

	if(*mat == NULL )
	{
		fprintf(stderr,"Rien à desalloc_matrice() \n");
		return;
	}

	for(i=0; i<(*mat)->nb_lig ; i++)
	{
		free((*mat)->coeffs[i]);
	}
	free((*mat)->coeffs);
	free(*mat);
	
	//important de remettre à NULL pour indiquer qu'il n'est plus valide
	*mat = NULL;
	
	return;
}

/**********************************************************************/
t_matrice* ato_matrice(char* str) //ASCII TO MATRICE, comme atof/atoi
{
	t_matrice* mat=NULL;
	char* pos_courante=str; //position courante dans la chaine str, équivalent du SEEK_CUR pour les flux
	char tmp[20] = {0};
	int i=0,j=0;
	int lig=0,col=0;

	if(str == NULL )
	{
		fprintf(stderr,"Echec chaine d'entree vide\n");
		return NULL;
	}
	
	/* pas de tete de lecture pour le sscanf comme pour les lectures dans les flux
	 * donc on ne se déplace pas automatiquement comme dans un flux après une lecture
	 * il faut le faire soi-même => incrémentation de <pos_courante>...
	 *
	 * On aurait pu le faire plus facilement en fusionnant cette fonction avec la fonction de lecture
	 * L'idée ici est d'imposer aux étudiants de ne pas toucher à la fonction de lecture précédemment
	 * écrite afin qu'ils puissent trouver une solution utilisant les fonctions sscanf, atof et atoi
	 * qu'ils n'ont sans doute jamais utilisé pour certains
	 */

	//Récupération du nombre de ligne
	sscanf(pos_courante,"%s", tmp);
	lig=atoi(tmp);
	pos_courante += strlen(tmp)+1;

	//Récupération du nombre de colonne
	sscanf(pos_courante,"%s", tmp);
	col=atoi(tmp);
	pos_courante += strlen(tmp)+1;

	//Creation d'une matrice vide
	//mat = alloc_matrice_1(lig,col);
	alloc_matrice_2(&mat,lig,col);

	//Récupération des coefficients de la matrice
	for(i=0; i<mat->nb_lig ; i++)
	{
		for(j=0; j<mat->nb_col ; j++)
		{
			//on lit la chaine de caractère mot par mot
			sscanf(pos_courante,"%s", tmp);
			pos_courante += strlen(tmp)+1;
			mat->coeffs[i][j] = atof(tmp);
		}
	}

	return mat;
}
