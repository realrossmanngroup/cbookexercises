#include <stdio.h>

#define MAXLINE 1000 /* maximum input line size */

char reversedversion[MAXLINE];

int get_line(char line[], int maxline);
void copy(char to[], char from[]);
void *reverse(char c[], int sizeofarray);

/* reverse a character array*/
void *reverse(char b[], int sizeofarray)
{
    extern char reversedversion[MAXLINE]; /*declare global variable we will move what we're reversing to*/
    int i, g, h;                          /*variables for loop. One will count down, one will count up.*/
    /*erase reversedversion if something was already in it*/
    for (i = 0; i <= MAXLINE; i++)
    {
        reversedversion[i] = ' ';
    }
    for (g = 0, h = sizeofarray - 2; g <= sizeofarray - 2, h >= 0; g++, h--) /*Set loop to count g up and h down; g up from 0, and h down from the end of the array */
    {
        if (b[g] != '\0') /*Only copy stuff over if it isn't null terminated - I don't want to put the null terminator at the beginning of my new character array!*/
        {
            reversedversion[h] = b[g];                                                             /*set last character of new array as equal to first character of old array, and keep going until loop ends*/
            printf("%c is b[%d] and %c is reversedversion[%d]\n", b[g], g, reversedversion[h], h); /*print what's going on for debugging purposes*/
        }
        else
        {
            reversedversion[sizeofarray - 1] = '\0'; /*when we DO get to a null terminator(end of first character array), make sure to put a null terminator on the END of the new char array*/
        }
    }
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
    reverse(s, i + 1);
    printf("%s\n", reversedversion);
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
    extern char reversed[MAXLINE];
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
        reverse(longest, max);
        printf("%s\n", reversedversion);
    }
    else
    {
        printf("The line was too short to print, sorry bro\n");
    }
    return 0;
}
