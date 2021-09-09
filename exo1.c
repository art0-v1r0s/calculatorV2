#include <stdio.h>
#include <stdlib.h>
#include <math.h>

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

int division(int a , int b)
{
	
	int q = 0;
	int r = a;
	while ( r >= b )
	{
	
		q = q + 1;
		r = r - b;
	}
	printf("ur quotient is %d & the rest is %d\n",q,r);

	return 0 ;
}

int main (int argc, char **argv )
{

	double result;

	printf("Welcome to the Calculator\n");
	if ( argc < 3 )
	{
	
		printf("Usage : ./exo1 a operator b\n");
		exit(1);
	}
//	printf("%c",argv[2][0]);
	
	switch (argv[2][0])
	{

		case '!' :
                        result = factorielle(atoi(argv[1]));
                        printf("ur result :  %.2lf\n",result);
                        break;

		case '^' :
                        result = pow(atoi(argv[1]),atoi(argv[3]));
                        printf("ur result :  %.2lf\n",result);
                        break;

		case '*' :
			result = atoi(argv[1])*atoi(argv[3]);
			printf("ur result :  %.2lf\n",result);
			break;

		case 'x' :
			result = atoi(argv[1])*atoi(argv[3]);
			printf("ur result :  %.2lf\n",result);
			break;
		
		case '+' :
                        result = atoi(argv[1])+atoi(argv[3]);
                        printf("ur result :  %.2lf\n",result);
                        break;
	
		case '-' :	
			result = atoi(argv[1])-atoi(argv[3]);
			printf("ur result :  %.2lf\n",result);
			break;	
		case '/' :	
			result = atoi(argv[1])/atoi(argv[3]);
			printf("ur result :  %.2lf\n",result);
			break;

		case '%' :
			result = division(atoi(argv[1]),atoi(argv[3]));
			break;

		case 'g' :
			result = pgcd(atoi(argv[1]),atoi(argv[3]));
                        printf("votre resultat :  %.2lf\n",result);
                        break;

		default :
			printf("Error! Operator is not correct\n");	
	}

	return 0;

}
