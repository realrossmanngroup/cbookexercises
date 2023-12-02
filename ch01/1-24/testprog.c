// PROGRAM TO REMOVE SINGLE & MULTI LINE COMMENTS FROM A C PROGRAM, WITHOUT MESSING UP FORMATTING

#include <stdio.h>
#include <stdlib.h>
#define MAXLINELENGTH 1000
#define MAXLINES 5000
#define MAXFILENAME 100
#define IN 0                             /*are we in a comment?*/
#define OUT 1                            /*are we out of a comment?*/
#define YES 1                            /*single line comment found?*/
#define NO 0                             /*single line comment not found*/
#define FALSE 0                          /*multiline comment has not ended*/
#define TRUE 1                           /*multiline comment has ended*/
int weare__acomment = OUT;                             /*used to keep track of where we are - IN or OUT of a comment? Start out of a comment */
int x = 0;                               /*use in for loop to count up in the nocomments array. this goes up when there are no comments */
int y = 0;                               /*use in for loop to count up in the comments array - this goes up when there are no comments, and when there are comments*/
int result = 10 / 2;                     /*testing if my program deletes a single slash when it shouldn't */
int didweescapenewline = NO;             /*If you escape the newline character inside of a string by typing a \ at the end of the line, we're gonna catch you*/
int linecountinput = 0;                  /* keep track of what line we are on in our string array while copying input file to it*/
int linecountoutput = 0;                 /*keep track of linecount of processed array with no comments*/
char comment[MAXLINES][MAXLINELENGTH];   /*array of strings we will store the file with comments in*/
char nocomment[MAXLINES][MAXLINELENGTH]; /*this is where I am storing the uncommented line after processing*/

// FUNCTION TO KEEP TRACK OF WHETHER WE ARE, OR ARE NOT, INSIDE OF A STRING, WHEN LOOKING FOR COMMENTS.

int stringinorout(int keeptrackofstring, int keeptrackofchar, char currentchar, char previouschar, int y)
{
    /*handle trolls that put a \ at the end of the line.
    400 lines of code for every use case and it didn't handle a troll
    putting a \ at the end of a line, escaping the newline character and tricking my 
    program into thinking we are automatically out of a string because we hit enter on a 
    newline. */

    /* a little bit of 
    ( (((( trolling 
*/
    if ((currentchar == '\n') && (previouschar == '\\') && weare__acomment == OUT)
    {
        didweescapenewline = YES;
    }

    /* Handle strings in double quotes, only outide of comments*/
    if (currentchar == '\"' && (y == 0 || previouschar != '\\' || weare__acomment != IN))
    {
        keeptrackofstring = (keeptrackofstring == OUT) ? IN : OUT;
    }

    /* Handle characters in single quotes, only outside of comments */
    if (currentchar == '\'' && ((y == 0 || previouschar != '\\') && (weare__acomment != IN)))
    {
        keeptrackofchar = (keeptrackofchar == OUT) ? IN : OUT;
    }

    /*so I don't get trolled by backslashes, singlequotes, or other garbage like I have been for the past 5 hours*/
    if (currentchar == '\\' && (y > 0 && (previouschar == '\\' || previouschar == '\'')))
    {
        y++; // Increment y to skip the next character
    }

    /* Return IN if inside a string or char literal, OUT otherwise */
    if (keeptrackofstring == IN || keeptrackofchar == IN)
    {
        return IN;
    }
    else
    {
        return OUT;
    }
}

// FUNCTION TO OPEN A FILE FOR PROCESSING & REMOVING COMMENTS FROM

FILE *openfile()
{

    char inputfilename[MAXFILENAME]; /* this will be where we store the name of our input file */
    int i = 0;                       /* use for looping to collect input from user */
    // ASK THE USER WHAT FILE THEY WANT TO WORK ON
    printf("What is the name of the INPUT file you wish to remove comments from in this directory?\n\n");
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

    FILE *program = fopen(inputfilename, "r");                           /*open file specified above and assign to *program pointer */
    printf("The filename you want me to open is %s\n\n", inputfilename); /*Confirm I am opening the correct file*/

    if (program == NULL)
    { /*error handling if it cannot open the file*/
        perror("Error opening file");
        fclose(program);
    } 
    else
    {
        printf("%p is open, that's filename: %s\n\n", (void *)program, inputfilename); /*tell me the file as a memory address & filename if it did open*/
        return program;                                                                /*return the program to the function so that we have an open file in our program after using this*/
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
        fclose(outputfile);
    }
    else
    {
        printf("%p is open, that's filename: %s and is ready for writing\n\n", (void *)outputfile, outputfilename); /*tell me the file as a memory address & filename if it did open*/
        return outputfile;                                                                                          /*return the program to the function so that we have an open file in our program after using this*/
    }
}

