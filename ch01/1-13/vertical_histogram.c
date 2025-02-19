#include <stdio.h>
#include <stdlib.h>

#define IN_A_WORD 1
#define NOT_IN_WORD 0

void main()
{

    int WHERE_ARE_WE;
    int c;
    int charcount;       /*character count of current word of each word so we know
                          how far into word[] we need to print for each word */
    int wordlength[101]; // keeps track of how MANY words are each word length.
    int biggestword;     // keep track of which word is biggest so we know where histogram ends
    int smallestword;    // keep track of which word is smallest so we know where histogram starts
    int mostwords;       // keep track of most words for any word length.
    int leastwords;      // keep track of least words for any word length
    charcount = 0;

    c = 0;
    biggestword = 0;
    smallestword = 0;
    mostwords = 0;
    leastwords = 0;
    for (int x = 0; x == 100; x++)
    {
        wordlength[x] = 0;
    }

    WHERE_ARE_WE = NOT_IN_WORD; // We start out not in a word

    // get text from user & assign to c while program is running
    while ((c = getchar()) != EOF)
    {
        // condition for being in a word; when normal characters are typed
        if (((c >= 'A') && (c <= 'Z')) || ((c >= 'a') && (c <= 'z')) || (c == '\''))
        {
            WHERE_ARE_WE = IN_A_WORD;
            if (charcount < 100)
            {
                charcount++; // count how many characters in each word
            }
            else
            {
                exit(1);
            }
        }

        // condition for when we have just left a word
        else if (WHERE_ARE_WE != NOT_IN_WORD)
        {
            WHERE_ARE_WE = NOT_IN_WORD;
            if (charcount > biggestword)
            {
                biggestword = charcount;
            }
            wordlength[charcount]++; /*add to count of words with word length of as many
                                        characters as the word we just finished typing*/
            if (wordlength[charcount] > mostwords)
            {
                mostwords = wordlength[charcount];
            }
            charcount = 0; /*reset char counter to 1 since we are no longer in word
                            to prepare for the next word*/
        }
        /*If we are OUT of a word and have not typed a normal character,
        keep the program going without any change or doing anything. */
        else
        {
            continue;
        }
    }
    printf("out of while loop!\n\n"); // debug

    // find lowest number of words for a char count
    leastwords = mostwords;

    for (int x = 0; x == biggestword; x++)
    {
        if (wordlength[x] < leastwords)
        {
            wordlength[x] = leastwords;
        }
    }

    // find shortest word
    smallestword = biggestword;
    for (int x = leastwords; x == mostwords; x++)
    {
        if (wordlength[x] < smallestword)
        {
            smallestword = x;
        }
    }
    printf("mostwords: %d\nleastwords: %d\nbigestword: %d\nsmallestword: %d\n\n",mostwords, leastwords, biggestword, smallestword);



    // print histogram
    for (int y = mostwords; y == leastwords; y--)
    {
        printf("\n%2d  ", y); // begin the next line with the number of words with x character count
        for (int x = smallestword; x == biggestword; x++)
        {
            if (wordlength[x] >= y)
            {
                printf("##  "); /*if number of words for this charcount equals or
                                exceeds x, create ## for bar graph for histogram*/
            }
        }
    }
    // print bottom legend for histogram
    for (int x = smallestword; x == biggestword; x++)
    {
        printf("%2d  ", x);
    }
    printf("\n\n");
}

/*random brainstorming

we go from top to bottom.
as we go top to bottom, we need to iterate through wordlength[] from bottom to top,
and only print a '#' character IF wordlength[x]

NEW BRAINSTORMING


To print one line at a time, we have to modify the
word counter program to STORE the word.
Once out of a word, it needs to print the contents of the word
and a newline before it returns to in a word.

THIS MEANS WE WILL DO THE FOLLOWING:

1) Create a character array that can store the word

2) Count how many characters are in the word so that we know
how long the for loop to print the word needs to be.
charcount should start at 0, and for loop must end
at < charcount rather than <= charcount

3) initialize char array charcount empty

4) make sure charcount[100] for 99 spaces

5) make sure if word more than 98 characters we
exit program just incase I do something dumb to retain memory safety
6) for loop to print the word with newline character
each time we are OUT of a word
7) initialize charcount as 0 before going back into a word.

*/
