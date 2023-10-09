#include <stdio.h>

float converttocels(float n); /* Declare convertocels as function, return a float, & accept a float as a parameter */

float converttocels(float fahr) /* function to convert fahrenheit to celsius */
{
	float celsius; /* declare variable that will be returned as a float at end of conversion*/

	celsius = 5 * (fahr - 32) / 9; /* math to convert fahrenheit to celsius*/
	return celsius;				   /* return the finished conversion to convertocels function*/
}

float main() /* main function of program*/
{
	int fahr;							 /* declare variable we will use for fahrenheit*/
	for (fahr = 32; fahr <= 212; fahr++) /* loop through all temperatures from freezing to boiling in fahrenheit*/
	{
		printf("%df = %2.2fc\n", fahr, converttocels(fahr)); /* convert them all and print the results as celsius, two decimal points out*/
	}
}
