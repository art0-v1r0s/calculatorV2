#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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

int main ( int argc,char ** argv )

{

	(void)argc;	
	double result;

	char * calcul = malloc( strlen ( argv[1] ) + 1 );
	if ( calcul != NULL )
	{
	
		strcpy( calcul , argv[1] );
	}else
	{
	
		return 1;
	}
	double nb1;
	double nb2;
	char op;
	
	printf("Welcome to the Calculator\n");

	//printf("argv1 in calcul %s\n",calcul);
		
	printf("ur calcul %s\n",calcul);

	sscanf(calcul,"%lf %c %lf",&nb1,&op,&nb2);
	
	free( calcul );
	switch (op)
	{

	case '!' :
	result = factorielle( nb1 );
	printf("ur result :  %.2lf\n",result);
	break;

	case 'v' :
	result = sqrt( nb1 );
	printf("ur result :  %.2lf\n",result);
	break;

	case '^' :
	result = pow( nb1 , nb2 );
	printf("ur result :  %.2lf\n",result);
	break;

	case '*' :
	result = nb1 * nb2;
	printf("ur result :  %.2lf\n",result);
	break;

	case 'x' :
	result = nb1 * nb2;
	printf("ur result :  %.2lf\n",result);
	break;

	case '+' :
	result = nb1 + nb2;
	printf("ur result :  %.2lf\n",result);
	break;

	case '-' :	
	result = nb1 - nb2;
	printf("ur result :  %.2lf\n",result);
	break;	
	case '/' :	
	result = nb1 / nb2;
	printf("ur result :  %.2lf\n",result);
	break;

	case '%' :
	result = division( nb1 , nb2 );
	break;

	case 'g' :
	result = pgcd(nb1,nb2);
	printf("votre resultat :  %.2lf\n",result);
	break;

	case 'e' :
	result = exp(nb1);
	printf("votre resultat :  %.2lf\n",result);
	break;

	case 'l' :
	result = log(nb1);
	printf("votre resultat :  %.2lf\n",result);
	break;

	default :
	printf("Error! Operator is not correct\n");	
	
	}

		return 0;
	}
