#include <stdio.h>

void main()
{

    int c;

    c = (getchar() != EOF);
    printf("Is \"getchar() != EOF\" 1 or 0? One way to find out: C is %d\n\n", c);
}