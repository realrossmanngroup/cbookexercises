#include <stdio.h>

void main()

{
float celsius = 0;

printf("Celsius    Fahrenheit \n");
while (celsius < 101){
printf("%6.2f     %6.2f\n", celsius, ((celsius * 9/5) + 32));
celsius = celsius + 1;
}
}
