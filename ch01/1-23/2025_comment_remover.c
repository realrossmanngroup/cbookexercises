#include <stdio.h>
#define IN 1
#define OUT 0

// THESE MUST BE GLOBAL VARIABLES SO FUNCTION CAN SEE THEM
// Making global variables to keep things cleaner

// keep track of comment status
int charliteral = OUT;
int stringliteral = OUT;
int singlelinecomment = OUT;
int multilinecomment = OUT;

// record characters
int currentchar = 0;
int prevchar = 0;

void main()
{
}

/* how to make this program

### variables needed

#### keep track of comment status

- charliteral
- stringliteral
- singlelinecomment
- multilinecomment

#### keep track of characters

- currentchar
- prevchar
*/

// # functions needed

// ## IMPORTANT: THESE NEED CURRENTCHAR, PREVCHAR, STRINGLITERAL, CHARLITERAL, SINGLELINECOMMENT, MULTILINECOMMENT TO BE GLOBAL VARIABLES

// ### check if in a single line comment

int checksinglelinecomment()
{
    // If we have // , we aren't in string literal, or char literal, and no escape character has fucked with us, in single line comment

    if ((currentchar == '/') && (prevchar == '/') && (prevchar - 1 != '\\') && (stringliteral == OUT) && (charliteral == OUT) && (multilinecomment == OUT))
    {
        -singlelinecomment = IN;
    }

    /*
    Once we've entered a single line comment, we need a way to check if we have left the single line comment.
    Leaving a singleline comment occurs on a new line, so we'll check for a newline character.
    Remeber that a newline can be escaped by a backslash.
    */

    else if ((singlelinecomment == IN) && (currentchar == '\n') && (prevchar != '\\'))
    {
        singlelinecomment = OUT;
    }

    /*
    Now we need a condition for what to do if we are not entering, or leaving a singleline comment, which is to
    keep singlelinecomment as it is without modifying it.
    */

    else
    {
        singlelinecomment = singlelinecomment;
    }

    return singlelinecomment;
}

// ### check if in double line comment

int checkdoublelinecomment()
{
    if ((currentchar == '*') && (prevchar == '/') && (prevchar - 1 != '\\') && (stringliteral == OUT) && (charliteral == OUT) && (singlelinecomment == OUT))
    {
        doublelinecomment = 'IN';

        else if (doublelinecomment == 'IN')
    }
}

- if (currentchar == *) && (prevchar ==

#### check if in single line comment

#### check if out of single line comment

#### check if in char literal

#### check if in string literal

- doesn't count if in single or multi line comment


### Logic for comments ###

#### If in a double line comment:

- don't move forward
- check for end of comment


#### If in single line comment

- don't move forward
- check for newline


*/