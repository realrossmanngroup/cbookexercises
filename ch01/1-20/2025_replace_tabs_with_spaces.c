#include <stdio.h>

#define MAXLINE 1000 /* maximum input line length */

int oldgetline(char line[], int maxline);

/* print the longest input line */
int main()
{
    int len;                 /* current line length */
    char line[MAXLINE];      /* current input line */
    char backwards[MAXLINE]; /* longest line saved here */

    // zero out the arrays

    for (int x = 0; x < MAXLINE; x++)
    {
        line[x] = '\0';
    }

    while ((len = oldgetline(line, MAXLINE)) > 0)
    {
        // debug
        // printf("\nlen = %d debug line %d\n", len, __LINE__);

        printf("%s\n\n", line);

        // debug
        /*
        for (int x = 0; x <= len; x++)
        {
            printf("\nbackwards[%d] is %c debug line %d\n", x, backwards[x], __LINE__);
        }
            */
    }

    return 0;
}

/* oldgetline: read a line into s, return length */
int oldgetline(char s[], int lim)
{
    int c, i;

    for (i = 0; (c = getchar()) != EOF; ++i)
    {
        /* logic to not keep adding stuff to the
        char array s[] if we are close to its limit */
        if ((i < (lim - 2) && (c != '\n') && (c != '\t')))
        {

            s[i] = c;
            // debug
            // printf("\nfirst if ran\ns[%d] = %c, debug line %d\n", i, s[i], __LINE__);
        }

        else if (c == '\t')
        {
            for (int tab8 = i; tab8 < (i + 8); ++tab8)
            {
                s[tab8] = ' ';
                
                //debug 
                // printf("\n\ns[%d] = %c, s[%d] = %c, debug line %d\n\n",tab8, s[tab8], i, s[i],__LINE__);
            }
            i = i + 7;
            continue;
        }

        else if (c == '\n')

        {

            s[i] = '\0';
            // debug
            // printf("\nnewline if statement ran debug line %d\n", __LINE__);
            break;
        }

        else if (i >= lim - 2)
        {
            s[i] = '\0';
            // debug
            // printf("\nif i is equal to lim-2 ran\n\ns[i] = %c, i = %d, s[i - 1] = %c, debug line %d\n", s[i], i, s[i - 1], __LINE__);
            break;
        }

        else
        {

            // debug
            // printf("\n\nelse ran\nc is %c, i = %d, debug line %d\n", c, i, __LINE__);

            continue;
        }
    }
    // debug
    // printf("\ni = %d debug line %d", i, __LINE__);
    return i;
}
