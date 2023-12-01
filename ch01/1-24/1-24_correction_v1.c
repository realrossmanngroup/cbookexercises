#include <stdio.h>
#define MAXCHARS 1000
#define MAXLINES 1000
#define MAXFILENAME 100
#define IN 0                      /*are we in a comment?*/
#define OUT 1                     /*are we out of a comment?*/
#define YES 1                           
#define NO 0                            
int linecountinput = 0;           /* keep track of what line we are on in our string array while copying input file to it*/
char program[MAXLINES][MAXCHARS]; /*array of strings we will store the file with comments in*/
int stringliteral = OUT;          /*keep track of whether we're in a string literal*/
int charliteral = OUT;            /*keep track of whether we're in a char literal */
int weare__acomment = OUT;                      /*keep track of whether we're in a comment*/
int weare__asinglelinecomment = OUT;                    /*keep track of whether we're on a single comment so we can reset it on the next line*/
int didweescapenewline = NO;

// FUNCTION TO KEEP TRACK OF WHETHER WE ARE, OR ARE NOT, INSIDE OF A STRING, WHEN LOOKING FOR COMMENTS.

int stringinorout(int keeptrackofstring, int keeptrackofchar, char currentchar, char previouschar, int weare__acomment)
{
    /*handle trolls that put a \ at the end of the line.
    400 lines of code for every use case and it didn't handle a troll
    putting a \ at the end of a line, escaping the newline character and tricking my
    program into thinking we are automatically out of a string because we hit enter on a
    newline. */
    if ((currentchar == '\n') && (previouschar == '\\') && weare__acomment == OUT)
    {
        didweescapenewline = YES;
    }

    /* Handle strings in double quotes, only outside of comments */
    if (currentchar == '\"' && weare__acomment != IN && !(previouschar == '\\' && keeptrackofstring == IN))
    {
        keeptrackofstring = (keeptrackofstring == OUT) ? IN : OUT;
    }

    /* Handle characters in single quotes, only outside of comments */
    if (currentchar == '\'' && weare__acomment != IN && !(previouschar == '\\' && keeptrackofchar == IN))
    {
        keeptrackofchar = (keeptrackofchar == OUT) ? IN : OUT;
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
        for (int x = 0; x <= linelength; x++) /*copy the contents of each line of the file over to a line in our string array*/
        {
            program[linecountinput][x] = filetempcontents[x];
            wheretoplacenullterminator = x;
        }
        program[linecountinput][wheretoplacenullterminator] = '\0'; /*place null terminator at the end of each line*/

        if (linecountinput < MAXLINES - 1)
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
    int y = 0;                              /*y stores what line we are on when iterating through the progrma*/
    int x = 0;                              /*x stores what character we are on when iterating through the program*/
    int p = 0;                              /*p stores which parenthesis we are on*/
    int maxparenthesis = 0;                 /*the highest number of parenthesis we opened as we count up*/
    int minparenthesis = 0;                 /*the lowest amount of parenthesis we close as we count down*/
    int parenthesis[MAXCHARS];              /*array for storing whether parenthesis are balanced - should ++ when there is an open parenthesis, and -- when there is a closed parenthesis*/
    int extra_closed_parenthesis[MAXCHARS]; /*array for storing how many extra closed parenthesis there are*/

    /*the parenthesis[] array keeps track of whether parenthesis are balanced. let parenthesis[0] be the first parenthesis. When an (
        is found, parenthesis[0]++ will occur, which brings it to 1. If a ) is done, parenthesis[0]-- will happen, which brings it
        to a 0. If any of these is a 1, or a negative one, it means that parenthesis is out of balance, and should be looked at. */

    int location_popen_column[MAXCHARS]; /*array for storing column of opening parenthesis*/
    int location_popen_line[MAXLINES];   /*array for storing line of opening parenthesis*/

    int location_pclose_column[MAXCHARS]; /*array for storing column of closing parenthesis*/
    int location_pclose_line[MAXLINES];   /*array for storing column of closing parenthesis*/

    FILE *inputfile = openfile(); /*get input file*/
    filetoarray(inputfile);       /* copy contents of program to program[] char array */

    for (y = 0; y < linecountinput; y++)
    { /* count each line, iterate upwards */
        if (weare__asinglelinecomment == IN)
            ;
        {
            weare__asinglelinecomment = OUT;
        }
        for (x = 0; x < MAXCHARS - 2; x++)
        {
            if (x > 0)
            {
                stringliteral = stringinorout(stringliteral, charliteral, program[y][x], program[y][x - 1], weare__acomment); // Keep track of whether we're in a string literal
            printf("DEBUG line %d: program[%d][%d] is %c, stringliteral is %d, charliteral is %d, comment is %d, singlelinecomment is %d\n", __LINE__, y, x, program[y][x],stringliteral, charliteral, weare__acomment, weare__asinglelinecomment);                                                                                 /*DEBUGOUTPUT*/

            }

            /*count each character per line, iterate upwards*/
            if (((program[y][x] == '/') && (program[y][x + 1] == '/')) && weare__acomment == OUT)
            {             /*we're in a comment, ignore*/
                weare__asinglelinecomment = IN; /*we are in a single line comment*/
                break;    /*go to the next line and go from there, nothing to see here*/
            }
            else if ((program[y][x] == '/') && (program[y][x + 1] == '*')) /*we're in a comment, skip over*/
                weare__acomment = IN;
            while (weare__acomment == IN)
            {
                if ((program[y][x] == '*') && (program[y][x + 1] == '/'))
                {
                    if (x < MAXCHARS - 2)
                    {
                        x = x + 2; /*skip past the comment*/
                    }
                    weare__acomment = OUT; /*mark us as OUT of a comment*/
                }
                else
                {
                    if (x < MAXCHARS - 2)
                    {
                        x++; /*keep moving forward*/
                    }
                    else
                    {
                        break;
                    }
                }
            }

            while ((weare__acomment == OUT) && (stringliteral == OUT))
            {
                if (program[y][x] == '(') /*if we have an open parenthesis*/
                {
                    parenthesis[p]++;       /*count up in parenthesis for the number parenthesis we are on*/
                    if (maxparenthesis < p) /*keep track of the highest number parenthesis ever hit so we know how far to print at the end*/
                    {
                        maxparenthesis = p;
                    }
                    location_popen_column[p] = x;                                                                                                                                                                                         /*register that the nth parenthesis' that's opened column location is x*/
                    location_popen_line[p] = y;                                                                                                                                                                                           /*register that the nth parenthesis' line location is y */
                    printf("DEBUG line %d:%c is program[%d][%d]\n", __LINE__, program[y][x], y, x);                                                                                                                                       /*debugoutput*/
                    printf("DEBUG line %d:%c is program[location_popen_line[%d]][location_popen_column[%d]] %c is program[%d][%d] \n\n", __LINE__, program[location_popen_line[p]][location_popen_column[p]], p, p, program[y][x], y, x); /*debugoutput*/
                    p++;                                                                                                                                                                                                                  /*iterate p up so that the next time we see an open parenthesis, it is seen as the 2nd, 3rd, 4th, etc.*/
                    break;
                }
                else if (program[y][x] == ')') /*if we have a closed parenthesis*/
                {

                    p--; /*iterate p down so that we are closing the last parenthesis we opened. */

                     if (p < 0)
                    {
                        extra_closed_parenthesis[(-p)]++;
                    }
                    else
                    {
                        parenthesis[p]--; /*count down in parenthesis for the number parenthesis we are on*/
                    }

                    location_pclose_column[p] = x; /*register that the nth parenthesis' that's closed column location is x*/
                    location_pclose_line[p] = y;   /*register that the nth parenthesis' that's closed location is y */

                    printf("DEBUG line %d:  %d is y, %d is x, %d is p, %d is location_pclose_line[%d]\n\n", __LINE__, y, x, p, location_pclose_line[p], p);                                                                                 /*DEBUGOUTPUT*/
                    printf("DEBUG line %d:%c is program[%d][%d]\n", __LINE__, program[y][x], y, x);                                                                                                                                       /*debugoutput*/
                    printf("DEBUG line %d:%c is program[location_pclose_line[%d]][location_pclose_column[%d]] %c is program[%d][%d] \n\n", __LINE__, program[location_pclose_line[p]][location_pclose_column[p]], p, p, program[y][x], y, x); /*debugoutput*/

                   
                    break;
                }
                else
                {
                    break; /*if we have none of the above, get out of here and move onto the next character*/
                }
            }
        }
    }

    /*print parenthesis status at the end, along with some of what
     was on the line with mismatched parenthesis so that a user
     can find it more quickly*/

    /*
    for each parenthesis , we want to
    1) check if it's a 0, meaning no fuckup.
    2) if 0 and not a fuckup, print the number of the parenthesis(the x in parenthesis[x] is how many])
    3) print everything around it.
    */

    for (int whichp = 0; whichp <= maxparenthesis; whichp++)
    {
        if (parenthesis[whichp] != 0)
        {
            printf("line with mismatched parenthesis is probably the %dth parenthesis on line %d: issue includes this text on line %d: ", whichp + 1, location_popen_line[whichp] + 1, location_popen_line[whichp] + 1);
        }
        { /*location_popen_column[whichp] = what you need to iterate location_popen_line[whichp] = the line you are now on */ /* program[location_popen_line[whichp]][location_popen_column[whichp]] = the character where you are right now*/
            for (int charsforcontext = (location_popen_column[whichp] >= 10 ? location_popen_column[whichp] - 10 : 0); charsforcontext < (location_popen_column[whichp] <= MAXCHARS - 11 ? location_popen_column[whichp] + 10 : MAXCHARS - 1); charsforcontext++)
            {
                printf("%c",program[location_popen_line[whichp]][charsforcontext]);
//debug printf("%c is program[%d][%d] %d is y\n\n", program[location_popen_line[whichp]][charsforcontext], location_popen_line[whichp], charsforcontext, charsforcontext);
            }
            printf("\n"); /*make it neat*/
        }
    }
printf("\n\n");}