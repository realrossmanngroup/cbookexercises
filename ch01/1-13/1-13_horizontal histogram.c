#include <stdio.h>
#include <stdlib.h>

/* output histogram based on word count */

#define NO 1 /*this is going to be used to tell if we're in or out of a word*/
#define YES 0

double main()
{

    int c, nc, i, j, k; /*define character we get from input,
                        count of new characters, & loop variables*/

    int INWORD; /*Are we in a word or out of a word for word counter?*/

    int wordlength[100]; /*Array counting number of characters
                        for different wordlengths*/

    int maxlength; /*Longest word*/
    nc = 0;
    maxlength = 0;

    for (i = 0; i < 100; ++i) /*Set all counts of wordlengths to 0*/
    {
        wordlength[i] = 0;
    }

    while ((c = getchar()) != EOF)
    {
        if (c == ' ' || c == '\n' || c == '\t') /*If we leave a word,
                                        add to the count of words with that
                                        character length*/
        {
            INWORD = NO;
            ++wordlength[nc];
            if (maxlength < nc) /*make maxlength equal to charcount
                                    if it's smaller than current charcount*/
            {
                maxlength = nc;
            }
            nc = 0;
        }
        else
        {
            INWORD = YES; /*if we're inside a word, keep counting chars*/
            if (nc < 98)
            {
                ++nc;
            }
            else /*wordcount[100] allows wordlengths up to 100 characters. Do not allow someone to get near this limit and write outside the program for security reasons*/
            {
                printf("HARDENED MEMORY ALLOCATOR ON THE FIRST CHAPTER OF THE BOOK!!!!");
                exit(0);
            }
        }
    }

    for (j = 1; j <= maxlength; j++) /*print charcount*/
    {
        printf("\n%3d characters ", j);
        for (k = 0; k < wordlength[j]; k++)
        {
            printf("|"); /*print number of words visually of each charcount*/
        }
    }
    printf("\n\nThe longest word was %d characters long", maxlength);
}
