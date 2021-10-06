#include <stdio.h>
#include <stdlib.h>
#include <string.h>//for strcmp
#include <math.h>//for pow sqrt log exp

#include<time.h> //time

#define SIZE_STACK 100

//function historique who write the calcul and the date in a file  
void historique(char * command,FILE * file){

    time_t t = time(NULL); /* t contient maintenant la date et l'heure courante */
    
    fprintf(file,"%s => %s\n",ctime(&t),command);//write in the file
        

}
//function factorielle 
unsigned long long factorielle(unsigned long long a)
{
    unsigned long long r = 1;

    for (unsigned long long i = 2; i <= a; ++i)
        r *= i;

    return r;
}
//function PGCD 
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
//euclidienne division who print the "quotien" and the "reste"
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
//function print
int impression(int *stack, int level)
{
    int index;
    for (index = 0; index < level; index++)
        printf("%d ", stack[index]);
    putchar('\n');
    return level;
}
//function addition 
int addition(int *stack, int level)
{
    stack[level - 2] = stack[level - 2] + stack[level - 1];
    return level - 1;
}

int soustraction(int *stack, int level)
{
    stack[level - 2] = stack[level - 2] - stack[level - 1];
    return level - 1;
}

int multiplication(int *stack, int level)
{
    stack[level - 2] = stack[level - 2] * stack[level - 1];
    return level - 1;
}

int division(int *stack, int level)
{
    stack[level - 2] = stack[level - 2] / stack[level - 1];
    return level - 1;
}

struct operation
{
    const char *nom;
    const int level_min;
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
               ops[i].level_min > 1 ? "n1 " : "",
               ops[i].level_min > 0 ? "n2 " : "",
               ops[i].nom);
}

int calcule(int *stack, int level, const char *string)
{
    int number;
    if (sscanf(string, "%d", &number) == 1)
    {
        if (level < SIZE_STACK)
        {
            stack[level] = number;
            return level + 1;
        }
        else
            printf("no space in the stack \n");
        return -1;
    }
    else
    {
        int i;
        for (i = 0; ops[i].nom != NULL; i++)
            if (strcmp(string, ops[i].nom) == 0)
            {
                if (level >= ops[i].level_min)
                    return (*ops[i].fonction)(stack, level);
                else
                {
                    printf("%s need %d arguments\n", ops[i].nom,
                           ops[i].level_min);
                    return -1;
                }
            }
        //printf("Operation inconnue: %s\n", string);
        //aide();
        return -1;
    }
}

int main(int argc, char **argv)
{
    if (argc <= 3)
    {
        double result;
        printf("%c",argv[2][0]);
        
        switch (argv[2][0])
        {

            case '!' :
                result = factorielle(atoi(argv[1]));
                printf("your result :  %.2lf\n",result);
                break;

            case '%' :
                result = divisionEucli(atoi(argv[1]),atoi(argv[3]));
                break;

            case 'g' :
                result = pgcd(atof(argv[1]),atof(argv[3]));
                printf("your result :  %.2lf\n",result);
                break;    
            
            case 'v' :
                result = sqrt(atof(argv[1]));
                printf("your result :  %.2lf\n",result);
                break;

            case '^' :
                result = pow(atof(argv[1]),atof(argv[3]));
                printf("your result :  %.2lf\n",result);
                break;

            case 'e' :
                result = exp(atof(argv[1]));
                printf("your result :  %.2lf\n",result);
                break;

            case 'l' :
                result = log(atof(argv[1]));
                printf("your result :  %.2lf\n",result);
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
        
        FILE * file = NULL;
    
        file = fopen("historique.txt","a");

        //pour function historique
        char calcul[SIZE_STACK] = "";
        for (int i=1; i < argc; i++)
        {
        //printf("Argument %d : %s \n", i+1, argv[i]);
        strcat(calcul,argv[i]);
        }
        //puts(calcul);

        historique(calcul,file);
        fclose(file);

        int stack[SIZE_STACK];
        int level = 0;
        argc--;
        argv++;
        while (argc > 0 && level != -1)
        {
            level = calcule(stack, level, *argv);
            argv++;
            argc--;
        }
        if (level != -1)
            impression(stack, level);
        return EXIT_SUCCESS;
    }
}