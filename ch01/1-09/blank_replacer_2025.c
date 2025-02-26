#include <stdio.h>
// create logic for blank detection.
#define YES 1
#define NO 0

/* Count how many new lines, blank characters, and characters
are present in input*/
void main()
{
    int c;
    int lastcharblank;
    lastcharblank = NO;

    while ((c = getchar()) != EOF) // get input from user
    {
        if ((c == ' ') && (lastcharblank == YES))
        {
            // don't add character if it's blank & last char is blank
        }
        else if ((c == ' ') && (lastcharblank == NO))
        {
            // if input is blank & last char is not a blank, insert blank
            putchar(c);
            // mark that last character was a blank
            lastcharblank = YES;
        }
        else
        {
            // add character to screen if it is a normal character
            putchar(c);
            // make sure last character is not set as a blank
            lastcharblank = NO;
        }
    }
}

/*
PLAN: 

How to make a program that copies input to output while
replacing multiple blanks with single blanks:

1. write logic to collect input characters and put output
character on screen for each.

2. if a blank & lastcharblank=no, then lastcharblank=yes & putcharc

3. if a blank and lastcharblank=yes, no putcharc.

4. otherwise putcharc

*/