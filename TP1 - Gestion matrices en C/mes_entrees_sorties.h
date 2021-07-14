#ifndef MES_ENTREES_SORTIES_H
#define MES_ENTREES_SORTIES_H

#define TAILLE_TAMPON 1024

//nom par défaut du fichier de sortie
#define FICHIER_SORTIE "out.txt"

/* Ecriture du message dans le fichier*/
void ecrire_fichier(char* fichier, char* message);

/* Renvoie le contenu du fichier
 * retourne NULL si la lecture a raté
 * */
char* lire_fichier(char* fichier);

/* copie le contenu du fichier nommé src dans le fichier nommé dest*/
void copier_fichier(char* dest, char* src);

#endif
