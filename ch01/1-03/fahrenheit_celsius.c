#include <stdio.h>

void main()

{
  float fahrenheit = 0;

  printf("Fahrenheit    Celsius \n");
  while (fahrenheit < 213) {
    printf("%6.2f        %6.2f\n", fahrenheit, ((fahrenheit - 32) * 5 / 9));
    fahrenheit = fahrenheit + 1;
  }
}
