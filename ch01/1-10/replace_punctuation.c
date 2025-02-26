#include <stdio.h>

/*
replace tabs with \t, backspace with \b, and backslash
with \\

Using ascii values for tab, backspace, and backslash to
detect whether C is a tab, backspace, or backslash
*/
void main()
{
    int c;

    while ((c = getchar()) != EOF) // get input from user
    {

        if (c == 9)
        {
            printf("\\t");
        }
        else if (c == 92)
        {

            printf("\\\\");
        }
        else if (c == 8)
        {
            printf("\\b");
        }
        else
        {
            putchar(c);
        }
    }
}
