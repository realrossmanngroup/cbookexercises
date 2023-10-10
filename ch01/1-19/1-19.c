#include <stdio.h>
#define MAXLINE 1000 /* maximum input line size */

int get_line(char line[], int maxline);
void copy(char to[], char from[]);
int reverse(char s[], int arraylength);
int arraylength;

/* reverse(s), this function is supposed to reverse a character array so a statement entered is backwards */

reverse(char s[], int arraylength)
{
    int i, j;
    char t[arraylength];
    for (i = 0; i <= arraylength; i++)
    {

        for (j = arraylength; i >= 0; j--)
        {

            s[i] = s[j];
        }
    }
    return s;
}

/* get_line: read a line into s, return length */
int get_line(char s[], int lim)
{
    int c, i;
    for (i = 0; i < lim - 1 && (c = getchar()) != EOF && c != '\n'; i++)
    {
        s[i] = c;
    }
    reverse(s, sizeof(s) / sizeof(s[0])); /*this is supposed to reverse the s array so the text is stored backwards*/
    if (c == '\n')
    {
        s[i] = c;
        ++i;
    }
    s[i] = '\0';
    return i;
}

/* copy: copy 'from' into 'to'; assume to is big enough */
void copy(char to[], char from[])
{
    int i;

    i = 0;
    while ((to[i] = from[i]) != '\0')
        ++i;
}

/* print longest input line */
int main()
{
    int len;               /* current line length */
    int max;               /* maximum length seen so far */
    char line[MAXLINE];    /* current input line */
    char longest[MAXLINE]; /* longest line saved here */

    max = 0;
    while ((len = get_line(line, MAXLINE)) > 0)
    {
        if (len > max)
        {
            max = len;
            copy(longest, line);
        }
    }
    if (max > 0)
    { /* there was a line */
        printf("%s", longest);
        printf("The longest line was %d characters long.\n", max);
    }
    return 0;
}
