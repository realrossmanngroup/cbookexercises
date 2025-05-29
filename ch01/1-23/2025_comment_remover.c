#include <stdio.h>
#define IN 1
#define OUT 0
#define MAXFILENAME 100
#define MAXLINES 1000
#define MAXCOLUMNS 1000
#define YES 1
#define NO 0

// THESE MUST BE GLOBAL VARIABLES SO FUNCTION CAN SEE THEM

// record input file and output file

char input[MAXLINES][MAXCOLUMNS];
char output[MAXLINES][MAXCOLUMNS];

int MAXLINECOUNT = 0;
int MAXLINELENGTH = 0;

// keep track of comment status
int charliteral = OUT;
int stringliteral = OUT;
int singlelinecomment = OUT;
int multilinecomment = OUT;

// record characters
int currentchar = 0;
int prevchar = 0;

// function declarations

int loadprogram();
int checkcharliteral();
int checkstringliteral();
int checksinglelinecomment();
int checkmultilinecomment();

void main()
{
    // how  many lines is the input?
    int linecount = 0;

    linecount = loadprogram();
    for (int x = 1; x <= linecount; x++)
    {
        printf("%s", input[x]);
    }
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
        multilinecomment = IN;
    }

    /*Once inside a multi-line comment, check for end of multiline comment*/
    else if ((multilinecomment == IN) && (currentchar == '/') && (prevchar == '*'))
    {
        multilinecomment = OUT;
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

int loadprogram()
{
    int ISFILEOPEN = NO;
    int LINE = 0;
    char filename[MAXFILENAME + 1]; // where filename will be stored
    FILE *program;

    while (ISFILEOPEN == NO)

    {
        printf("\nenter a filename to remove comments from below!\n\n");
        scanf("%100s", filename);

        program = fopen(filename, "r");

        if (program != NULL)
        {
            printf("\nprogram opened successfully!\n");
            ISFILEOPEN = YES;
            break;
        }
        else
        {
            ISFILEOPEN == NO;
            printf("\nprogram failed to open, file is null! Try again\n");
        }
    }
    while (fgets(input[LINE], (MAXCOLUMNS - 3), program) != NULL)
    {
        if (LINE < MAXLINES - 2)
        {
            LINE++;
        }
        else
        {
            break;
        }
    }
    return LINE;
}

void main()
{

    int line = 0;
    int column = 0;

    loadprogram();

    for (line = 0; line >= MAXLINELENGTH; line++)
    {
        for (column = 0; column != '\0'; column++)
        {

            /* Here we are going through each character. 
            what do we need to do?
            
            1. */
        }
    }
}

/*

1. program needs to open a file

```
loadprogram();

```

2. program needs to have 2D array, input[LINE][COLUMN], output[LINE][COLUMN]

DONE

3. needs for loop that iterates through program input. y is line, x is column

for()

4. needs to know MAXLINE and MAXCOLUMN. needs to count this.

5. y =

6. when singleline comment ends
    - `\n` must be placed
    - `\0` must be placed after
    - LINE must iterate.

4



*/
