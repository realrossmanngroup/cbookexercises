#include <stdio.h>
#include <stdlib.h>

#define MAXCHARS 1000
#define MAXLINES 1000
#define MAXFILENAME 100
#define IN 0  /*are we in a comment?*/
#define OUT 1 /*are we out of a commlocation_parenclose_columnent?*/
#define YES 1
#define NO 0

int linecountinput = 0;          /* keep track of what line we are on in our string array while copying input file to it*/
int howlongisthisline[MAXLINES]; /*for each line, how long is it*/

int line = 0;                     /* line stores what line we are on when iterating through the program*/
int column = 0;                   /* column stores what character we are on when iterating through the program*/
char program[MAXLINES][MAXCHARS]; /*array of strings we will store the file with comments in*/

int areweinastring = OUT; /*are we in a string*/
int stringliteral = OUT;  /*keep track of whether we're " " quotes*/
int charliteral = OUT;    /*keep track of whether we're in ' ' quotes */

int weare__acomment = OUT;           /*keep track of whether we're in a comment*/
int weare__asinglelinecomment = OUT; /*keep track of whether we're on a single comment so we can reset it on the next line*/
int didweescapenewline = NO;

/*theparenthesis_open_status] array keeps track of whether parenthesis are balanced. letparenthesis_open_status0] be the
first parenthesis. When an ( is found,parenthesis_open_status0]++ will occur, which brings it to 1. If a ) shows up,
parenthesis[0]-- will happen, which brings it to a 0. If any of these is a 1, or a negative one,
it means that parenthesis is out of balance, and should be looked at. Same for arrays for other character types */

int paren_open_count = 0;                       /*paren_open_count stores which parenthesis we are on*/
int paren_close_count = 0;                      /*paren_open_count stores which EXCESS closed parenthesis we are on*/
int max_open_parenthesis = 0;                   /*the highest number of parenthesis we opened as we count up*/
int max_closed_parenthesis = 0;                 /*the highest number of EXCESS closed parenthesis */
int parenthesis_open_status[MAXCHARS] = {0};    /*array for storing whether parenthesis are balanced - should ++ when there is an open parenthesis, and -- when there is a closed parenthesis*/
int parenthesis_closed_status[MAXCHARS] = {0};  /*array for storing how many extra closed parenthesis there are*/
int location_parenopen_line[MAXLINES] = {0};    /*array for storing line of opening parenthesis*/
int location_parenopen_column[MAXCHARS] = {0};  /*array for storing column of opening parenthesis*/
int location_parenclose_line[MAXLINES] = {0};   /*array for storing column of closing parenthesis*/
int location_parenclose_column[MAXCHARS] = {0}; /*array for storing column of closing parenthesis*/
int parenthesis_balanced = YES;

int curlycount = 0; /*curlycount stores which curly braces we are on*/
int curlyclosecount = 0;
int maxcurly = 0;                               /*the highest number of curly braces we opened as we count up*/
int curlybraces[MAXCHARS] = {0};                /*array for storing whether curly braces are balanced - should ++ when there is an open curly brace, and -- when there is a closed curlybrace*/
int extra_closed_curlybraces[MAXCHARS] = {0};   /*array for storing how many extra closed curly braces there are*/
int location_curlyopen_column[MAXCHARS] = {0};  /*array for storing column of opening curly braces*/
int location_curlyopen_line[MAXLINES] = {0};    /*array for storing line of opening curly braces*/
int location_curlyclose_column[MAXCHARS] = {0}; /*array for storing column of closing curly braces*/
int location_curlyclose_line[MAXLINES] = {0};   /*array for storing column of closing curly braces*/

int bracketcount = 0; /*bracketcount stores which brackets we are on*/
int bracketclosecount = 0;
int maxbracket = 0;                               /*the highest number of brackets we opened as we count up*/
int brackets[MAXCHARS] = {0};                     /*array for storing whether brackets are balanced - should ++ when there is an open bracket brace, and -- when there is a closed bracketbrace*/
int extra_closed_brackets[MAXCHARS] = {0};        /*array for storing how many extra closed brackets there are*/
int location_bracketopen_column[MAXCHARS] = {0};  /*array for storing column of opening brackets*/
int location_bracketopen_line[MAXLINES] = {0};    /*array for storing line of opening brackets*/
int location_bracketclose_column[MAXCHARS] = {0}; /*array for storing column of closing brackets*/
int location_bracketclose_line[MAXLINES] = {0};   /*array for storing column of closing brackets*/

