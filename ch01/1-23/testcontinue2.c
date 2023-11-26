#include <stdio.h>

int main()
{
    int x = 0;
    int c;

    for (x = 0; x < 100; x++)
    {
        printf("x is %d\n", x);
        printf("Enter a number, any number!\n");

        c = getchar(); // Read the first character
        while (getchar() != '\n')
        {
            ; // Read and discard characters until newline
        }

        if (c - '0' == 5)
        {
            continue; // If the user enters 5, continue the loop
        }

        printf("the rest of the stupid loop is going, tralalalalal!\n");
        printf("more dumb shit you should avoid by pressing 5\n");
    }
}


if ((comment[a][y] == '\"' && (y == 0 || comment[a][y-1] != '\\')) || (comment[a][y] == '\'' && (y == 0 || comment[a][y-1] != '\\'))) {
    stringLiteral = (stringLiteral == OUT) ? IN : OUT;
}
