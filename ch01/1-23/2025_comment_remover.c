#include <stdio.h>
#define IN 1
#define OUT 0
#define MAXFILENAME 100

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

// ## One function that runs all functions below. Functions below check if we are in a string literal, char literal, single line comment, or multiline comment.

// ### check if in a single line comment

int checksinglelinecomment()
{
    // If we have // , we aren't in string literal, or char literal, and no escape character has fucked with us, in single line comment

    if ((currentchar == '/') && (prevchar == '/') && (stringliteral == OUT) && (charliteral == OUT) && (multilinecomment == OUT))
    {
        singlelinecomment = IN;
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

int checkmultilinecomment()
{
    if ((currentchar == '*') && (prevchar == '/') && (stringliteral == OUT) && (charliteral == OUT) && (singlelinecomment == OUT))
    {
        multilinecomment = 'IN';
    }

    /*Once inside a multi-line comment, check for end of multiline comment*/
    else if ((multilinecomment == 'IN') && (currentchar == '/') && (prevchar == '*'))
    {
        multilinecomment = 'OUT';
    }
    else
    {
        multilinecomment = multilinecomment;
    }
    return multilinecomment;
}

// #### check if in char literal

int checkcharliteral()
{
    if ((currentchar == '\'') && (prevchar != '\\') && (charliteral == OUT))
    {
        charliteral = IN;
    }
    else if ((currentchar == '\'') && (prevchar != '\\') && (charliteral == IN))
    {
        charliteral = OUT;
    }
    else
    {
        charliteral = charliteral;
    }
    return charliteral;
}

// #### check if in string literal

int checkstringliteral()
{
    if ((currentchar == '\'') && (prevchar != '\\') && (stringliteral == OUT))
    {
        stringliteral = IN;
    }
    else if ((currentchar == '\'') && (prevchar != '\\') && (stringliteral == IN))
    {
        stringliteral = OUT;
    }
    else
    {
        stringliteral = stringliteral;
    }
    return stringliteral;
}

// open a c file to remove comments from

FILE *INPUT()
{
    char filename[MAXFILENAME + 1];
    int n = 0;

    printf("\nenter a filename to remove comments from below!\n\n");
    while ((n < MAXFILENAME) && (filename[n] = getc(stdin)) != EOF)
    {
        if (filename[n] != '\n')
        {
            n++;
        }
        else
        {
            filename[n] == '\0';
            break;
        }
    }

    FILE *file_ptr;

    file_ptr = fopen(filename, "r");
    return file_ptr;
}

/*

1. program needs to open a file

2. program needs to have 2D array, input[LINE][COLUMN], output[LINE][COLUMN]

3. needs for loop that iterates through program input. y is line, x is column

4. needs to know MAXLINE and MAXCOLUMN. needs to count this.

5. y =

6. when singleline comment ends
    - `\n` must be placed
    - `\0` must be placed after
    - LINE must iterate.

4



*/