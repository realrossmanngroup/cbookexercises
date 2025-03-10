#include <stdio.h>

#define MAXLINE 1000 /* maximum input line length */

int oldgetline(char line[], int maxline);

/*NOTES TO SUCCEED:
1. need to set up function to reverse
2. need to make sure it accepts LENGTH
3. need to make sure length is KEPT TRACK OF AGAIN
4. need to remove anything that removes trailing blanks & spaces, NOT NECESSARY.
5. need to make sure null terminator is placed in proper position*/
char reverse(char forwards[], char backwards[], int length);

int main()
{
    int len = 0;            /* current line length */
    char line[MAXLINE];     /* current input line */
    char reversed[MAXLINE]; // where we put the reversed line

    // clear both character arays
    for (int erase = 0; erase < MAXLINE; erase++)
    {
        line[erase] = '\0';
        reversed[erase] = '\0';
    }
    while ((len = oldgetline(line, MAXLINE)) != EOF)
    {

        reverse(line, reversed, len);
        // printf("\nnormal string: \n%s\nreversed string:\n %s", line, reverse(line, reversed, len));
        printf("\nnormal string: \n%s\nreversed string:\n %s", line, reversed);

        // clear both character arays
        for (int erase = 0; erase < MAXLINE; erase++)
        {
            line[erase] = '\0';
            reversed[erase] = '\0';
        }
    }
}

/* oldgetline: read a line into s, return length */
int oldgetline(char s[], int lim)
{
    int c, i;
    for (i = 0; ((c = getchar()) != EOF); ++i)
    {
        /* logic to not keep adding stuff to the
        char array s[] if we are close to its limit */
        if (i < (lim - 2))
        { // only put something into char array if it is not a newline
            if (c != '\n')
            {
                s[i] = c;
                printf("\ndebug line %d\ns[i] = %c\n i = %d\n", __LINE__, s[i], i);
            }

            else
            { /* on newline add null terminator, but don't
                 put newline into char array. make sure to
                 iterate i & return i to the function so
                 the length of what was typed that line is known
                 and added to `len` variable in above while loop*/
                s[i] = '\0';
                printf("\ndebug line %d\ns = %s\n i = %d\n", __LINE__, s, i);

                return i;
                break;
            }
        }
    }
}

char reverse(char forwards[], char backwards[], int length)
{
    int newstring, oldstring;

    for (newstring = 0, oldstring = length; newstring < length, oldstring >= 0; newstring++, oldstring--)
    {
        backwards[newstring] = forwards[oldstring];
        // debug is it properly placing things in new place
        printf("\ndebug line %d\nbackwards[newstring] = %c , newstring = %d\nforwards[oldstring] = %c , oldstring = %d", __LINE__, backwards[newstring], newstring, forwards[oldstring], oldstring);
    }
    backwards[length] = '\0';
    printf("\ndebug line %d\nbackwards[0]: %c, backwards[length] = %c\n", __LINE__, backwards[0], backwards[length]);
    // debug did null terminator arrive
    printf("\ndebug line %d\nbackwards string: %s\n", __LINE__, backwards);
}