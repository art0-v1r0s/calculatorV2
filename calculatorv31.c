#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include<time.h> //time

#define TAILLE_PILE 100

void historique(char * command,FILE * fichier){

    time_t t = time(NULL); /* t contient maintenant la date et l'heure courante */
    
    fprintf(fichier,"%s => %s\n",ctime(&t),command);
        

}

unsigned long long factorielle(unsigned long long a)
{
    unsigned long long r = 1;

    for (unsigned long long i = 2; i <= a; ++i)
        r *= i;

    return r;
}

long long pgcd(long long a, long long b)
{
    if (b == 0)
        return a;

    long long r = a % b;

    while (r != 0)
    {
            a = b;
            b = r;
            r = a % b;
    }

    return b;
}

int divisionEucli(int a, int b)
{
	int q = 0;
	int r = a;
	while (r >= b)
	{
		q = q + 1;
		r = r - b;
	}
	printf("ur quotient is %d & the rest is %d\n", q, r);
	return 0;
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
    if (argc <= 4)
    {
        double result;
        printf("%c",argv[2][0]);
        
        switch (argv[2][0])
        {

            case '!' :
                result = factorielle(atoi(argv[1]));
                printf("votre resultat :  %.2lf\n",result);
                break;

            case '%' :
                result = divisionEucli(atoi(argv[1]),atoi(argv[3]));
                break;

            case 'g' :
                result = pgcd(atof(argv[1]),atof(argv[3]));
                printf("votre resultat :  %.2lf\n",result);
                break;    
            
            case 'v' :
                result = sqrt(atof(argv[1]));
                printf("ur result :  %.2lf\n",result);
                break;

            case '^' :
                result = pow(atof(argv[1]),atof(argv[3]));
                printf("ur result :  %.2lf\n",result);
                break;

            case 'e' :
                result = exp(atof(argv[1]));
                printf("votre resultat :  %.2lf\n",result);
                break;

            case 'l' :
                result = log(atof(argv[1]));
                printf("votre resultat :  %.2lf\n",result);
                break;

            default :
                printf("Error! Operator is not correct\n");	
        }
            
    }
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
        //puts(calcul);

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