int quotecount = 0; /*quotecount stores which quotes we are on*/
int quoteclosecount = 0;
int maxquote = 0;                               /*the highest number of quotes we opened as we count up*/
int quotes[MAXCHARS] = {0};                     /*array for storing whether quotes are balanced - should ++ when there is an open quote, and -- when there is a closed quote*/
int extra_closed_quotes[MAXCHARS] = {0};        /*array for storing how many extra closed quotes there are*/
int location_quoteopen_column[MAXCHARS] = {0};  /*array for storing column of opening quotes*/
int location_quoteopen_line[MAXLINES] = {0};    /*array for storing line of opening quotes*/
int location_quoteclose_column[MAXCHARS] = {0}; /*array for storing column of closing quotes*/
int location_quoteclose_line[MAXLINES] = {0};   /*array for storing column of closing quotes*/

// FUNCTION FOR KEEPING TRACK OF SOMETHING
// COUNTING & KEEPING TRACK OF EXCESS OPENING CHARACTERS
void trackopenedchars(char openchar, char closechar,
                      int *opencounter, int *closecounter,
                      int *max_open, int *max_close, int openstatus[],
                      int openline[], int opencolumn[],
                      int closestatus[], int *BALANCED)
{
    printf("debug line %d before if in function, program[%d][%d] is %c \n", __LINE__, line, column, program[line][column]);
    if (program[line][column] == openchar) /*if we have an open character*/
    {
        openstatus[*opencounter]++;   /*count up in the array for that character, the number of open characters we're on. */
        if (*max_open < *opencounter) /*keep track of the highest number parenthesis ever hit so we know how far to print at the end*/
        {
            *max_open = *opencounter;
        }
        opencolumn[*opencounter] = column; /*store the column coordinate of the nth opened char in the location array*/
        openline[*opencounter] = line;     /*store the line coordinate of the nth opened char in the location array*/
        printf("DEBUG %d OPEN %c FOUND: *opencounter is %d, openstatus[%d] is %d, program[%d][%d] is %c \n\n",
               __LINE__, openchar, *opencounter, *opencounter, openstatus[*opencounter], openline[*opencounter], opencolumn[*opencounter],
               program[openline[*opencounter]][opencolumn[*opencounter]]);
        (*opencounter)++; /*iterate p up so that the next time we see an open parenthesis, it is seen as the 2nd, 3rd, 4th, etc.*/
        printf("DEBUG %d did *opencounter go up after detecting an opening parenthesis? *opencounter is %d\n\n",
               __LINE__, *opencounter);
    }
    else if (program[line][column] == closechar) /*if we have a closed char */
    {
        if (!(*opencounter < 0))
        {
            *BALANCED = YES;
            (*opencounter)--; /*iterate *opencounter down so that we are closing the last char we opened. */

            openstatus[*opencounter]--;
        } /*count down in the tracking array for the number char we are on*/
        else
        {
            *BALANCED = NO;
        }
    }

    else
    {
        printf("debug line %d ending else in function\n", __LINE__);
    }
}

// COUNTING & KEEPING TRACK OF EXCESS CLOSING CHARACTERS

void trackclosedchars(char openchar, char closechar, int *opencounter, int *closecounter,
                      int *max_close, int closestatus[],
                      int closeline[], int closecolumn[], int *BALANCED)
{
    printf("debug line %d before if in function, program[%d][%d] is %c \n", __LINE__, line, column, program[line][column]);
    if ((program[line][column] == closechar) && (*BALANCED == NO)) /*if we have a closed character AND our parenthesis aren't balanced*/
    {
        closestatus[*closecounter]++;   /*count up in the array for that character, the number of open characters we're on. */
        if (*max_close < *closecounter) /*keep track of the highest number parenthesis ever hit so we know how far to print at the end*/
        {
            *max_close = *closecounter;
        }
        closecolumn[*closecounter] = column; /*store the column coordinate of the nth opened char in the location array*/
        closeline[*closecounter] = line;     /*store the line coordinate of the nth opened char in the location array*/
        printf("DEBUG %d CLOSE %c FOUND: *closecounter is %d, closestatus[%d] is %d, program[%d][%d] is %c \n\n",
               __LINE__, closechar, *closecounter, *closecounter, closestatus[*closecounter], closeline[*closecounter], closecolumn[*closecounter],
               program[closeline[*closecounter]][closecolumn[*closecounter]]);
        (*closecounter)++; /*iterate closecounter up so that the next time we see a closechar, it is seen as the 2nd, 3rd, 4th, etc.*/
        printf("DEBUG %d did *closecounter go up after detecting a closechar? *closecounter is %d\n\n",
               __LINE__, *closecounter);
    }
    /* else if ((program[line][column] == openchar) && !(*opencounter < 0)) // if we have a OPEN char and we do not have an excess of open chars
     {
         (*closecounter)--; //iterate *closecounter down so that we are closing the last char we opened.

         if (!(*closecounter < 0))
         {
             closestatus[*closecounter]--; // count down in the tracking array for the number char we are on
         }
     } */
    else
    {
        printf("debug line %d ending else in function\n", __LINE__);
    }
}

