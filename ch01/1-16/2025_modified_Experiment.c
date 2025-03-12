#include <stdio.h>

#define MAXLINE 1000 /* maximum input line length */

int oldgetline(char line[], int maxline);
void copy(char to[], char from[]);

/* print the longest input line */
int main()
{
    int len;               /* current line length */
    int max;               /* maximum length seen so far */
    char line[MAXLINE];    /* current input line */
    char longest[MAXLINE]; /* longest line saved here */

    max = 0;
    while ((len = oldgetline(line, MAXLINE)) > 0)
    {
        if (len > max)
        {
            max = len;
            copy(longest, line);
        }
        printf("\nlongest:\n%s\nline:\n%s\n\n", longest, line);

    }

    if (max > 0) /* there was a line */
        printf("\n%s\n\n", longest);
    printf("the longest line was %d characters long\n\n", max);

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
        if (i < (lim - 2))
        {
            s[i] = c;
            // debug
            // printf("\ns[i] = %c, i = %d, debug line %d\n", s[i], i, __LINE__);
            if (c == '\n')
            {

                s[i] = '\0';
                // hyper debug
                /*for (int x = 0; x <= i; x++)
                {
                    printf("\ns[i] = %c, s[i + 1] = %c, i = %d, debug line %d\n", s[i], s[(i + 1)], i, __LINE__);
                }*/
                i++;

                if (i < lim - 2)
                {
                    s[i] = '\0';
                    // debug
                    // printf("\ns[i] = %c, i = %d, s[i + 1] = %c, debug line %d\n", s[i], i, s[i + 1], __LINE__);
                    break;
                }
            }
        }
        else
        {

            // debug
            // printf("\nc is %c, i = %d, debug line %d\n", c, i, __LINE__);

            continue;
        }
    }
    return i;
}

/* copy: copy 'from' into 'to'; assume to is big enough */
void copy(char to[], char from[])
{
    int i;

    i = 0;
    while ((to[i] = from[i]) != '\0')
    {
        ++i;
    }
}

/*This program cannot accept more than 4095
characters. it tops out at that point and i can't
figure out why it won't count past that point.
the program successfully shows you as many characters
as possible from the longest line after you hit
enter with no text input, or ctrl-d to end the program.
however, the program cannot count more than 4095 characters.
the loop stops at that point. i hope i can figure this
one out later on.*/