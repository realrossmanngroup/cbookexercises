#include <stdio.h>
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
    int longestword = 0;  // length of longest word
    int shortestword = 0; // length of shortest word

    // clear array for counting how many words for each wordlength to 0

    for (int set = 0; set <= 100; set++)

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
                return 0; // Exits program without allowing buffer overflow
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

// figure out shortest word

for (int x = 0; count[x] < 1; x++)
{
    shortest = x;
}

// create histogram

printf("wordlength") for (int x = shortest; x <= longest; x++)
{

    printf("3.0%d", x); // print legend for word length for y axis

    /* print out a number of # equal to the count of count[x]

    THINKING OUT LOUD HERE:

    if i */
    for (int bar = 0; bar < count[x]; bar++)
    {
        printf("#");
    }
    printf("\n");
}

// print legend for word count on x axis
for (int bottomcount = 0; bottomcount <= longest; bottomcount++)
{
    printf("%3.0d" bottomcoiunt);
}
printf("\t\t\twordcount\n\n");
}

/*
1. reuse logic for counting in/out of word from 1-12.
2. add array that counts the length of words called count[]
3. use howlong to count how many characters once the word starts.
make sure this starts after character is input.
4. count[(howlong)]  length of the word is howlong, count[howlong]
stores how many words of that length(howlong) there are
5.  ++count[howlong] each time you are out of a word.
6. reset howlong counter to 0 once out of word.
7. make int counting biggest & smallest word.
8. if howlong > longestword, longestword = howlong
9. if howlong < shortestword, shortestword = howlong

10. how do we figure out what to set shortest word to?

largest word can be set dynamically in real time, since it
starts at a natural of 0.

however, shortest word would be a tough one. think this
through once the program works.

this is not necessary for a histogram, the histogram can start
from 2 or 3 characters but that's lame, need histogram to work properly.


for x=0, count[x] < 1, x++
shortest = x

11.

*/

/*

WHERE YOU LEFT OFF:

1. THEN THE FOR LOOP TO MAKE SHORTEST EQUAL TO THE SMALLEST WORD

2. THEN THE LOGIC TO PRINT THIS...
*/