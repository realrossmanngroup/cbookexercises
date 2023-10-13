#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXLINE 1000 /* maximum input line size */

    int get_line(char line[], int maxline);
void copy(char to[], char from[]);
char *reverse(char c[], int sizeofarray);

/* reverse a character array*/
char *reverse(char b[], int sizeofarray)
{
    int g, h; /*variables for loop. One will count down, one will count up.*/
    char *t = (char *)malloc(sizeofarray * sizeof(char));
    for (g = 0, h = sizeofarray - 2; g <= sizeofarray - 2, h >= 0; g++, h--) /*Set loop to count g up and h down; g up from 0, and h down from the end of the array */
    {
        if (b[g] != '\0') /*Only copy stuff over if it isn't null terminated - I don't want to put the null terminator at the beginning of my new character array!*/
        {
            t[h] = b[g];                                               /*set last character of new array as equal to first character of old array, and keep going until loop ends*/
            printf("%c is b[%d] and %c is t[%d]\n", b[g], g, t[h], h); /*print what's going on for debugging purposes*/
        }
        else
        {
            t[sizeofarray - 1] = '\0'; /*when we DO get to a null terminator(end of first character array), make sure to put a null terminator on the END of the new char array*/
        }
    }
    return t;
}

/* get_line: read a line into s, return length */
int get_line(char s[], int lim)
{
    int c, i;
    for (i = 0; i < lim - 1 && (c = getchar()) != EOF && c != '\n'; i++)
    {
        s[i] = c;
    }
    if (c == '\n')
    {
        s[i] = c;
        ++i;
    }
    s[i] = '\0';
    printf("%s\n", reverse(s, sizeof(s) / sizeof(s[0])));
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
    if (max > 0) /* Only print the line if it's over 0 characters*/
    {            /* there was a line */
        printf("%s", reverse(longest, sizeof(longest) / sizeof(longest[0])));
    }
    else
    {
        printf("The line was too short to print, sorry bro\n");
    }
    return 0;
}
