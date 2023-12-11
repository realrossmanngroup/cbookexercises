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
