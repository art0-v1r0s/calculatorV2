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

int main ( void )
{

	
	double result;

	char calcul[256];
	double nb1;
	double nb2;
	char op;
	
	printf("Welcome to the Calculator\n");

	printf("enter ur calcul :\n");

	fgets(calcul, 256, stdin);

	if ( calcul[ strlen( calcul-1 ) ] == '\n' ) 
	{
		calcul[strlen(calcul-1)]='\0';
	}
		
	printf("%s",calcul);
	sscanf(calcul,"%lf %c %lf",&nb1,&op,&nb2);
	printf("%lf\n",nb1);
	printf("%c\n",op);
	printf("%lf\n",nb2);

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

	default :
	printf("Error! Operator is not correct\n");	
	
	}


		return 0;
	}
