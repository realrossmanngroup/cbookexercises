//PROGRAM TO REMOVE SINGLE & MULTI LINE COMMENTS FROM A C PROGRAM, WITHOUT MESSING UP FORMATTING

#include <stdio.h>
#define MAXLINELENGTH 1000
#define MAXLINES 1000
#define MAXFILENAME 100
#define IN 0  /*are we in a comment?*/
#define OUT 1 /*are we out of a comment?*/
#define YES 1 /*single line comment found?*/
#define NO 0  /*single line comment not found*/

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
    }
    else
    {
        printf("%p is open, that's filename: %s and is ready for writing\n\n", (void *)outputfile, outputfilename); /*tell me the file as a memory address & filename if it did open*/
        return outputfile;                                                                                          /*return the program to the function so that we have an open file in our program after using this*/
    }
}

void main()
{
    int j = 0;                               /*use for looping to spit file being read into string array*/
    int x = 0;                               /*use in for loop to count up in the nocomments array. this goes up when there are no comments */
    int w = OUT;                             /*used to keep track of where we are - IN or OUT of a comment? Start out of a comment */
    int y = 0;                               /*use in for loop to count up in the comments array - this goes up when there are no comments, and when there are comments*/
    int linewereon = 0;                      /* keep track of what line we are on in our string array while copying input file to it*/
    int wheretoplacenullterminator = 0;      /*where to place null terminator as we copy each line*/
    int linelength = 0;                      /*how long each line I am taking from my file is*/
    int singlelinecomment = NO;              /*bool to tell when we're in a single line comment, initialize at 0*/
    char nocomment[MAXLINES][MAXLINELENGTH]; /*this is where I am storing the uncommented line after processing*/
    char comment[MAXLINES][MAXLINELENGTH];   /*array of strings we will store the file with comments in*/
    char filetempcontents[MAXLINELENGTH];    /*this is where we store the text of our file as we read it line by line temporarily */

    FILE *inputfile = openfile(); /*get input file*/

    // COPY THE CONTENTS OF THE FILE TO A MULTI STRING ARRAY SO WE MAY SEARCH IT FOR COMMENTS

    while (fgets(filetempcontents, MAXLINELENGTH, inputfile) != NULL)
    {
        linelength = 0;
        while (filetempcontents[linelength] != '\0')
        {
            linelength++;
        }
        for (int x = 0; x <= linelength; x++) /*copy the contents of each line of the file over to a line in our string array*/
        {
            comment[linewereon][x] = filetempcontents[x];
            wheretoplacenullterminator = x;
        }
        comment[linewereon][wheretoplacenullterminator] = '\0'; /*place null terminator at the end of each line*/

        linewereon++; /* each time the while loop loops we're on a new line, so iterate the line we're on in the string array */
    }

    // PRINT THE C PROGRAM LOADED INTO THE PROGRAM, WITH COMMENTS

    printf("\n########!!!!!!$$$$$$%%%%%%^^^^^^&&&&&&******(((())))______++++++@@@@@@\nTHIS IS THE COMMENTED, UNPROCESSED VERSION OF THE PROGRAM!\n########!!!!!!$$$$$$%%%%%%^^^^^^&&&&&&******(((())))______++++++@@@@@@\n\n");
    for (int x = 0; x < linewereon; x++) /*this prints the file I loaded into my string array just to make sure I stored it properly*/
    {

        printf("%s", comment[x]);
    } /*print the program */

    /*everything below is a total mess at the moment :'( )*/

    // REMOVE COMMENTS FROM THE FILE LOADED INTO THE MULTI STRING ARRAY comment[][] AND MOVE IT TO char nocomment[][]

    for (int a = 0; a <= linewereon; a++, x = 0, y = 0)
    {
        if (singlelinecomment == YES)
        {
            singlelinecomment = NO;
            continue;
        }
        if (w == OUT)
        { /*if we out of a comment, do the following*/

            /*write the logic for not iterating upwards when a /* is seen until a */ // is seen.
            while ((comment[a][y] != '\0') && (y < MAXLINELENGTH - 1))
            {
                if ((comment[a][y] == '/') && (comment[a][y + 1] == '/')) /*if we see a SINGLE line comment*/
                {
                    singlelinecomment = YES;
                    nocomment[a][x] = '\n'; /*replace the single line comment with a newline character so the formatting isn't a mess*/
                    break;                  /*we get out of here. There's nothing to do. Go to the next line. */
                }
                else if ((comment[a][y] != '/') && (comment[a][y + 1] != '*'))
                {            /*if we do not see the first part of a comment, copy the commented array to the non-commented array directly*/
                    w = OUT; /*we are OUT of a comment*/
                    nocomment[a][x] = comment[a][y];
                    x++;
                    y++;
                }
                else if ((comment[a][y] == '/') && (comment[a][y + 1] == '*'))                                                                                            /*if we DO see a comment, iterate the commented array character up without iterating new array character up, and don't copy the text over*/
                {                                                                                                                                                         /*I changed this to an else-if because C is dumb and runs this else as long as ONE of the conditions in the above if is false, not both. I need to make sure this only runs when we get into a comment man!!*/
                    y = y + 2;                                                                                                                                            /*move past the two characters that begin the comment in the comment[] array*/
                    w = IN; /*mark our status: we are inside a comment*/                                                                                                  /*we are IN a comment*/
                    while (((comment[a][y] != '*') || (comment[a][y + 1] != '/')) && (y < MAXLINELENGTH - 2) && ((comment[a][y] != '\0') || (comment[a][y + 1] != '\0'))) /*this runs until we see the characters that end the comment*/
                    {

                        y++;                                                      /* once we see the two characters that begin the comment, we iterate y for the commented array up without iterating x for the non-commented array*/
                        if ((comment[a][y] == '*') && (comment[a][y + 1] == '/')) /*Look out for the two characters that end the comment block!*/
                        {
                            y = y + 2; /* add 2 to y so that we skip over it in the commented array!*/
                            w = OUT;   /*we are OUT of a comment again*/
                            break;     /*break out of this loop, as we have broken out of the comment!*/
                        }
                    }
                }
                else if ((comment[a][y] != '/') && (comment[a][y + 1] == '*'))
                {            /*This catches a single asterisk on the right side of a blank and makes sure we copy it over. */
                    w = OUT; /*we are OUT of a comment*/
                    nocomment[a][x] = comment[a][y];
                    x++;
                    y++;
                }
                else if ((comment[a][y] == '*') && (comment[a][y + 1] != '/'))
                {            /*This catches a single asterisk on the left side of a blank and makes sure we copy it over. */
                    w = OUT; /*we are OUT of a comment*/
                    nocomment[a][x] = comment[a][y];
                    x++;
                    y++;
                }
                else if ((comment[a][y] == '/') && ((comment[a][y + 1] != '*') || (comment[a][y + 1] != '/')))
                {            /*This catches a single slash on the left side of a blank and makes sure we copy it over. */
                    w = OUT; /*we are OUT of a comment*/
                    nocomment[a][x] = comment[a][y];
                    x++;
                    y++;
                }
                else if ((comment[a][y] != '/') || ((comment[a][y] != '*') && (comment[a][y + 1] == '/')))
                {            /*This catches a single slash on the right side of a blank and makes sure we copy it over. */
                    w = OUT; /*we are OUT of a comment*/
                    nocomment[a][x] = comment[a][y];
                    x++;
                    y++;
                }

                else
                {
                    printf("If you're here, you're truly lost: I don't know what to tell you\n");
                    break; /*FOR DEBUGGING*/
                }
            }
        }
        else
        {                                                                                                                                                         /*if W = IN, we are in a comment as we enter a new line:*/
            while (((comment[a][y] != '*') || (comment[a][y + 1] != '/')) && (y < MAXLINELENGTH - 2) && ((comment[a][y] != '\0') || (comment[a][y + 1] != '\0'))) /*this runs until we see the characters that end the comment*/
            {
                y++;                                                  /* once we see the two characters that begin the comment, we iterate y for the commented array up without iterating x for the non-commented array*/
                if (comment[a][y] == '*' && comment[a][y + 1] == '/') /*Look out for the two characters that end the comment block!*/
                {

                    y = y + 2; /* add 2 to y so that we skip over it in the commented array!*/
                    w = OUT;   /*we are OUT of a comment again*/
                    break;
                    /* break out of this loop, as we have broken out of the comment! */
                }
            }
        }
    }

    // SAVE WHAT I PROCESSED TO A FILE

    FILE *savefilenocomments = savefile();

    for (int x = 0; x < linewereon; x++) /*this writes the processed output without comments to my file I specified*/
    {
        fprintf(savefilenocomments, "%s", nocomment[x]);
    }

    // PRINT THE C PROGRAM PROCESSED BY THE PROGRAM, WITHOUT COMMENTS

    printf("\n########!!!!!!$$$$$$%%%%%%^^^^^^&&&&&&******(((())))______++++++@@@@@@\nTHIS IS THE UN-COMMENTED, PROCESSED VERSION OF THE PROGRAM!\n########!!!!!!$$$$$$%%%%%%^^^^^^&&&&&&******(((())))______++++++@@@@@@\n\n");

    for (int x = 0; x < linewereon; x++) /*this prints the processed output without comments*/
    {
        printf("%s", nocomment[x]);
    } /*print the processed, uncommented program */

    fclose(inputfile);
    fclose(savefilenocomments);
}
