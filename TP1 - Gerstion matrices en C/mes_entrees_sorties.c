#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mes_entrees_sorties.h"

/**********************************************************************/
void ecrire_fichier(char* fichier, char* message)
{
	FILE* fichier_ecrit = NULL;

	fichier_ecrit = fopen(fichier, "w");

	if(fichier_ecrit != NULL && message!=NULL)
	{
		printf("ecriture dans le fichier <%s>...\n",fichier);
		fputs(message, fichier_ecrit);
	}
	else
	{
		fprintf(stderr,"Echec ecriture du message \"%s\" dans \"%s\".\n",message,fichier);
	}

	fclose(fichier_ecrit);

	return;
}

/**********************************************************************/
char* lire_fichier(char* fichier)
{
	FILE* fichier_lu = NULL;
	char* phrase = NULL;
	char tmp[TAILLE_TAMPON]="";

	fichier_lu = fopen(fichier,"r");

	if(fichier_lu == NULL)
	{
		fprintf(stderr,"Echec de l'ouverture du fichier a lire \"%s\".\n",fichier);
		phrase = NULL;
	}
	else
	{
		//phrase initiale vide
		phrase = (char*)malloc(1*sizeof(char));
		phrase[0]='\0';

		//Lecture ligne à ligne du contenu du fichier
		printf("Lecture du contenu du fichier <%s>...\n",fichier);
		while( fgets(tmp,TAILLE_TAMPON,fichier_lu) )
		{
			phrase = (char*)realloc(phrase,(strlen(phrase)+strlen(tmp)+1)*sizeof(char));
			strcpy(phrase+strlen(phrase),tmp);
		}
	}

	fclose(fichier_lu);

	return phrase;
}

/**********************************************************************/
void copier_fichier(char* dest, char* src)
{
	char* message = NULL;

	if( src==NULL || dest==NULL )
	{
		fprintf(stderr,"Echec copie, fichier invalide <src: %s> <dest: %s>...\n",src,dest);
	}
	else
	{
		message = lire_fichier(src);
		ecrire_fichier(dest,message);
	}

	return;
}