// FUNCTION TO PRINT THE LOCATION OF THE ERRORS IN SYNTAX OF CODE AFTER FINDING THEM

void printerrors(int openstatus[], int max_open, int openline[], int opencolumn[],
                 int closeline[], int closecolumn[], int closestatus[], int max_close)
{

    for (int whichp = 0; whichp <= max_open; whichp++)
    {
        if (openstatus[whichp] != 0)
        {
            printf("line with mismatched thing is probably the %dth thing on line %d: \n", whichp + 1, openline[whichp] + 1);
            printf("%d debugoutput openstatus[%d] is %d\n", __LINE__, whichp, openstatus[whichp]);
            /*location_parenopen_column[whichp] = what you need to iterate location_parenopen_line[whichp] = the line you are now on */ /* program[location_parenopen_line[whichp]][location_parenopen_column[whichp]] = the character where you are right now*/
            for (int charsforcontext = (opencolumn[whichp] >= 10 ? opencolumn[whichp] - 10 : 0); charsforcontext < (opencolumn[whichp] <= MAXCHARS - 11 ? opencolumn[whichp] + 10 : MAXCHARS - 1); charsforcontext++)
            {
                printf("%c", program[openline[whichp]][charsforcontext]);
            }
            printf("\n"); /*make it neat*/
        }
    }
    printf("\n\n");

    for (int whichp = 0; whichp <= max_close; whichp++)
    {
        if (closestatus[whichp] != 0)
        {
            printf("line with extra closed thing is probably the %dth thing on line %d \n", whichp + 1, closeline[whichp] + 1);
            printf("%d DEBUGOUTPUT closestatus[%d] is %d\n", __LINE__, whichp, closestatus[whichp]);
            /*location_parenopen_column[whichp] = what you need to iterate location_parenopen_line[whichp] = the line you are now on */ /* program[location_parenopen_line[whichp]][location_parenopen_column[whichp]] = the character where you are right now*/
            for (int charsforcontext = (closecolumn[whichp] >= 10 ? closecolumn[whichp] - 10 : 0); charsforcontext < (closecolumn[whichp] <= MAXCHARS - 11 ? closecolumn[whichp] + 10 : MAXCHARS - 1); charsforcontext++)
            {
                printf("%c", program[closeline[whichp]][charsforcontext]);
            }
            printf("\n"); /*make it neat*/
        }
    }
}

// FUNCTION TO KEEP TRACK OF WHETHER WE ARE, OR ARE NOT, INSIDE OF A STRING, WHEN LOOKING FOR COMMENTS.

