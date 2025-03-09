#include <stdio.h>
#include <stdlib.h>

#define IN 1  /* inside a word */
#define OUT 0 /* outside a word */

// this program prints each word on a new line

void main()
{
    int c, state;
    state = OUT; // in or out of word?

    // new variables for horizontal histogram

    int howlong = 0;      // word length
    int count[101];       // stores how many words were typed for each word length
    int longestword = 0;  // length of longestword word
    int shortestword = 0; // length of shortestword word
    int highestcount = 0; // what was the most time a word of a specific length was used

    // clear array for counting how many words for each wordlength to 0

    for (int set = 0; set <= 100; set++)
    {

        count[set] = '\0';
    }

    while ((c = getchar()) != EOF)
    {

        /* if a space, tab, or nonsensical character is entered,
        assume that we are now OUT of a word. */

        if (c == ' ' || c == '\n' || c == '\t' ||
            (c >= 33 && c <= 64) || (c >= 91 && c <= 96) || (c >= 123 && c <= 126))

        {
            /* this is separated into a nested if/else statement
            so that spaces/tabs do not get entered as new words.
            we only want to hit enter and have WORDS be counted,
            not tabs/spaces/other nonsense. therefore, only if we are In
            a word when a space/tab/newline is created are we going to consider
            us as having moved from in a word to out
            */
            if (state == IN)
            {
                // record we're out of a word.
                state = OUT;
                if (howlong < 100)
                {
                    ++count[howlong]; // add that wordlength to the count
                }
                else
                {
                    printf("\n\nExiting program due to memory insecurity. Not letting memory insecure stuff just because I'm on chapter 1\n(thank you eron for teaching me when I was a noob!)\n\n");
                    exit(0); // Exits program without allowing buffer overflow
                }

                if (howlong > longestword)
                {
                    longestword = howlong;
                }
                howlong = 0; // reset wordlength to 0
            }

            /* if we are already out of a word, keep the state at out,
            but do not print the word on a new line.*/
            else
            {
                state = OUT;
            }
        }

        /* if a normal character is typed while we were OUTSIDE
        a word, count us as in a word & increment word length
        counter. this switch to being in a word only happens
        once the first character of a word is typed */
        else if (state == OUT)
        {

            state = IN;
            ++howlong;
        }
        /* if a normal character is typed while we are IN a word,
        add another character to word length counter */
        else
        {
            ++howlong;
        }
    }

    // figure out shortestword word

    for (int x = 0; count[x] < 1; x++)
    {
        shortestword = x + 1;
    }

    // figure out highest count of a word of a specific length

    for (int x = 0; x <= longestword; x++)
    {
        if (count[x] > highestcount)
        {
            highestcount = count[x];
        }
    }

    // vertical histogram

    for (int y = highestcount; y > 0; y--)
    {

        /*print "wordcount" next to y axis on bottom
        horizontally if y axis is 9 or less. if y axis
        is 9 or more, then print wordcount vertically*/
        if (highestcount < 9)
        {
            if (y == 1)
            {
                printf("wordcount\t%3.0d | ", y);
            }
            else
            {
                printf("\t\t%3.0d | ", y);
            }
        }
        else
        {

            if (y == 9)
            {
                printf("\tw\t%3.0d | ", y);
            }
            else if (y == 8)
            {
                printf("\to\t%3.0d | ", y);
            }
            else if (y == 7)
            {
                printf("\tr\t%3.0d | ", y);
            }
            else if (y == 6)
            {
                printf("\td\t%3.0d | ", y);
            }
            else if (y == 5)
            {
                printf("\tc\t%3.0d | ", y);
            }
            else if (y == 4)
            {
                printf("\to\t%3.0d | ", y);
            }
            else if (y == 3)
            {
                printf("\tu\t%3.0d | ", y);
            }
            else if (y == 2)
            {
                printf("\tn\t%3.0d | ", y);
            }
            else if (y == 1)
            {
                printf("\tt\t%3.0d | ", y);
            }
            else
                printf("\t\t%3.0d | ", y);
        }
        for (int x = 1; x <= longestword; x++)
        {
            if (count[x] >= y)
            {
                printf("*  ");
            }
            else
            {
                printf("   ");
            }
        }
        printf("\n");
    }
    // dashes between graph & x axis legend
    printf("\t\t    ");
    for (int bottomcount = 0; bottomcount < longestword; bottomcount++)
    {
        printf("___");
    }

    printf("\n\t\t ");

    // x axis legend
    for (int bottomcount = 0; bottomcount <= longestword; bottomcount++)
    {
        printf("%3.0d", bottomcount);
    }
    // label for x axis
    printf("\n\n\t\t\twordlength\n\n");

    /* create horizontal histogram

    // label for y axis
    printf("\n\b");

    for (int x = shortestword; x <= longestword; x++)
    { // print "wordlength" horizontally on last y axis legend line if y is less than 10.
        if (longestword < 10)
        {
            if (x < longestword)
            {
                printf("%4.0d |", x);
            }
            else
            {
                printf("wordlength%4.0d |", x);
            }
        } // if y is MORE than 10 we have enough space to type out "wordlength" vertically.
        else
        {
            if (x == (longestword - 9))
            {
                printf("w%4.0d |", x);
            }
            else if (x == (longestword - 8))
            {
                printf("o%4.0d |", x);
            }
            else if (x == (longestword - 7))
            {
                printf("r%4.0d |", x);
            }
            else if (x == (longestword - 6))
            {
                printf("d%4.0d |", x);
            }
            else if (x == (longestword - 5))
            {
                printf("l%4.0d |", x);
            }
            else if (x == (longestword - 4))
            {
                printf("e%4.0d |", x);
            }
            else if (x == (longestword - 3))
            {
                printf("n%4.0d |", x);
            }
            else if (x == (longestword - 2))
            {
                printf("g%4.0d |", x);
            }
            else if (x == (longestword - 1))
            {
                printf("t%4.0d |", x);
            }
            else if (x == (longestword))
            {
                printf("h%4.0d |", x);
            }
            else
            {
                printf("%4.0d |", x);
            }
        }

        for (int bar = 0; bar < count[x]; bar++)
        {
            printf("*  ");
        }
        printf("\n");
    }

    // dashes between graph & x axis legend
    printf("      ");
    for (int bottomcount = 0; bottomcount < highestcount; bottomcount++)
    {
        printf("___");
    }
    // x axis legend
    printf("\n ");
    for (int bottomcount = 0; bottomcount <= highestcount; bottomcount++)
    {
        printf("%3.0d", bottomcount);
    }
    // label for x axis
    printf("\n\nwordcount\n\n");
*/
}
