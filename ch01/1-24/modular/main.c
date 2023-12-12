#include <stdio.h>
#include <stdlib.h>
#include "definitions.h"
#include "file_handling.h"
#include "print_output.h"
#include "syntax_tracking.h"

void main()
{
    FILE *inputfile = openfile(); // get input file
    filetoarray(inputfile);       // copy contents of program to program[] char array

    // WE BEGIN LOOKING THROUGH OUR INPUT FILE BELOW

    for (line = 0; line < linecountinput; line++) // go through each line of the program and iterate upwards once at the end
    {
        if ((weare__asinglelinecomment == IN) && (didweescapenewline == NO)) // singleline comments do not persist to the next line. Once we're on a new line,

        {
            weare__asinglelinecomment = OUT;
        }
        for (column = 0; column < howlongisthisline[line]; column++)
        {

            areweinastring = stringinorout(stringliteral, charliteral, program[line][column], program[line][column - 1], weare__acomment); // Keep track of whether we're in a string literal
                                                                                                                                           //  printf("DEBUG line %d: program[%d][%d] is %c, areweinastring is %d, stringliteral is %d, charliteral is %d, comment is %d, singlelinecomment is %d, parencount/counter is %d, extra_closed_parenthesis[%d] is %d\n", __LINE__, line, column, program[line][column], areweinastring, stringliteral, charliteral, weare__acomment, weare__asinglelinecomment, parencount, abs(parencount), extra_closed_parenthesis[abs(parencount)]); //DEBUGOUTPUT
            if (weare__acomment == IN)
            {
                while (weare__acomment == IN) // this is for when we are still in a multiline comment as we enter a new line. find the end of the comment!
                {
                    if ((program[line][column] == '*') && (program[line][column + 1] == '/') && (areweinastring == OUT))
                    {
                        if (column < MAXCHARS - 3)
                        {
                            column = column + 2; // skip past the comment
                        }
                        weare__acomment = OUT; // mark us as OUT of a comment
                    }
                    else
                    {
                        if (column < MAXCHARS - 3)
                        {
                            column++; // keep moving forward
                        }
                        else
                        {
                            break;
                        }
                    }
                }
            }

            // count each character per line, iterate upwards
            if (((program[line][column] == '/') && (program[line][column + 1] == '/')) && ((weare__acomment == OUT)) && (areweinastring == OUT))
            {                                   // we're in a comment, ignore
                weare__asinglelinecomment = IN; // we are in a single line comment
                break;                          // go to the next line and go from there, nothing to see here
            }
            else if ((program[line][column] == '/') && (program[line][column + 1] == '*'))
            { // we're in a comment, skip over
                weare__acomment = IN;
                while (weare__acomment == IN)
                {
                    if ((program[line][column] == '*') && (program[line][column + 1] == '/'))
                    {
                        if (column < MAXCHARS - 2)
                        {
                            column = column + 2; // skip past the comment
                        }
                        weare__acomment = OUT; // mark us as OUT of a comment
                    }
                    else
                    {
                        if (column < MAXCHARS - 2)
                        {
                            column++; // keep moving forward
                        }
                        else
                        {
                            break;
                        }
                    }
                }
            }
            // when not in a comment or a string, we check if the character is a (, ), [, ], {, }, and keep count of it!
            if ((weare__acomment == OUT) && (areweinastring == OUT))
            {
                trackchars('(', ')', &parencount, &parenclosecount,
                           &maxparenthesis, &maxextraclosedparenthesis,
                           parenthesis, extra_closed_parenthesis,
                           location_parenopen_column, location_parenopen_line,
                           location_parenclose_column, location_parenclose_line);

                trackchars('{', '}', &curlycount, &curlyclosecount,
                           &maxcurly, &maxextraclosedcurlybraces,
                           curlybraces, extra_closed_curlybraces,
                           location_curlyopen_column, location_curlyopen_line,
                           location_curlyclose_column, location_curlyclose_line);

                trackchars('[', ']', &bracketcount, &bracketclosecount,
                           &maxbracket, &maxextraclosedbrackets,
                           brackets, extra_closed_brackets,
                           location_bracketopen_column, location_bracketopen_line,
                           location_bracketclose_column, location_bracketclose_line);

                trackquotes('\"', '\"', &quotecount, &quoteclosecount,
                            &maxquote, &maxextraclosedquotes,
                            quotes, extra_closed_quotes,
                            location_quoteopen_column, location_quoteopen_line,
                            location_quoteclose_column, location_quoteclose_line);
            }
        }
    }

    /*print character status at the end, along with a guess as to
    which line has mismatched characters most needing to be fixed.
    so the programmer can find it. for each entry in the array, we want to:

    1) check if it's a 0, meaning no fuckup.
    2) if it isn't 0, that means that set of characters is the one off balance.
    3) print what is near the opening/closing ones that are off balance,
    as well as the line number so the programmer knows where to look for their bug
*/

    printerrors(parenthesis, maxparenthesis,
                location_parenopen_line, location_parenopen_column,
                location_parenclose_line, location_parenclose_column,
                extra_closed_parenthesis, maxextraclosedparenthesis, '(', ')');

    printerrors(curlybraces, maxcurly,
                location_curlyopen_line, location_curlyopen_column,
                location_curlyclose_line, location_curlyclose_column,
                extra_closed_curlybraces, maxextraclosedcurlybraces, '{', '}');

    printerrors(brackets, maxbracket,
                location_bracketopen_line, location_bracketopen_column,
                location_bracketclose_line, location_bracketclose_column,
                extra_closed_brackets, maxextraclosedbrackets, '[', ']');

    printerrors(quotes, maxquote,
                location_quoteopen_line, location_quoteopen_column,
                location_quoteclose_line, location_quoteclose_column,
                extra_closed_quotes, maxextraclosedquotes, '\"', '\"');

    printf("\n\n");
}





