// ----- LASTE EDIT THE 07-10-2021 BY ARTHUR D AND KEVIN D -----

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include<time.h>

#define TAB_SIZE 100

// ----- HISTORIC FUNCTION WHICH WRITE THE CALCUL AND THE DATE/TIME IN A FILE -----
void historic(char * command,FILE * file){
    time_t date = time(NULL);
    fprintf(file, "%s => %s\n", ctime(&date), command); // ctime convert the timestamp of the var date into a string
}


// ----- EVERY FUNCTIONS USED IN THE CALCULATOR -----
// Factorial function
unsigned long long factorial(unsigned long long a){
    unsigned long long tmp = 1;
    unsigned long long i = 0;
    for (i = 2; i <= a; ++i)
        tmp *= i;

    return tmp;
}


// Euclidean division function
int euclideanDiv(int a, int b){
	int q = 0;
	int r = a;

	while (r >= b){
		q = q + 1;
		r = r - b;
	}

	printf("Your quotient is %d & the rest is %d\n", q, r);
	return 0;
}


// Print function
double print(double *opTab, int level){
    int index = 0;

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
double multiplicationStar(double *opTab, int level){
    opTab[level - 2] = opTab[level - 2] * opTab[level - 1];
    return level - 1;
}

// Multiplication function
double multiplicationV(double *opTab, int level){
    opTab[level - 2] = opTab[level - 2] * opTab[level - 1];
    return level - 1;
}


// Division function
double division(double *opTab, int level){
    if(opTab[level -1] == 0){
      printf("Impossible to divide by zero !!!");
      return EXIT_FAILURE;
    }else{
      opTab[level - 2] = opTab[level - 2] / opTab[level - 1];
      return level - 1;
    }
}


// Power function
double power(double *opTab, int level){
    opTab[level - 2] = pow(opTab[level - 2], opTab[level - 1]);
    return level - 1;
}


// Euclidean function
double euclidean(double *opTab, int level){
    opTab[level - 2] = euclideanDiv((int)opTab[level - 2], (int)opTab[level - 1]);
    return level - 1;
}


// Structure of the operations
struct operation{
    const char *name;
    const int level_min;
    double (*function)(double *, int);
};


// Array that contains our operations
const struct operation operations[] = {
    {"+", 2, addition},
    {"-", 2, substraction},
    {"*", 2, multiplicationStar},
    {"x", 2, multiplicationV},
    {"/", 2, division},
    {"%", 2, euclidean},
    {"^", 2, power},
    {"p", 1, print},
    {NULL, 0, NULL} // Used for ending the helper menu
};


// Helper menu
void helper(void){
    int i = 0;
    printf("Syntax: \n");

    for (i = 0; operations[i].name != NULL; i++)
        printf("%s%s%s \n",
               operations[i].level_min > 1 ? "n1 " : "",
               operations[i].level_min > 0 ? "n2 " : "",
               operations[i].name
             );
}


double calculate(double *opTab, int level, const char *string){
    double number = 0;

    if (sscanf(string, "%lf", &number) == 1){
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
        for (i = 0; operations[i].name != NULL; i++)
            if (strcmp(string, operations[i].name) == 0){
                if (level >= operations[i].level_min)
                    return (*operations[i].function)(opTab, level);
                else{
                    printf("%s need %d arguments\n", operations[i].name, operations[i].level_min);
                    return -1;
                }
                }
        return -1;
    }
}


// ----- SINGLE OPERATION FUNCTIONS -----
int main(int argc, char **argv){
    if (argc == 3){
        double result = 0;

        switch (argv[2][0]){
            case '!' :
                result = factorial(atoi(argv[1]));
                printf("%.0lf\n", result);
                break;

            case 'v' :
                result = sqrt(atof(argv[1]));
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
          strcat(calcul, argv[i]);
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
