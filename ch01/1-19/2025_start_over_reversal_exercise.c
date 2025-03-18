#include <stdio.h>

#define MAXLINE 1000 /* maximum input line length */

int oldgetline(char line[], int maxline);
void reverse(char to[], char from[], int length);

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
        backwards[x] = '\0';
    }

    while ((len = oldgetline(line, MAXLINE)) > 0)
    {
        // debug
        // printf("\nlen = %d debug line %d\n", len, __LINE__);

        reverse(backwards, line, len);

        printf("%s\n\n", backwards);

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
        if ((i < (lim - 2) && (c != '\n')))
        {
            s[i] = c;
            // debug
            // printf("\nfirst if ran\ns[%d] = %c, debug line %d\n", i, s[i], __LINE__);
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

/*
reverse: copy 'from' into 'to' while reversing, place
null terminator manually at the end. we skip the null
terminator while reversing since the null terminator
represents the end of the string and it doesn't belong
in the beginning!
*/
void reverse(char to[], char from[], int length)
{
    int reversed, original = 0;

    for (reversed = (length - 1), original = 0; reversed == 0, original <= (length - 1); reversed--, original++)
    {
        to[reversed] = from[original];
        // debug
        // printf("\nto[%d] is %c from[%d] is %c debug line %d\n", reversed, to[reversed], original, from[original], __LINE__);
    }

    to[length] = '\0';
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

/*

to do for exercise 1-19, using code from 1-16 as a base

1. remove logic for figuring out longest line, unnecessary.

2. get program to print each line after hitting enter rather
than waiting for it to end

3. figure out how to make reverse function

*/