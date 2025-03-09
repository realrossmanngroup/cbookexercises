#include <stdio.h>

double tocelsius(double fahr);

void main()
{
    // create variabnles for each
    double fahr;
    fahr = 0;

    //do calculation of celsius \
    from fahrenheit according to cels=(5/9(f -32))

    for (fahr == 0; fahr <= 300; fahr = fahr + 1)
    {

        printf("%8.2f %8.2f\n\n", fahr, tocelsius(fahr));
    }
}

double tocelsius(double fahr)
{
    double cels;
    cels = ((5.0 / 9.0) * (fahr - 32));
    return cels;
}

/*This was confusing, if I did 5/9 instead of
5.0/9.0 it would give me a 0 due to integer
division. remember this for later!*/