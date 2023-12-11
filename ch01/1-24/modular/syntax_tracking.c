#include <stdio.h>
#include "syntax_tracking.h"
#include "definitions.h"

// FUNCTION TO KEEP TRACK OF WHETHER WE ARE, OR ARE NOT, INSIDE OF A STRING, WHEN LOOKING FOR COMMENTS.

int stringinorout(int keeptrackofstring, int keeptrackofchar, char currentchar, char previouschar, int comment)
{

    static int escaped = NO;
    /*handle trolls that put a \ at the end of the line.
    400 lines of code for every use case and it didn't handle a troll
    putting a \ at the end of a line, escaping the newline character and tricking my
    program into thinking we are automatically out of a string because we hit enter on a
    newline. */

    if (previouschar == '\\' && !escaped)
    {
        escaped = YES;
    }
    else if (escaped == YES)
    {
        escaped = NO;
    }

    if ((currentchar == '\n') && (previouschar == '\\') && comment == OUT)
    {
        escaped = OUT;
        didweescapenewline = YES;
    }

    // Handle strings in double quotes, only outside of comments
    if (currentchar == '\"' && !(comment == IN) && !(keeptrackofchar == IN) && !(escaped == YES))
    {
        keeptrackofstring = (keeptrackofstring == OUT) ? IN : OUT;
        stringliteral = keeptrackofstring;
    }

    // Handle characters in single quotes, only outside of comments
    if (currentchar == '\'' && !(comment == IN) && !(keeptrackofstring == IN) && !(escaped == YES))
    {
        keeptrackofchar = (keeptrackofchar == OUT) ? IN : OUT;
        charliteral = keeptrackofchar;
    }

    // Return IN if inside a string or char literal, OUT otherwise
    return (keeptrackofstring == IN || keeptrackofchar == IN) ? IN : OUT;
}

// FUNCTION FOR KEEPING TRACK OF SOMETHING

// COUNTING & KEEPING TRACK OF PARENTHESIS, BRACKETS, CURLY BRACES - WHATEVER YOU WANT, THIS DOES IT!
void trackchars(char openchar, char closechar, int *counter, int *closecounter,
                int *maxcount, int *maxclosed, int ifthisis0youclosedit[], int extraclosedtrackingarray[],
                int opencolumn[], int openline[], int closecolumn[], int closeline[])
{
    //    printf("debug line %d before if in function, program[%d][%d] is %c \n", __LINE__, line, column, program[line][column]);
    if (program[line][column] == openchar) // if we have an open character
    {
        ifthisis0youclosedit[*counter]++; // count up in the array for that character, the number of open characters we're on.
        if (*maxcount < *counter)         // keep track of the highest number char ever hit so we know how far to print at the end
        {
            *maxcount = *counter;
        }
        opencolumn[*counter] = column; // store the column coordinate of the nth opened char in the location array
        openline[*counter] = line;     // store the line coordinate of the nth opened char in the location array
                                       // printf("DEBUG LINE %d OPEN %c FOUND: *counter is %d, ifthisis0youclosedit[%d] is %d, program[%d][%d] is %c \n\n", __LINE__, openchar, *counter, *counter, ifthisis0youclosedit[*counter], openline[*counter], opencolumn[*counter], program[openline[*counter]][opencolumn[*counter]]);
        (*counter)++;                  // iterate counter up so that the next time we see an open char, it is seen as the 2nd, 3rd, 4th, etc.
                                       // printf("DEBUG %d did *counter go up after detecting an opening parenthesis? *counter is %d\n\n",__LINE__, *counter);
    }
    else if (program[line][column] == closechar) // if we have a closed char
    {
        (*counter)--; // iterate *counter down so that we are closing the last char we opened.

        if (*counter < 0)
        {
            extraclosedtrackingarray[*closecounter]++;
            (*closecounter)++;
            *maxclosed = *closecounter;
            *counter = 0;
        }
        else
        {
            ifthisis0youclosedit[*counter]--; // count down in the tracking array for the number char we are on
        }

        closecolumn[*closecounter] = column; // store the column coordinate of the nth closed char in the location array
        closeline[*closecounter] = line;     // store the line coordinate of the nth closed char in the location array

        // printf("DEBUG %d CLOSED %c FOUND: *counter is %d, ifthisis0youclosedit[%d] is %d, extraclosedtrackingarray[%d] is %d, program[%d][%d] is %c \n\n", __LINE__, closechar, *counter, *counter, ifthisis0youclosedit[*counter], *closecounter, extraclosedtrackingarray[abs(*closecounter)], closeline[*counter], closecolumn[*counter], program[closeline[*counter]][closecolumn[*counter]]);
    }
    else
    {
        // printf("debug line %d ending else in function\n", __LINE__);
    }
}

