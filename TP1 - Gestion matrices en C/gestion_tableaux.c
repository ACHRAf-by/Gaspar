#include <stdio.h>
#include <stdlib.h>
#include "gestion_tableaux.h"


/**********************************************************************/
/*** FAIRE LA CORRECTION alloc_2D() EN LIVE ***/
int** alloc_2D(int dim1, int dim2 )
{
	int** tab = NULL;
	int i=0;
	
	tab = (int**)malloc( dim1*sizeof(int*) );
	for(i=0;i<dim1;i++)
	{
		tab[i] = (int*)malloc(dim2*sizeof(int));
	}
	
	return tab;
}

/**********************************************************************/
/*** FAIRE LA CORRECTION  alloc_2D_v2()  EN LIVE ***/
void  alloc_2D_v2(int** * tab, int dim1, int dim2)
{
	int i=0;
	
	*tab = (int**)malloc( dim1*sizeof(int*) );
	for(i=0;i<dim1;i++)
	{
		(*tab)[i] = (int*)malloc(dim2*sizeof(int));
	}
	
	return;

}

/*
//NE FONCTIONNE PAS CAR ON TRAVAILLE AVEC UNE COPIE DU POINTEUR !!!!
void  alloc_2D_v2(int** tab, int dim1, int dim2)
{
	int i=0;
	
	tab = (int**)malloc( dim1*sizeof(int*) );
	for(i=0;i<dim1;i++)
	{
		tab[i] = (int*)malloc(dim2*sizeof(int));
	}
	
	return;

}*/

/**********************************************************************/
/*** FAIRE LA CORRECTION  desalloc_tab2D()  EN LIVE ***/
void desalloc_tab2D(int** * tab, int dim1)
{
	int i =0;
		
	for(i=0;i<dim1;i++)
	{
		free((*tab)[i]); 	//	*tab[i] => peut être différent suivant la priorité des opérateurs * et [ ]
	}					//	Si * est prioritaire => (*tab)[i] => 
						//  Si les [ ] sont prioritaires => *(tab[i])
						//	tab[i] <=> *(tab+i)
						//	*( (*tab)+i ) => (*tab)[i]
						//	/!\ *(tab[i]) => *(*(tab+i))
	free(*tab);
	*tab = NULL;
	
	return;
}

/**********************************************************************/
void saisir_tab2D(int** tab, int dim1, int dim2)
{
	int i=0,j=0;
	
	if(tab == NULL)
	{
		printf("tableau n'existe pas...\n");
		return;
	}
	
	printf(" ** Saisir les coeffs du tableau **\n");

	for(i=0;i<dim1;i++)
	{
		for(j=0;j<dim2;j++)
		{
			printf("saisie du coeff <%d,%d> : ",i,j);
			scanf(" %d",&tab[i][j]);
		}
	}
	return;
}

/**********************************************************************/
void afficher_tab2D(int** tab, int dim1, int dim2)
{
	int i=0,j=0;
	
	if(tab == NULL)
	{
		printf("tableau n'existe pas...\n");
		return;
	}
	
	for(i=0;i<dim1;i++)
	{
		for(j=0;j<dim2;j++)
		{
			printf("%3d ",tab[i][j]);
		}
		printf("\n");
	}

	return;
}