/* Initializing variables we use for storage of status & 
tracking of location to 0. These can be found in definitions.h */

int linecountinput = 0;			// keep track of what line we are on in our string array while copying input file to it
int howlongisthisline[MAXLINES];		// for each line, how long is it

int line = 0;				// line stores what line we are on when iterating through the program
int column = 0;				// column stores what character we are on when iterating through the program
char program[MAXLINES][MAXCHARS];	// array of strings we will store the file with comments in

int areweinastring = OUT;		// are we in a string
int stringliteral = OUT;			// keep track of whether we're " " quotes
int charliteral = OUT;			// keep track of whether we're in ' ' quotes

int weare__acomment = OUT;		// keep track of whether we're in a comment
int weare__asinglelinecomment = OUT;	// keep track of whether we're on a single comment so we can reset it on the next line
int didweescapenewline = NO;		// keep track of whether someone put a \ escape character before hitting enter to escape a newline. 

/*the parenthesis[] array keeps track of whether parenthesis are balanced. let parenthesis[0] be the
first parenthesis. When an ( is found, parenthesis[0]++ will occur, which brings it to 1. If a ) shows up,
parenthesis[0]-- will happen, which brings it to a 0. If any of these is a 1, or a negative one,
it means that parenthesis is out of balance, and should be looked at. Same for arrays for other character types */

int parencount = 0;			// parencount stores which parenthesis we are on
int parenclosecount = 0;			// parencount stores which EXCESS closed parenthesis we are on
int maxparenthesis = 0;			// the highest number of parenthesis we opened as we count up
int maxextraclosedparenthesis = 0;	// the highest number of EXCESS closed parenthesis
int parenthesis[MAXCHARS] = {0};		// array for storing whether parenthesis are balanced - should ++ when there is an open parenthesis, and -- when there is a closed parenthesis
int extra_closed_parenthesis[MAXCHARS] = {0};   // array for storing how many extra closed parenthesis there are
int location_parenopen_column[MAXCHARS] = {0};  // array for storing column of opening parenthesis
int location_parenopen_line[MAXLINES] = {0};    // array for storing line of opening parenthesis
int location_parenclose_column[MAXCHARS] = {0}; // array for storing column of closing parenthesis
int location_parenclose_line[MAXLINES] = {0};   // array for storing column of closing parenthesis

int curlycount = 0;			// curlycount stores which curly braces we are on
int curlyclosecount = 0;			// curlyclosecount stores which EXCESS closed curlybraces we are on
int maxcurly = 0;				// the highest number of curly braces we opened as we count up
int maxextraclosedcurlybraces = 0;		// the highest number of EXCESS closed curly braces
int curlybraces[MAXCHARS] = {0};			// array for storing whether curly braces are balanced - should ++ when there is an open curly brace, and -- when there is a closed curlybrace
int extra_closed_curlybraces[MAXCHARS] = {0};	// array for storing how many extra closed curlybraces there are
int location_curlyopen_column[MAXCHARS] = {0};	// array for storing column of opening curly braces
int location_curlyopen_line[MAXLINES] = {0};	// array for storing line of opening curly braces
int location_curlyclose_column[MAXCHARS] = {0};	// array for storing column of closing curly braces
int location_curlyclose_line[MAXLINES] = {0};	// array for storing column of closing curly braces

int bracketcount = 0;				// bracketcount stores which brackets we are on
int bracketclosecount = 0;			// bracketclosecount stores which EXCESS closed brackets we are on
int maxbracket = 0;				// the highest number of brackets we opened as we count up
int maxextraclosedbrackets = 0;			// the highest number of EXCESS closed brackets
int brackets[MAXCHARS] = {0};			// array for storing whether brackets are balanced - should ++ when there is an open bracket brace, and -- when there is a closed bracketbrace
int extra_closed_brackets[MAXCHARS] = {0};	// array for storing how many extra closed brackets there are
int location_bracketopen_column[MAXCHARS] = {0};	// array for storing column of opening brackets
int location_bracketopen_line[MAXLINES] = {0};	// array for storing line of opening brackets
int location_bracketclose_column[MAXCHARS] = {0};// array for storing column of closing brackets
int location_bracketclose_line[MAXLINES] = {0};	// array for storing column of closing brackets

int quotecount = 0;				// quotecount stores which quotes we are on
int quoteclosecount = 0;				// quoteclosecount stores which EXCESS closed quotes we are on
int maxquote = 0;				// the highest number of quotes we opened as we count up
int maxextraclosedquotes = 0;			// the highest number of EXCESS closed quotes
int quotes[MAXCHARS] = {0};			// array for storing whether quotes are balanced - should ++ when there is an open quote, and -- when there is a closed quote
int extra_closed_quotes[MAXCHARS] = {0};		// array for storing how many extra closed quotes there are
int location_quoteopen_column[MAXCHARS] = {0};	// array for storing column of opening quotes
int location_quoteopen_line[MAXLINES] = {0};	// array for storing line of opening quotes
int location_quoteclose_column[MAXCHARS] = {0};	// array for storing column of closing quotes
int location_quoteclose_line[MAXLINES] = {0};	// array for storing column of closing quotes