int stringinorout((((((((((((((((int keeptrackofstring, int keeptrackofchar, char currentchar, char previouschar, int comment)
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

    if (((currentchar == '\n') && (previouschar == '\\') && comment == OUT)
    {
        escaped = OUT;
        didweescapenewline = YES;
    }

    /* Handle strings in double quotes, only outside of comments */
    if (currentchar == '\"' && !(comment == IN) && !(keeptrackofchar == IN) && !(escaped == YES)))))))))
    {
        keeptrackofstring = (keeptrackofstring == OUT) ? IN : OUT;
        stringliteral = keeptrackofstring;
    }

    /* Handle characters in single quotes, only outside of comments */
    if (((currentchar == '\'' && !(comment == IN) && !(keeptrackofstring == IN) && !(escaped == YES))
    {
        keeptrackofchar = (keeptrackofchar == OUT) ? IN : OUT;
        charliteral = keeptrackofchar;
    }

    /* Return IN if inside a string or char literal, OUT otherwise */
    return (keeptrackofstring == IN || keeptrackofchar == IN) ? IN : OUT;
}

// FUNCTION TO OPEN A FILE FOR PROCESSING & REMOVING COMMENTS FROM

FILE *openfile()
{
    char inputfilename[MAXFILENAME]; /* this will be where we store the name of our input file */
    int i = 0;                       /* use for looping to collect input from user */
    // ASK THE USER WHAT FILE THEY WANT TO WORK ON
    printf("What is the name of the INPUT file you wish to check for imbalanced parenthesis?\n\n");
    while ((i < MAXFILENAME - 1) && (inputfilename[i] = getc(stdin)) != EOF)
    { /* have user type in input filename */
        if (inputfilename[i] != '\n')
        { /*take user input into filename before they hit enter*/
            i++;
        }
        else
        {
            inputfilename[i] = '\0'; /* null terminate filename character array once user hits enter */
            break;                   /*end acceptance of while loop that accepts user input into filename[] once they hit enter*/
        }
    }

    // OPEN THE FILE THE USER HAS CHOSEN TO WORK ON

    FILE *openedfile = fopen(inputfilename, "r");                        /*open file specified above and assign to *program pointer */
    printf("The filename you want me to open is %s\n\n", inputfilename); /*Confirm I am opening the correct file*/

    if (openedfile == NULL)
    { /*error handling if it cannot open the file*/
        perror("Error opening file");
    }
    else
    {
        printf("%p is open, that's filename: %s\n\n", (void *)openedfile, inputfilename); /*tell me the file as a memory address & filename if it did open*/
        return openedfile;                                                                /*return the program to the function so that we have an open file in our program after using this*/
    }
}

// FUNCTION FOR CREATING A FILE TO SAVE THE PROCESSED, UNCOMMENTED CODE TO

FILE *savefile()
{

    char outputfilename[MAXFILENAME]; /* this will be where we store the name of our output file */
    int i = 0;                        /* use for looping to collect input from user */
    // ASK THE USER WHAT FILE THEY WANT TO SAVE TO
    printf("What is the name of the OUTPUT file you wish to save your uncommented code to in this directory?\n\n");
    while ((i < MAXFILENAME - 1) && (outputfilename[i] = getc(stdin)) != EOF)
    { /* have user type in filename to save to */
        if (outputfilename[i] != '\n')
        { /*take user input into filename before they hit enter*/
            i++;
        }
        else
        {
            outputfilename[i] = '\0'; /* null terminate filename character array once user hits enter */
            break;                    /*end acceptance of while loop that saves program output*/
        }
    }

    // If file is good, tell the user & return it to the function call

    FILE *outputfile = fopen(outputfilename, "w");                              /*open file specified above and assign to *program pointer */
    printf("The filename you want me to save to is is %s\n\n", outputfilename); /*Confirm I am opening the correct file*/

    if (outputfile == NULL)
    { /*error handling if it cannot open the file*/
        perror("Error creating file");
    }
    else
    {
        printf("%p is open, that's filename: %s and is ready for writing\n\n", (void *)outputfile, outputfilename); /*tell me the file as a memory address & filename if it did open*/
        return outputfile;                                                                                          /*return the program to the function so that we have an open file in our program after using this*/
    }
}

// FUNCTION FOR COPYING PROGRAM FROM FILE TO program[] ARRAY SO WE CAN PROCESS IT WITHIN THIS PROGRAM

void filetoarray(FILE *file)
{
    char array[MAXLINES][MAXCHARS];     /* array we will store each line of file to*/
    int linelength = 0;                 /*how long each line I am taking from my file is*/
    int wheretoplacenullterminator = 0; /*where to place null terminator as we copy each line*/
    char filetempcontents[MAXCHARS];    /*this is where we store the text of our file as we read it line by line temporarily */

    while (fgets(filetempcontents, MAXCHARS - 2, file) != NULL)
    {
        linelength = 0;
        while (filetempcontents[linelength] != '\0')
        {
            if (linelength < MAXLINES - 2)
            {
                linelength++;
            }
        }
        for (int charposition = 0; charposition <= linelength; charposition++) /*copy the contents of each line of the file over to a line in our string array*/
        {
            program[linecountinput][charposition] = filetempcontents[charposition];
            wheretoplacenullterminator = charposition;
        }
        program[linecountinput][wheretoplacenullterminator] = '\0';         /*place null terminator at the end of each line*/
        howlongisthisline[linecountinput] = wheretoplacenullterminator + 1; /*keep track of the length of each line*/

        if (linecountinput < MAXLINES - 2)
        {
            linecountinput++; /* each time the while loop loops we're on a new line, so iterate the line we're on in the string array */
        }
        else
        {
            break;
        }
    }
}

void main()
{
    FILE *inputfile = openfile(); /*get input file*/
    filetoarray(inputfile);       /* copy contents of program to program[] char array */

    // WE BEGIN LOOKING THROUGH OUR INPUT FILE BELOW

    for (line = 0; line < linecountinput; line++) /* go through each line of the program and iterate upwards once at the end */
    {
        if ((weare__asinglelinecomment == IN) && (didweescapenewline == NO)) // singleline comments do not persist to the next line. Once we're on a new line,

        {
            weare__asinglelinecomment = OUT;
        }
        for (column = 0; column < howlongisthisline[line]; column++)
        {

            areweinastring = stringinorout(stringliteral, charliteral, program[line][column], program[line][column - 1], weare__acomment);                                                                                                                                                                 // Keep track of whether we're in a string literal
            printf("DEBUG line %d: program[%d][%d] is %c, areweinastring is %d, stringliteral is %d, charliteral is %d, comment is %d, singlelinecomment is %d\n", __LINE__, line, column, program[line][column], areweinastring, stringliteral, charliteral, weare__acomment, weare__asinglelinecomment); /*DEBUGOUTPUT*/
            printf("CONTINUED: paren_open_count/opencounter is %d, paren_close_count/closecounter is %d, parenthesis_open_status[%d] is %d, parenthesis_close_status[%d] is %d\n", paren_open_count, paren_close_count, paren_open_count, parenthesis_open_status[paren_open_count], paren_close_count, parenthesis_closed_status[paren_close_count]);

            if (weare__acomment == IN)))
            {
                while (weare__acomment == IN) /*this is for when we are still in a multiline comment as we enter a new line. find the end of the comment!*/
                {
                    if ((program[line][column] == '*') && (program[line][column + 1] == '/') && (areweinastring == OUT))
                    {
                        if (column < MAXCHARS - 3)
                        {
                            column = column + 2; /*skip past the comment*/
                        }
                        weare__acomment = OUT; /*mark us as OUT of a comment*/
                    }
                    else
                    {
                        if (column < MAXCHARS - 3)
                        {
                            column++; /*keep moving forward*/
                        }
                        else
                        {
                            break;
                        }
                    }
                }
            }

            /*count each character per line, iterate upwards*/
            if (((program[line][column] == '/') && (program[line][column + 1] == '/')) && ((weare__acomment == OUT)) && (areweinastring == OUT))
            {                                   /*we're in a comment, ignore*/
                weare__asinglelinecomment = IN; /*we are in a single line comment*/
                break;                          /*go to the next line and go from there, nothing to see here*/
            }
            else if ((program[line][column] == '/') && (program[line][column + 1] == '*'))
            { /*we're in a comment, skip over*/
                weare__acomment = IN;
                while (weare__acomment == IN)
                {
                    if ((program[line][column] == '*') && (program[line][column + 1] == '/'))
                    {
                        if (column < MAXCHARS - 2)
                        {
                            column = column + 2; /*skip past the comment*/
                        }
                        weare__acomment = OUT; /*mark us as OUT of a comment*/
                    }
                    else
                    {
                        if (column < MAXCHARS - 2)
                        {
                            column++; /*keep moving forward*/
                        }
                        else
                        {
                            break;
                        }
                    }
                }
            }
            /* when not in a comment or a string, we check if the character is a (, ), [, ], {, }, and keep count of it!*/
            if ((weare__acomment == OUT) && (areweinastring == OUT))))
            {

                // track open parenthesis & count excess
                trackopenedchars('(', ')',
                                 &paren_open_count, &paren_close_count,
                                 &max_open_parenthesis, &max_closed_parenthesis, parenthesis_open_status,
                                 location_parenopen_line, location_parenopen_column,
                                 parenthesis_closed_status, &parenthesis_balanced);

                // track closed parenthesis & count excess
                trackclosedchars('(', ')', &paren_open_count, &paren_close_count,
                                 &max_closed_parenthesis, parenthesis_closed_status,
                                 location_parenclose_line, location_parenclose_column, &parenthesis_balanced);
            }
        }
    }

    printerrors(parenthesis_open_status, max_open_parenthesis, location_parenopen_line, location_parenopen_column,
                location_parenclose_line, location_parenclose_column, parenthesis_closed_status, max_closed_parenthesis);

    printf("\n\n");
}
