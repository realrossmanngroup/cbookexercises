#include <stdio.h>

#define MAXLINE 1000 /* maximum input line length */

int oldgetline(char line[], int maxline);

int main()
{
    int len = 0;        /* current line length */
    char line[MAXLINE]; /* current input line */

    while ((len = oldgetline(line, MAXLINE)) != EOF)
    {

        {
            printf("\n%s\n", line);
            for (int erase = 0; erase < MAXLINE; erase++)
            {
                line[erase] = '\0';
            }
        }
    }

    return 0;
}

/* oldgetline: read a line into s, return length */
int oldgetline(char s[], int lim)
{
    int c, i;
    for (i = 0; (c = getchar()) != EOF && c != '\n'; ++i)
    {
        /* logic to not keep adding stuff to the
        char array s[] if we are close to its limit */
        if (i < (lim - 2))
        { // only put something into char array if it is not a tab/newline/blank
            if ((c != '\t') && (c != '\n') && (c != ' '))
            {
                s[i] = c;
            }

            else if (c == '\n')
            { // on newline add null terminator, but don't put newline into char array
                s[i] = '\0';
                break;
            }
            else if ((c == '\t') || (c == ' '))
            { // for characters we do not want to count, move loop back and don't add

                --i;
            }
        }
    }
}
