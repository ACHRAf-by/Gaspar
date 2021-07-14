/*
 * VERSION ACTUELLE
 * 
 * Compilation : gcc -Wall gestion_matrice.c gestion_tableauxmes_entrees_sorties.c test_mes_entrees_sorties.c
 * 			ou : gcc -Wall *.c
 * Lancement : 
 * 				./a.out matrice1.txt ==> copie le contenu de <matrice.txt> dans <out.txt> (nom par défaut)
 * 				./a.out -o sortie.txt matrice1.txt ==> copie le contenu de <matrice.txt> dans <sortie.txt>
 * 				./a.out matrice1.txt -o sortie.txt ==> copie le contenu de <matrice.txt> dans <sortie.txt>
 *
 * CE QUI MANQUE DANS CETTE CORRECTION
 *  - prise en compte de plusieurs fichiers d'entrée (matrice1 et matrice2) pour faire la multiplication matricielle
 *	
 *  */

#include "mes_entrees_sorties.h"
#include "gestion_matrice.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>


/* copie les noms des fichiers d'entrées et de sortie donnés lors du lancement 
 * Si le format ne convient pas => flag -help pour l'utilisateur */
void options_lancemenent(char** dest,char** src, int nbarg, char** argv);
void desalloc_fichiers(char* dest, char* src);

int main(int nbarg, char* argv[])
{
	char* dest=NULL, *src=NULL;
	t_matrice* mat = NULL;
	
	//récupérer les noms des fichiers à utiliser, donner au lancement
	options_lancemenent(&dest, &src, nbarg, argv);
	
	printf("Copie de <%s> dans <%s>\n",src,dest);
	copier_fichier(dest, src);	
	
	mat = ato_matrice(lire_fichier(src));//ASCII TO MATRICE, comme atof/atoi
	printf("Matrice contenu dans <%s>:\n",src);
	aff_matrice(mat);
	desalloc_matrice(&mat);
	
	//libérer les noms de fichiers dynamiques
	desalloc_fichiers(dest, src);
	
	return 0;
}


void options_lancemenent(char** dest,char** src, int nbarg, char** argv)
{	
	/*
	 * Possible de faire une gestion plus propre et indépendante de l'ordre.
	 * avec getopt() par exemple
	 */
	
	switch(nbarg)
	{
		case 2:		if( strcmp(argv[1],"--help") == 0 )
					{
						//Reprendre le format de "gcc --help"
						printf("Utilisation: %s [option] fichier \n",argv[0]);
						printf("Options:\n");
						printf("  --help    Afficher ces informations\n");
						printf("  -o <s>    Ecrire dans le fichier de sortie <s>, par defaut <out.txt>\n");
						exit(0);
					}
					else
					{
						*dest = (char*)malloc((strlen(FICHIER_SORTIE)+1)*sizeof(char));
						strcpy(*dest,FICHIER_SORTIE);
						*src = (char*)malloc((strlen(argv[1])+1)*sizeof(char));
						strcpy(*src,argv[1]);
						
					}
				break;
	
		case 4:		
					if( strcmp(argv[1],"-o") == 0 )
					{
						*dest = (char*)malloc((strlen(argv[2])+1)*sizeof(char));
						strcpy(*dest,argv[2]);
						*src = (char*)malloc((strlen(argv[3])+1)*sizeof(char));
						strcpy(*src,argv[3]);
					}
					else if( strcmp(argv[2],"-o") == 0 )
					{
						*dest = (char*)malloc((strlen(argv[2])+1)*sizeof(char));
						strcpy(*dest,argv[3]);
						*src = (char*)malloc((strlen(argv[3])+1)*sizeof(char));
						strcpy(*src,argv[1]);
					}
					else
					{
						printf("Utiliser le flag \"--help\" pour consulter l'aide\n");
						exit(0);
					}
					
				break;
			
		default:	printf("Utiliser le flag \"--help\" pour consulter l'aide\n");
					exit(0);
	}

	return;
}

void desalloc_fichiers(char* dest, char* src)
{
	free(dest);
	free(src);
	
	return;
}
