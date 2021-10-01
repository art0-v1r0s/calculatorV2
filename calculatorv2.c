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

int main (int argc,char ** argv)

{

	(void)argc;	
	double result;

	char * calcul = argv[1];

	char * calcul2 = calloc(strlen(calcul),sizeof(char));

	//char operator[] = "*x/";

	//size_t sizeOp = strlen(operator);
	size_t sizeCal = strlen(calcul);

	if (sizeCal==3)
	{
		switch (calcul[1])
		{

		case '*' :
		result = atof(&(calcul[0])) * atof(&(calcul[2]));
		printf("ur result :  %.2lf\n",result);
		break;

		case 'x' :
		result = atof(&(calcul[0])) * atof(&(calcul[2]));
		printf("ur result :  %.2lf\n",result);
		break;

		case '+' :
		result = atof(&(calcul[0])) + atof(&(calcul[2]));
		printf("ur result :  %.2lf\n",result);
		break;

		case '-' :	
		result = atof(&(calcul[0])) - atof(&(calcul[2]));
		printf("ur result :  %.2lf\n",result);
		break;	
		case '/' :	
		result = atof(&(calcul[0])) / atof(&(calcul[2]));
		printf("ur result :  %.2lf\n",result);
		break;

		case '%' :
		result = division( atof(&(calcul[0])) , atof(&(calcul[2])) );
		break;


		default :
		printf("Error! Operator is not correct\n");
		
		}
	}
	
	for(size_t i = 0; i < strlen(calcul); i++)
	{
		if ( (calcul[i] == 'X' || calcul[i] == '*' || calcul[i] == '/') && calcul2 !=NULL )
		{

		switch (calcul[i])
		{

		case '*' :
		result = atof(&(calcul[i-1])) * atof(&(calcul[i+1]));
		//calcul2[i] = result;
		int flag = 0;
		int cpt = 0;
		for(size_t j = strlen(calcul2);	j > 0 || flag == 1; j--){
			cpt++;
			if(calcul2[j] == '+' || calcul2[j] == '-'){
				flag = 1;
				printf("je suis dans le if + - calcul2");
				//calcul2[i+1] = '\0';
				//int tmp = strlen(calcul2) - cpt;
				//snprintf(calcul2, tmp, "%lf", result);
				
			}
					
		}
		printf("%lf", result);
		break;

		case 'x' :
		result = atof(&(calcul[i-1])) * atof(&(calcul[i+1]));
		break;
	
		case '/' :	
		result = atof(&(calcul[i-1])) / atof(&(calcul[i+1]));
		break;

		default :
		printf("Error! Operator is not correct\n");
		
		}

		printf("ur in *x/\n");
		}
		else
		{
			if(calcul2!=NULL)
			{
			calcul2[i] = calcul[i];
			puts(calcul2);
			}
					

		}
		
	}
	
	printf("Welcome to the Calculator\n");

	//printf("argv1 in calcul %s\n",calcul);
		
	printf("ur calcul %s\n",calcul);

	//sscanf(calcul,"%lf %c %lf",&nb1,&op,&nb2);
	free( calcul2 );
	free( calcul );
	

		return 0;
	}
