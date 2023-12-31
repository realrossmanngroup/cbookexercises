#include <stdio.h>
#define TABLENGTH 5 /*How many spaces is a tab?*/

int main()
{
    int c; /* collect input here*/
    int i; /* used to create for loop to replace tabs with spaces*/

    while ((c = getchar()) != EOF) /*Get input from keyboard until user hits ctrl-D*/
    {
        if (c == '\t') /*If the user puts in a tab, we will put a blank character ' ' five times instead of a tab*/
        {
            for (i = 0; i <= TABLENGTH; i++) /*We use a for loop to accomplish this*/
            {
                putchar(' ');
            }
        }
        else /* If the user has put anything but a tab, we just put on screen what they input*/
        {
            putchar(c);
        }
    }
}