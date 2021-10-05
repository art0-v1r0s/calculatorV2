#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include<time.h> //time

#define TAILLE_PILE 100

void historique(char * command,FILE * fichier){

    time_t t = time(NULL); /* t contient maintenant la date et l'heure courante */
    
    fprintf(fichier,"%s => %s\n",ctime(&t),command);
        

}

int impression(int *pile, int niveau)
{
    int index;
    for (index = 0; index < niveau; index++)
        printf("%d ", pile[index]);
    putchar('\n');
    return niveau;
}

int addition(int *pile, int niveau)
{
    pile[niveau - 2] = pile[niveau - 2] + pile[niveau - 1];
    return niveau - 1;
}

int soustraction(int *pile, int niveau)
{
    pile[niveau - 2] = pile[niveau - 2] - pile[niveau - 1];
    return niveau - 1;
}

int multiplication(int *pile, int niveau)
{
    pile[niveau - 2] = pile[niveau - 2] * pile[niveau - 1];
    return niveau - 1;
}

int division(int *pile, int niveau)
{
    pile[niveau - 2] = pile[niveau - 2] / pile[niveau - 1];
    return niveau - 1;
}

struct operation
{
    const char *nom;
    const int niveau_min;
    int (*fonction)(int *, int);
};

const struct operation ops[] = {
    {"+", 2, addition}, {"-", 2, soustraction}, {"x", 2, multiplication}, {"/", 2, division}, {"p", 1, impression}, {NULL, 0, NULL}};

void aide(void)
{
    int i;
    printf("Syntaxe:\n");
    for (i = 0; ops[i].nom != NULL; i++)
        printf("  %s%s%s\n",
               ops[i].niveau_min > 1 ? "n1 " : "",
               ops[i].niveau_min > 0 ? "n2 " : "",
               ops[i].nom);
}

int calcule(int *pile, int niveau, const char *chaine)
{
    int nombre;
    if (sscanf(chaine, "%d", &nombre) == 1)
    {
        if (niveau < TAILLE_PILE)
        {
            pile[niveau] = nombre;
            return niveau + 1;
        }
        else
            printf("Pas assez de place dans la pile\n");
        return -1;
    }
    else
    {
        int i;
        for (i = 0; ops[i].nom != NULL; i++)
            if (strcmp(chaine, ops[i].nom) == 0)
            {
                if (niveau >= ops[i].niveau_min)
                    return (*ops[i].fonction)(pile, niveau);
                else
                {
                    printf("%s a besoin de %d arguments\n", ops[i].nom,
                           ops[i].niveau_min);
                    return -1;
                }
            }
        printf("Operation inconnue: %s\n", chaine);
        aide();
        return -1;
    }
}

int main(int argc, char **argv)
{
    if (argc == 1)
    {
        aide();
        return EXIT_FAILURE;
    }
    else
    {
        FILE * fichier = NULL;
    
        fichier = fopen("historique.txt","a");

        //pour function historique
        char calcul[TAILLE_PILE] = "";
        for (int i=1; i < argc; i++)
        {
        //printf("Argument %d : %s \n", i+1, argv[i]);
        strcat(calcul,argv[i]);
        }
        puts(calcul);

        historique(calcul,fichier);
        fclose(fichier);

        int pile[TAILLE_PILE];
        int niveau = 0;
        argc--;
        argv++;
        while (argc > 0 && niveau != -1)
        {
            niveau = calcule(pile, niveau, *argv);
            argv++;
            argc--;
        }
        if (niveau != -1)
            impression(pile, niveau);
        return EXIT_SUCCESS;
    }
}