#include <stdio.h>

int main()
{

    int x = 0;
    int c;

    for (x = 0; x < 100; x++)
    {

        printf("x is %d\n", x);
        printf("enter a number, any number!\n");
        while (c = getchar() != '\n')
        {
            ;
        }
        if (c - '0' == 5)
        {
            continue;
        }
        else
        {
            break;
        }
    }
}