#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h> //pour macro x_FILENO
#include <stdlib.h>
#include <time.h>
#include <stdio.h>

void aff_num_flux(void);

int main(int argc,char* argv[])
{
	FILE* f=NULL;
	
	aff_num_flux();
	
	if(argc != 2)
	{
		printf("Merci de preciser uniquement un nom de fichier...\n");
		return 0;
	}
	
	printf("Redirection de l'entrée standard dans le fichier : %s\n", argv[1]);
	
	//il faut ouvrir un flux pour le fichier puis récupérer son numéro à envoyer à dup2
	f = fopen(argv[1],"w");
	
	dup2(fileno(f),STDOUT_FILENO); //On peut mettre simplement 1 comme 2ème argument mais c'est moins clair ;-)
	
	printf("Cette affichage aura lieu dans le fichier et non dans le terminal !\n");
	
	return 0;
}

void aff_num_flux(void)
{
	printf("Numero flux entree : %d (%d)\n",fileno(stdin),STDIN_FILENO);
	printf("Numero flux sortie : %d (%d)\n",fileno(stdout),STDOUT_FILENO);
	printf("Numero flux error  : %d (%d)\n",fileno(stderr),STDERR_FILENO);
	
	return;
}