// FUNCTION FOR COPYING PROGRAM FROM FILE TO comment[] ARRAY SO WE CAN PROCESS IT WITHIN THIS PROGRAM

char filetoarray(FILE *file)
{
    char array[MAXLINES][MAXLINELENGTH]; /* array we will store each line of file to*/
    int linelength = 0;                  /*how long each line I am taking from my file is*/

    int wheretoplacenullterminator = 0; /*where to place null terminator as we copy each line*/

    char filetempcontents[MAXLINELENGTH]; /*this is where we store the text of our file as we read it line by line temporarily */

    while (fgets(filetempcontents, MAXLINELENGTH, file) != NULL)
    {
        linelength = 0;
        while (filetempcontents[linelength] != '\0')
        {
            linelength++;
        }
        for (int x = 0; x <= linelength; x++) /*copy the contents of each line of the file over to a line in our string array*/
        {
            comment[linecountinput][x] = filetempcontents[x];
            wheretoplacenullterminator = x;
        }
        comment[linecountinput][wheretoplacenullterminator] = '\0'; /*place null terminator at the end of each line*/

        if (linecountinput < MAXLINES)
        {
            linecountinput++;
        }
        else
        {
            exit(1);
        } /* each time the while loop loops we're on a new line, so iterate the line we're on in the string array */
    }
}

// PRINT A CHARACTER ARRAY IN FULL
void printarray(char array[MAXLINES][MAXLINELENGTH], int end)
{
    for (int x = 0; x <= end; x++)
    { // PRINT FROM LINE 0 TO end WHICH REPRESENTS THE NUMBER OF LINES IN THE PROGRAM
        printf("%s", comment[x]);
    }
}

