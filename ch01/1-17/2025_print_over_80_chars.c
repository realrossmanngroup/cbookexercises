#include <stdio.h>

#define MAXLINE 1000 /* maximum input line length */

int oldgetline(char line[], int maxline);

int main()
{
    int len = 0;        /* current line length */
    char line[MAXLINE]; /* current input line */

    while ((len = oldgetline(line, MAXLINE)) != EOF)
    {
        if (len > 80)
        {
            printf("\n Your line is over 80 characters! Here it is:\n\n%s\n\n", line);
        }
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

        {
            continue;
        }

    return i;
}
