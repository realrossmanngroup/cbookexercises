#include <stdio.h>

void main()
{
	printf("Fahrenheit    Celsius \n");
	for (float fahrenheit = 300; fahrenheit >= 0; fahrenheit--){
		printf("%6.2f        %6.2f\n", fahrenheit, ((fahrenheit - 32) * 5/9));
		}
}