// COUNTING & KEEPING TRACK OF QUOTES.
void trackquotes(char openchar, char closechar, int *counter, int *closecounter,
                 int *maxcount, int *maxclosed, int ifthisis0youclosedit[], int extraclosedtrackingarray[],
                 int opencolumn[], int openline[], int closecolumn[], int closeline[])
{
    //   printf("debug line %d before if in function, program[%d][%d] is %c, program[%d][%d] is %c\n", __LINE__, line, column, program[line][column], line, column + 1, program[line][column + 1]);
    if (program[line][column + 1] == openchar) // if we have an open character
    {
        ifthisis0youclosedit[*counter]++; // count up in the array for that character, the number of open characters we're on.
        if (*maxcount < *counter)         // keep track of the highest number char ever hit so we know how far to print at the end
        {
            *maxcount = *counter;
        }
        opencolumn[*counter] = column + 1; // store the column coordinate of the nth opened char in the location array
        openline[*counter] = line;         // store the line coordinate of the nth opened char in the location array
                                           //      printf("DEBUG LINE %d OPEN %c QUOTE FOUND: *counter is %d, ifthisis0youclosedit[%d] is %d, program[%d][%d] is %c, program[%d][%d] is %c  \n\n", __LINE__, openchar, *counter, *counter, ifthisis0youclosedit[*counter], openline[*counter], opencolumn[*counter], program[openline[*counter]][opencolumn[*counter]], openline[*counter], opencolumn[*counter] + 1, program[openline[*(counter)]][opencolumn[*counter] + 1]);
        (*counter)++;                      // iterate counter up so that the next time we see an open char, it is seen as the 2nd, 3rd, 4th, etc.
        //       printf("DEBUG %d did *counter go up after detecting an opening QUOTE? *counter is %d\n\n", __LINE__, *counter);
    }
    else if (program[line][column] == closechar) // if we have a closed char
    {
        (*counter)--; // iterate *counter down so that we are closing the last char we opened.

        if (*counter < 0)
        {
            extraclosedtrackingarray[*closecounter]++;
            (*closecounter)++;
            *maxclosed = *closecounter;
            *counter = 0;
        }
        else
        {
            ifthisis0youclosedit[*counter]--; // count down in the tracking array for the number char we are on
        }

        closecolumn[*closecounter] = column; // store the column coordinate of the nth closed char in the location array
        closeline[*closecounter] = line;     // store the line coordinate of the nth closed char in the location array

        //       printf("DEBUG %d CLOSED %c QUOTE FOUND: *counter is %d, ifthisis0youclosedit[%d] is %d, extraclosedtrackingarray[%d] is %d, program[%d][%d] is %c, program[%d][%d] is %c  \n\n", __LINE__, closechar, *counter, *counter, ifthisis0youclosedit[*counter], *closecounter, extraclosedtrackingarray[abs(*closecounter)], closeline[*counter], closecolumn[*counter], program[closeline[*counter]][closecolumn[*counter]], closeline[*counter], closecolumn[*counter], program[closeline[*counter]][closecolumn[*counter]]);
    }
    else
    {
        //     printf("debug line %d ending else in function\n", __LINE__);
    }
}

