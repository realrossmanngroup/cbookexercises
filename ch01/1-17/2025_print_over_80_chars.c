#include <stdio.h>

#define MAXLINE 1000 /* maximum input line length */

int oldgetline(char line[], int maxline);
// void copy(char to[], char from[]);

/* print the longest input line */
int main()
{
    int len = 0;        /* current line length */
    char line[MAXLINE]; /* current input line */

    printf("\nlen is %d debug line %d\n", len, __LINE__);
    while ((len = oldgetline(line, MAXLINE)) != EOF)
    {
        if (len > 80)
        {
            printf("\n\nMUSTBEOVER80 %s\n\n", line);
        }
      /* debug
        printf("\nlen is %d debug line %d\n", len, __LINE__); // debug
        printf("\nwhile loop runs again, len is %d debug line %d\n", len, __LINE__);
        */
    }

    return 0;
}

/* oldgetline: read a line into s, return length */
int oldgetline(char s[], int lim)
{
    int c, i;
    for (i = 0; (c = getchar()) != EOF && c != '\n'; ++i)
        /* logic to not keep adding stuff to the
        char array s[] if we are close to its limit */
        if (i < (lim - 2))
        {
            s[i] = c;
            /* debug
            printf("\ns[i] = %c, i = %d, debug line %d\n", s[i], i, __LINE__); 
            */
            if (c == '\n')
            {
                s[i] = c;
                if (i < lim - 2)
                {
                    s[i + 1] = '\0';
                }
                printf("\ns[i] = %c, i = %d, debug line %d\n", s[i], i, __LINE__);
            }
        }
        else

        { /* debug
            printf("\nc is %c, i = %d, debug line %d\n", c, i, __LINE__);
            */

            continue;
        }

    return i;
}

/*
// copy: copy 'from' into 'to'; assume to is big enough
void copy(char to[], char from[])
{
    int i;

    i = 0;
    while ((to[i] = from[i]) != '\0')
        ++i;
}
*/