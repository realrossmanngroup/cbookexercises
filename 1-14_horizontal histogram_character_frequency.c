#include <stdio.h>

/* output histogram based on word count */

double main()
{
    int c, i, j, k; /*define character we get from input,
                        count of new characters, & loop variables*/

    int charcount[1000]; /*Array counting number of times an ascii character has been used */

    int maxascii; /*highest ascii character count*/
    maxascii = 0;

    for (i = 0; i < 1000; ++i) /*Set all counts of charcounts to 0*/
    {
        charcount[i] = 0;
    }

    while ((c = getchar()) != EOF)
    {
        if (c < 998)
        {
            ++charcount[c];
            if (maxascii < c)
            {
                maxascii = c;
            }
        }

        else /*wordcount[1000] allows charcounts up to 1000 characters. Do not allow someone to get near this limit and write outside the program for security reasons*/

        {
            printf("HARDENED MEMORY ALLOCATOR ON THE FIRST CHAPTER OF THE BOOK!!!!");
            exit(0);
        }
    }
    for (j = 1; j <= maxascii; j++) /*print charcount*/
    {
        printf("\n%3c ", j);
        for (k = 0; k < charcount[j]; k++)
        {
            printf("|"); /*print number of words visually of each charcount*/
        }
    }
    printf("\n\nThe highest ASCII character was the character \"%c\" ", maxascii);
}