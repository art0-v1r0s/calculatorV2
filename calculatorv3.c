#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include<time.h>

#define TAB_SIZE 100

// ----- HISTORIC FUNCTION WHICH WRITE THE CALCUL AND THE DATE/TIME IN A FILE -----
void historic(char * command,FILE * file){
    time_t date = time(NULL);
    fprintf(file, "%s => %s\n", ctime(&date), command);
}


// ----- EVERY FUNCTIONS USED IN THE CALCULATOR -----
// Factorial function
unsigned long long factorial(unsigned long long a){
    unsigned long long tmp = 1;

    for (unsigned long long i = 2; i <= a; ++i)
        tmp *= i;

    return tmp;
}


// Euclidean division function
int euclideanDiv(int a, int b){
	int q = 0;
	int tmp = a;

	while (tmp >= b){
		q = q + 1;
		tmp = tmp - b;
	}

	printf("Your quotient is %d & the rest is %d\n", q, tmp);
	return 0;
}


// Print function
double print(double *opTab, int level){
    int index;
    for (index = 0; index < level; index++)
        printf("%.2lf ", opTab[index]);
    putchar('\n');
    return level;
}


// Addition function
double addition(double *opTab, int level){
    opTab[level - 2] = opTab[level - 2] + opTab[level - 1];
    return level - 1;
}


// Substraction function
double substraction(double *opTab, int level){
    opTab[level - 2] = opTab[level - 2] - opTab[level - 1];
    return level - 1;
}


// Multiplication function
double multiplication(double *opTab, int level){
    opTab[level - 2] = opTab[level - 2] * opTab[level - 1];
    return level - 1;
}


// Division function
double division(double *opTab, int level){
    opTab[level - 2] = opTab[level - 2] / opTab[level - 1];
    return level - 1;
}


// Structure of the operations
struct operation{
    const char *nom;
    const int level_min;
    double (*fonction)(double *, int);
};


// Array that contains our operations
const struct operation operations[] = {
    {"+", 2, addition},
    {"-", 2, substraction},
    {"*", 2, multiplication},
    {"x", 2, multiplication},
    {"/", 2, division},
    {"p", 1, print},
    {NULL, 0, NULL}
};


// Helper menu
void helper(void){
    int i;
    printf("Syntax: \n");

    for (i = 0; operations[i].nom != NULL; i++)
        printf("%s%s%s \n",
               operations[i].level_min > 1 ? "n1 " : "",
               operations[i].level_min > 0 ? "n2 " : "",
               operations[i].nom
             );
}


double calculate(double *opTab, int level, const char *string){
    int number;

    if (sscanf(string, "%d", &number) == 1){
        if (level < TAB_SIZE){
            opTab[level] = number;
            return level + 1;
        }
        else
            printf("No space in the operation tab \n");
        return -1;
    }
    else{
        int i;
        for (i = 0; operations[i].nom != NULL; i++)
            if (strcmp(string, operations[i].nom) == 0){
                if (level >= operations[i].level_min)
                    return (*operations[i].fonction)(opTab, level);
                else{
                    printf("%s need %d arguments\n", operations[i].nom, operations[i].level_min);
                    return -1;
                }
                }
        return -1;
    }
}


// ----- SINGLE OPERATION FUNCTIONS -----
int main(int argc, char **argv){
    if (argc == 3){
        double result;

        switch (argv[2][0]){
            case '!' :
                result = factorial(atoi(argv[1]));
                printf("%.2lf\n", result);
                break;

            case '%' :
                result = euclideanDiv(atoi(argv[1]), atoi(argv[3]));
                break;

            case 'v' :
                result = sqrt(atof(argv[1]));
                printf("%.2lf\n", result);
                break;

            case '^' :
                result = pow(atof(argv[1]), atof(argv[3]));
                printf("%.2lf\n", result);
                break;

            case 'e' :
                result = exp(atof(argv[1]));
                printf("%.2lf\n", result);
                break;

            case 'l' :
                result = log(atof(argv[1]));
                printf("%.2lf\n", result);
                break;

            default :
                printf("Error! Operator is not correct\n");
        }
    }
    else if (argc == 1 || argc == 2){
        helper();
        return EXIT_FAILURE;
    }
    else{
        FILE * file = NULL;
        file = fopen("historic.txt","a");

        char calcul[TAB_SIZE] = "";
        for (int i=1; i < argc; i++){
          strcat(calcul,argv[i]);
        }

        historic(calcul,file);
        fclose(file);

        double opTab[TAB_SIZE];
        int level = 0;
        argc --;
        argv ++;

        while (argc > 0 && level != -1){
            level = calculate(opTab, level, *argv);
            argv ++;
            argc --;
        }
        if (level != -1)
            print(opTab, level);
        return EXIT_SUCCESS;
    }
}
