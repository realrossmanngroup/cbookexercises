#include <stdio.h>

#define MAXLINE 1000 /* maximum input line length */
#define TAB 8

int oldgetline(char line[], int maxline);
int blankcount = 0;

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

        printf("%s\n\n", line);
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
        if ((i < (lim - 2) && (c != '\n') && (c != ' ')))
        {
            blankcount = 0;
            s[i] = c;
        }

        else if (c == ' ')
        {
            blankcount++;
            s[i] = c;

            if (blankcount >= TAB)
            {
                i = i - (TAB - 1); // go back to where first blank was

                s[i] = '\t'; // insert tab where the first blank was
                
                // null the rest
                for (int x = (i + 1); x < lim; x++)
                {
                    s[x] = '\0';
                }
                /*
                                // place null terminator where blanks were before.
                                for (int erase = i; erase <= (i + 7); erase++)
                                {
                                    s[erase] = '\0';
                                } */
            }
        }

        else if (c == '\n')

        {
            blankcount = 0;
            s[i] = '\0';

            break;
        }

        else if (i >= lim - 2)
        {
            s[i] = '\0';

            break;
        }

        else
        {

            continue;
        }
    }

    return i;
}

/* HOW TO DO THIS EXERCISE TO TURN 1-20 INTO 1-21:

1. create a system that counts if there are consecutive blanks
2. once we are at 7 consecutive blanks, rewind 7 and replace with tab.
3. clear out the blanks ahead with null terminator. use for loop for this, figure it out later.
4. clear what is used for counting
 */
