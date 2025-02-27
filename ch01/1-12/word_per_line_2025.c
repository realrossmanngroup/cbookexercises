#include <stdio.h>
#define IN 1  /* inside a word */
#define OUT 0 /* outside a word */

// this program prints each word on a new line

void main()
{
    int c, nl, nw, charcount, state;
    state = OUT;
    nl = nw = charcount = 0;

    // create character array that will store the word
    char word[100];
    // set it to nothing
    for (int count = 0; count < 100; count++)
    {
        word[count] = '\0';
    }

    while ((c = getchar()) != EOF)
    {

        /* if a space, tab, or nonsensical character is entered,
        assume that we are now OUT of a word, and then print whatever
        word was typed and hit enter to create a new line.
        */
        if (c == ' ' || c == '\n' || c == '\t' ||
            (c >= 33 && c <= 64) || (c >= 91 && c <= 96) || (c >= 123 && c <= 126))

        {
            /* this is separated into a nested if/else statement
            so that spaces/tabs do not get printed on new lines.
            we only want to hit enter and have WORDS print on new lines,
            we do not want lines for tabs. therefore, only if we are In
            a word when a space/tab/newline is created are we going to print
            the word
            */
            if (state == IN)
            {
                // record we're out of a word.
                state = OUT;
                /* print the word, character by character
                    and make sure that it only prints the exact
                    length of the word based on the recorded
                    character count for the word */
                for (int x = 0; x <= charcount; x++)
                {
                    printf("%c", word[x]);
                }
                // print a newline
                printf("\n");

                // clear the word array
                for (int count = 0; count < 100; count++)
                {
                    word[count] = '\0';
                }
                // set charcount to 0
                charcount = 0;
            }

            /* if we are already out of a word, keep the state at out,
            but do not print the word on a new line.*/
            else
            {
                state = OUT;
            }
        }

        /* if a normal character is typed while we were OUTSIDE
        a word, count us as in a word. this switch to being
        in a word only happens once the first character of a word is
        typed*/
        else if (state == OUT)
        {

            // record the first letter of the word
            word[charcount] = c;
            // increment character count so next letter goes into the next slot in char arrray
            ++charcount;
            state = IN;
        }
        /* if a normal character is typed while we are IN a word,
        add the character to the word and up the charcount*/
        else
        {
            word[charcount] = c;
            ++charcount;
        }
    }
    printf("\n");
}

/*

this program has to be much more ambitious than before.

1. we need to create & initialize a character array.
2. once we are in a word, it needs to save its contents to an array
3. this means it has to count how many characters we are in every time
a character is typed, so that it knows where to add to the array.
4. the count of how many characters we are into the word has to be
reset each time we leave a word, back to 0.
5. each time we are out of a word, it has to
a. print the word
b. reset the character count back to 0
c. clear the word array
6. it needs to know the difference between hitting space when inside a word
and hitting space when outside a word so that each space does not result
in a new line

*/