/* This is garbage but much better than my first
program and was done with no help besides googling
how to copy a file into a C program since this wasn't
in the book yet. There is a janky section I noted
below that I am not proud of that I'd like to come
back to later when I feel I've gotten good enough*/

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
int checkcharliteral(char currentchar, char prevchar);
int checkstringliteral(char currentchar, char prevchar);
int checksinglelinecomment(char currentchar, char prevchar);
int checkmultilinecomment(char currentchar, char prevchar);

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

int commentstatus(char currentchar, char prevchar)
{
    charliteral = checkcharliteral(currentchar, prevchar);
    stringliteral = checkstringliteral(currentchar, prevchar);
    singlelinecomment = checksinglelinecomment(currentchar, prevchar);
    multilinecomment = checkmultilinecomment(currentchar, prevchar);

    if ((singlelinecomment == IN) || (multilinecomment == IN))
    {
        return IN;
    }
    else
    {
        return OUT;
    }
}

int checksinglelinecomment(char currentchar, char prevchar)
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

int checkmultilinecomment(char currentchar, char prevchar)
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

int checkcharliteral(char currentchar, char prevchar)
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

int checkstringliteral(char currentchar, char prevchar)
{
    if ((currentchar == '\"') && (prevchar != '\\') && (stringliteral == OUT))
    {
        stringliteral = IN;
    }
    else if ((currentchar == '\"') && (prevchar != '\\') && (stringliteral == IN))
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
            ISFILEOPEN = NO;
            printf("\nprogram failed to open, file is null! Try again\n");
        }
    }
    LINE = 0;
    // print input program to confirm it loaded
    while (fgets(input[LINE], (MAXCOLUMNS - 3), program) != NULL)
    {
        printf("Line %d: %s", LINE, input[LINE]);
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

    charliteral = OUT;
    stringliteral = OUT;
    singlelinecomment = OUT;
    multilinecomment = OUT;

    int oldline = 0;
    int oldcolumn = 0;
    int newline = 0;
    int newcolumn = 0;

    MAXLINECOUNT = loadprogram();

    for (oldline = 0, newline = 0; oldline <= MAXLINECOUNT; oldline++, newline++)
    {
        for (oldcolumn = 0, newcolumn = 0; input[oldline][oldcolumn] != '\0'; oldcolumn++, newcolumn++)
        { // if we're out of a comment, copy over.
            if (commentstatus(input[oldline][oldcolumn + 1], input[oldline][oldcolumn]) == OUT)
            {

                output[newline][newcolumn] = input[oldline][oldcolumn];
            }

            else if (commentstatus(input[oldline][oldcolumn + 1], input[oldline][oldcolumn]) == IN)
            {
                printf("\n\nin a comment: singlelinecomment = %d, multilinecomment = %d, commentstatus =  %d \n\n", singlelinecomment, multilinecomment, commentstatus(input[oldline][oldcolumn], input[oldline][oldcolumn - 1]));

                if (singlelinecomment == IN)
                {
                    output[newline][newcolumn - 1] = '\n';
                    singlelinecomment = OUT;
                    break;
                }
                else if (multilinecomment == IN)
                {
                    newcolumn--; // don't let new move forward as long as we're in a multiline comment.

                    /*THIS IS JANK :(
                    if the program gets to the end of a multiline comment, it copies over the
                    end-of-multiline-comment symbol, because it checks whether it is at the end
                    of a comment AHEAD of time. I did this so it wouldn't copy over the `/*` in
                    the beginning, but this backfired at the end. I could've made the program so
                    it goes back and erases what it copied but that seems dangerous so I thought
                    this was safer. I am also coming back to something I haven't worked on for 
                    3 months that I shouldn't have left off. I want to come back to this and 
                    find a less janky solution later, I'm not proud fo this :( */
                    
                    /* If we are in a multiline comment, it checks to see if the next two characters are
                    leaving the multiline comment. If they are, it sets us out of the multiline comment
                    and skips ahead two in the position we are reading from input so that the 
                    copying logic above doesn't copy the asterisk & foreward slash of the 
                    end of the comment */
                    if (((charliteral == OUT) && (stringliteral == OUT)) && (multilinecomment == IN) && ((input[oldline][oldcolumn + 2] == '/') && (input[oldline][oldcolumn + 1] == '*')))
                    {
                        multilinecomment = OUT;
                        oldcolumn = oldcolumn + 2;
                    }
                }
            }
        }
    }

    // print output

    printf("\n\n\nnow here is the uncommented version!\n\n\n");

    for (int y = 0; y <= MAXLINECOUNT; y++)
    {
        for (int x = 0; output[y][x] != '\0'; x++)
        {
            printf("%c", output[y][x]);
        }
    }
    printf("\n\n\nand there you have it, the program is comment free!\n\n\n");
}

/* what needs to happen:

1. when we hit a singleline comment, move to newline & character 1 for both INPUT and OUTPUT.
2. add null terminator at point of new comment.
3. when we hit a DOUBLELINE comment, stop counting column in output, keep counting input.
4. when end of line is hit in DOUBLELINE comment, output column count increments again as normal(aka normal copying)
5. don't do any bullshit where line in INPUT moves along with line in OUTPUT.

6. once we enter a comment, such as /*,
copy the line from input[][]  to output [][]. easy

/*





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