void main()
{
    int j = 0;                           /*use for looping to spit file being read into string array*/
    int stringliteral = OUT;             /*used to keep track of where we are, IN or OUT of a string literal. ex. printf("this is NOT a comment // because it is inside a string") */
    int charliteral = OUT;               /*because ' and " are not the same, but can mess with my strings anyway. "*/
    int singlelinecomment = NO;          /*bool to tell when we're in a single line comment, initialize at 0*/
    int multilinecommentend = FALSE;     /*bool to go back to the top of the for loop & keep copying stuff when a multiline comment ends and there is more data to process on that line*/
    FILE *inputfile = openfile();        /*get input file*/
    filetoarray(inputfile);              /* copy contents of program to comment[] char array */
    printarray(comment, linecountinput); /* print the input file to the screen so the user can see what we will be processing*/

    /* Find & skip over comments in comment[] and move the output over to nocomment[]
    keeping in mind multiline comments, single line comments, string literals, & other fringe cases
    a represents the line we are on. y represents where we are in the nocomment[] character array,
    x represents where we are in the comment[] character array. When we are not in a comment,
    we will copy comment[a][y] over to comment[a][x]. When we find a comment, we will keep
    iterating up y which represents where we are in the comment[] array, but not iterate x which
    represents where we are in the comment[] array - effectively skipping over comments. */

    for (int a = 0; a <= linecountinput; a++, linecountoutput++, x = 0, y = 0)
    {
        if (didweescapenewline == NO)
        {
            stringliteral = OUT; /*each time we start a new line, assume we are not inside a string literal. I'm assuming there's no way
                                to put a string across multiple lines. If there is, I am going to shoot myself. */
        }
        else
        {
            didweescapenewline = NO;
        }

        if (singlelinecomment == YES)
        {
            singlelinecomment = NO;
            continue;
        }
        if (weare__acomment == OUT)
        { // If we out of a comment, do the following
            // If we find a "//" , go to the next line without copying further.
            // If we find a "/*", keep moving to the next character without copying anything, until a "*/" is found

            while ((comment[a][y] != '\0') && (y < MAXLINELENGTH - 1)) // Keep going through the line until we get to a null terminator or the end of the line
            {
                stringliteral = stringinorout(stringliteral, charliteral, comment[a][y], comment[a][y - 1], y); // Keep track of whether we're in a string literal
                if (((comment[a][y] == '/') && (comment[a][y + 1] == '/')) && (stringliteral == OUT))           /*if we see a SINGLE line comment OUTSIDE OF A STRING*/
                {
                    printf("DEBUGOUTPUT line number: %d stringliteral is %d I DETECTED A SINGLE LINE COMMENT AT comment[%d][%d] which is %c (should be a slash) and comment[%d][%d] which is %c (should be a slash)! weare__acomment is%d\n", __LINE__, stringliteral, a, y, comment[a][y], a, y + 1, comment[a][y + 1], weare__acomment); /*debugoutput*/
                    nocomment[a][x] = '\n';                                                                                                                                                                                                                                                                     /*replace the single line comment with a newline character so the formatting isn't a mess*/
                    nocomment[a][x + 1] = '\0';                                                                                                                                                                                                                                                                 /*null terminate the line*/
                    break;                                                                                                                                                                                                                                                                                      /*we get out of here. There's nothing to do. Go to the next line. */
                }
                else if ((comment[a][y] != '/') || (comment[a][y + 1] != '*')) /* If we are not in a single line comment(above) and we do not see the start of a multiline comment, copy code over*/
                {
                    weare__acomment = OUT;                                                                                                                                                                                                                                                                                                              /*we are OUT of a comment*/
                    nocomment[a][x] = comment[a][y];                                                                                                                                                                                                                                                                                      // copy text from the comment array to the nocomment array
                    printf("DEBUGOUTPUT line number: %d copying stuff from comment to nocomment on line 1, NOT in comment: stringliteral is %d, weare__acomment is%d, nocomment[%d][%d] is %c, comment[%d][%d] is %c, comment[%d][%d] is %c \n", __LINE__, stringliteral, weare__acomment, a, x, nocomment[a][x], a, y, comment[a][y], a, y + 1, comment[a][y + 1]); /* for debugging */
                    x++;                                                                                                                                                                                                                                                                                                                  // go to the next character in the comment array
                    y++;                                                                                                                                                                                                                                                                                                                  // go to the next character in the nocomment array
                }
                else if (((comment[a][y] == '/') && (comment[a][y + 1] == '*')) && (stringliteral == IN)) /* If we are not in a multiline comment(above) and we come across a multiline comment beginning while in a string, copy code over*/
                {
                    weare__acomment = OUT;                                                                                                                                                                                                                                                                                                              /*we are OUT of a comment*/
                    nocomment[a][x] = comment[a][y];                                                                                                                                                                                                                                                                                      // copy text from the comment array to the nocomment array
                    printf("DEBUGOUTPUT line number: %d copying stuff from comment to nocomment on line 1, NOT in comment: stringliteral is %d, weare__acomment is%d, nocomment[%d][%d] is %c, comment[%d][%d] is %c, comment[%d][%d] is %c \n", __LINE__, stringliteral, weare__acomment, a, x, nocomment[a][x], a, y, comment[a][y], a, y + 1, comment[a][y + 1]); /* for debugging */
                    x++;                                                                                                                                                                                                                                                                                                                  // go to the next character in the comment array
                    y++;                                                                                                                                                                                                                                                                                                                  // go to the next character in the nocomment array
                }
                else if (((comment[a][y] == '/') && (comment[a][y + 1] == '*')) && (stringliteral == OUT))                    /*if we DO see a multiline comment, iterate the commented array character up without iterating new array character up, and don't copy the text over*/
                {                                                                                                             /*I changed this to an else-if because C is dumb and runs this else as long as ONE of the conditions in the above if is false, not both. I need to make sure this only runs when we get into a comment man!!*/
                    y = y + 2;                                                                                                /*move past the two characters that begin the comment in the comment[] array*/
                    weare__acomment = IN;                                                                                                   /*mark our status: we are inside a comment*/
                    while ((weare__acomment != OUT) && (y < MAXLINELENGTH - 2) && ((comment[a][y] != '\0') || (comment[a][y + 1] != '\0'))) /*Keep iterating nocomment[a][y] forward, looking for the end of the comment, until we get to a null terminator or the end of the line: run as long as we are in a comment*/
                    {
                        stringliteral = stringinorout(stringliteral, charliteral, comment[a][y], comment[a][y - 1], y);                                                                                                                                                                                          // check if we're in a string
                        weare__acomment = IN;                                                                                                                                                                                                                                                                                  // set that we are IN a comment
                        printf("DEBUGOUTPUT line number: %d inside a MULTILINE comment on line 1: stringliteral is %d, weare__acomment is%d, nocomment[%d][%d] is %c, comment[%d][%d] is %c, comment[%d][%d] is %c \n", __LINE__, stringliteral, weare__acomment, a, x, nocomment[a][x], a, y, comment[a][y], a, y + 1, comment[a][y + 1]); /* for debugging */
                        y++;                                                                                                                                                                                                                                                                                     // move forward in the comment[a][y] array skipping over elements of the text as long as we are still inside a comment
                        if (((y == MAXLINELENGTH - 3) || (comment[a][y] == '\0') || (comment[a][y + 1] == '\0')) && (stringliteral == OUT))                                                                                                                                                                      /*if we made it to the end of the line and the multiline comment hasn't ended, add a newline character */
                        {
                            nocomment[a][x] = '\n';                                                           // add a newline character.
                        }                                                                                     /* once we see the two characters that begin the comment, we iterate y for the commented array up without iterating x for the non-commented array*/
                        if (((comment[a][y] == '*') && (comment[a][y + 1] == '/')) && (stringliteral == OUT)) /*If we find the two characters that end the comment block, move out of the comment & mark we're out of a comment*/
                        {
                            printf("DEBUGOUTPUT line number: %d end of multiline comment on line 1: stringliteral is %d, weare__acomment is%d, nocomment[%d][%d] is %c, comment[%d][%d] is %c, comment[%d][%d] is %c \n", __LINE__, stringliteral, weare__acomment, a, x, nocomment[a][x], a, y, comment[a][y], a, y + 1, comment[a][y + 1]); /* for debugging */
                            y = y + 2;                                                                                                                                                                                                                                                                             /* add 2 to y so that we skip over the comment in the commented array!*/
                            weare__acomment = OUT;                                                                                                                                                                                                                                                                               /* specify that we are OUT of a comment again; this breaks us out of this while loop where we are looking for the end of a comment*/
                        }
                    }
                }
                else
                {
                    printf("If you're here, you're truly lost: I don't know what to tell you\n");
                    printf("DEBUGOUTPUT line number: %d on line 1, at the else NOT in comment: stringliteral is %d, weare__acomment is%d, nocomment[%d][%d] is %c, comment[%d][%d] is %c, comment[%d][%d] is %c \n", __LINE__, stringliteral, weare__acomment, a, x, nocomment[a][x], a, y, comment[a][y], a, y + 1, comment[a][y + 1]); /* for debugging */

                    break; /*FOR DEBUGGING*/
                }
            }
        }
        else
        {
            while ((y < MAXLINELENGTH - 2) && ((comment[a][y] != '\0') || (comment[a][y + 1] != '\0')))
            {

                if (weare__acomment == IN)
                {
                    /*if weare__acomment = IN, we are in a comment as we enter a new line:*/
                    while ((y < MAXLINELENGTH - 2) && ((comment[a][y] != '\0') || (comment[a][y + 1] != '\0')) && (weare__acomment != OUT)) /*this runs until we see the characters that end the comment*/
                    {
                        stringliteral = stringinorout(stringliteral, charliteral, comment[a][y], comment[a][y - 1], y); // check if we're in a string

                        weare__acomment = IN;
                        printf("DEBUGOUTPUT line number: %d INSIDE multiline comment on line 2: stringliteral is %d, weare__acomment is%d, nocomment[%d][%d] is %c, comment[%d][%d] is %c, comment[%d][%d] is %c \n", __LINE__, stringliteral, weare__acomment, a, x, nocomment[a][x], a, y, comment[a][y], a, y + 1, comment[a][y + 1]);
                        y++;                                                                                  /* once we see the two characters that begin the comment, we iterate y for the commented array up without iterating x for the non-commented array*/
                        if (((comment[a][y] == '/') && (comment[a][y + 1] == '/')) && (stringliteral == OUT)) /*if we see a SINGLE line comment*/
                        {

                            printf("DEBUGOUTPUT line number: %d WE FOUND A SINGLELINE // COMMENT INSIDE multiline comment on line 2, stringliteral is %d, weare__acomment is%d, nocomment[%d][%d] is %c, comment[%d][%d] is %c, comment[%d][%d] is %c \n", __LINE__, stringliteral, weare__acomment, a, x, nocomment[a][x], a, y - 1, comment[a][y - 1], a, y, comment[a][y]);
                            weare__acomment = IN;
                            y = y + 1; /*skip over it*/
                            weare__acomment = IN;
                        }
                        if ((comment[a][y - 1] == '*' && comment[a][y] == '/') && (stringliteral == OUT)) /*Look out for the two characters that end the comment block!*/
                        {
                            printf("DEBUGOUTPUT line number: %d end of multiline comment on line 2: stringliteral is %d, weare__acomment is%d, nocomment[%d][%d] is %c, comment[%d][%d] is %c, comment[%d][%d] is %c \n", __LINE__, stringliteral, weare__acomment, a, x, nocomment[a][x], a, y, comment[a][y], a, y + 1, comment[a][y + 1]);
                            //  multilinecommentend = TRUE; /*this will take us to the top of the loop*/
                            y = y + 2; /* add 2 to y so that we skip over it in the commented array!*/
                            weare__acomment = OUT;   /*we are OUT of a comment again*/
                            printf("DEBUGOUTPUT line number: %d we skipped over the multiline comment on line 2: stringliteral is %d, weare__acomment is%d, nocomment[%d][%d] is %c, comment[%d][%d] is %c, comment[%d][%d] is %c \n", __LINE__, stringliteral, weare__acomment, a, x, nocomment[a][x], a, y, comment[a][y], a, y + 1, comment[a][y + 1]);
                        }
                        else if (((comment[a][y] == '*') && (comment[a][y + 1] == '/')) && (stringliteral == IN)) /* If we meet the end of a comment inside a string literal, it doesn't matter, because... you're not in a string when you're inside a comment. If we are inside a multiline comment, and we see a quote, it doesn't matter */
                        {
                            y = y + 2; /* add 2 to y so that we skip over it in the commented array!*/
                            weare__acomment = OUT;   /*we are OUT of a comment again*/

                            printf("DEBUGOUTPUT line number: %d in multiline comment on line 2, stringliteral is %d, weare__acomment is%d, nocomment[%d][%d] is %c, comment[%d][%d] is %c, comment[%d][%d] is %c \n", __LINE__, stringliteral, weare__acomment, a, x, nocomment[a][x], a, y, comment[a][y], a, y + 1, comment[a][y + 1]); /* for debugging */
                        }
                    }
                }
                else
                { /*write the logic for not iterating upwards when a /* is seen until a */ // is seen.
                    while ((comment[a][y] != '\0') && (y < MAXLINELENGTH - 1))
                    {
                        stringliteral = stringinorout(stringliteral, charliteral, comment[a][y], comment[a][y - 1], y); // check if we're in a string

                        if (((comment[a][y] == '/') && (comment[a][y + 1] == '/')) && (stringliteral == OUT)) /*if we see a SINGLE line comment*/
                        {
                            printf("DEBUGOUTPUT line number: %d stringliteral is %d I DETECTED A SINGLE LINE COMMENT AT comment[%d][%d] which is %c (should be a slash) and comment[%d][%d] which is %c (should be a slash)! weare__acomment is%d\n", __LINE__, stringliteral, a, y, comment[a][y], a, y + 1, comment[a][y + 1], weare__acomment);
                            singlelinecomment = YES;

                            nocomment[a][x] = '\0'; // null terminate the end of the line break;
                            break;                  /*we get out of here. There's nothing to do. Go to the next line. */
                        }
                        else if ((comment[a][y] != '/') || (comment[a][y + 1] != '*'))
                        {            /*if we do not see the first part of a comment, copy the commented array to the non-commented array directly*/
                            weare__acomment = OUT; /*we are OUT of a comment*/
                            nocomment[a][x] = comment[a][y];
                            printf("DEBUGOUTPUT line number: %d stringliteral is %d copying stuff from comment to nocomment on line 2, NOT in comment: weare__acomment is%d, nocomment[%d][%d] is %c, comment[%d][%d] is %c, comment[%d][%d] is %c \n", __LINE__, stringliteral, weare__acomment, a, x, nocomment[a][x], a, y, comment[a][y], a, y + 1, comment[a][y + 1]);
                            x++;
                            y++;
                        }
                        else if (((comment[a][y] == '/') && (comment[a][y + 1] == '*')) && (stringliteral == OUT))                    /*if we DO see a comment, iterate the commented array character up without iterating new array character up, and don't copy the text over*/
                        {                                                                                                             /*I changed this to an else-if because I didn't realize C runs this else as long as ONE of the conditions in the above if is false, not both. I need to make sure this only runs when we get into a comment man!!*/
                            y = y + 2;                                                                                                /*move past the two characters that begin the comment in the comment[] array*/
                            weare__acomment = IN; /*mark our status: we are inside a comment*/                                                      /*we are IN a comment*/
                            while ((weare__acomment != OUT) && (y < MAXLINELENGTH - 2) && ((comment[a][y] != '\0') || (comment[a][y + 1] != '\0'))) /*this runs until we see the characters that end the comment*/
                            {
                                stringliteral = stringinorout(stringliteral, charliteral, comment[a][y], comment[a][y - 1], y); // check if we're in a string

                                weare__acomment = IN;
                                printf("DEBUGOUTPUT line number: %d inside a MULTILINE comment on line 2: stringliteral is %d, weare__acomment is%d, nocomment[%d][%d] is %c, comment[%d][%d] is %c, comment[%d][%d] is %c \n", __LINE__, stringliteral, weare__acomment, a, x, nocomment[a][x], a, y, comment[a][y], a, y + 1, comment[a][y + 1]);

                                y++;
                                if (((y == MAXLINELENGTH - 3) || (comment[a][y] == '\0') || (comment[a][y + 1] == '\0')) && (stringliteral == OUT))
                                { /*if we made it to the end of the line and the multiline comment hasn't ended, add a newline character */
                                    nocomment[a][x] = '\n';
                                }                                                                                     /* once we see the two characters that begin the comment, we iterate y for the commented array up without iterating x for the non-commented array*/
                                if (((comment[a][y] == '*') && (comment[a][y + 1] == '/')) && (stringliteral == OUT)) /*Look out for the two characters that end the comment block!*/
                                {
                                    printf("DEBUGOUTPUT line %d: end of multiline comment on line 2: stringliteral is %d, weare__acomment is%d, nocomment[%d][%d] is %c, comment[%d][%d] is %c, comment[%d][%d] is %c \n", __LINE__, stringliteral, weare__acomment, a, x, nocomment[a][x], a, y, comment[a][y], a, y + 1, comment[a][y + 1]);
                                    y = y + 2; /* add 2 to y so that we skip over it in the commented array!*/
                                    weare__acomment = OUT;   /*we are OUT of a comment again, this breaks us out of this while loop*/
                                }
                            }
                        }

                        else
                        {
                            printf("If you're here, you're truly lost: I don't know what to tell you\n");
                            break; /*FOR DEBUGGING*/
                        }
                    }
                }
            }
        }
    }

    // SAVE WHAT I PROCESSED TO A FILE
    FILE *savefilenocomments = savefile();

    printarray(nocomment, linecountoutput);

    for (int z = 0; z < linecountinput; z++) /*this writes the processed output without comments to my file I specified*/
    {
        fprintf(savefilenocomments, "%s", nocomment[z]);
    }

    // PRINT THE C PROGRAM PROCESSED BY THE PROGRAM, WITHOUT COMMENTS

    printf("\nTHIS IS THE UN-COMMENTED, PROCESSED VERSION OF THE PROGRAM!\n\n");

    for (int z = 0; z < linecountinput; z++) /*this prints the processed output without comments*/
    {
        printf("%s", nocomment[z]);
    } /*print the processed, uncommented program */

    fclose(inputfile);
    fclose(savefilenocomments);
}
