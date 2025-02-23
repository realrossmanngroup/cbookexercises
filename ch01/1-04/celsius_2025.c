#include <stdio.h>

void main()
{
    // create variabnles for each
    double cels;
    cels = 0;

    //do calculation of Celsius \
    to fahrenheit according to cels=(5/9(f -32))
    printf("Celsius  Fahrenheit\n\n");
    for (cels == 0; cels <= 100; cels = cels + 10)
    {

        printf("%6.0f %6.0f\n\n", cels, (cels * 9.0/5.0) + 32);
    }
}

/*This was confusing, if I did 5/9 instead of
5.0/9.0 it would give me a 0 due to integer
division. remember this for later!*/