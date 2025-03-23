#include <stdio.h>
#define MAXLINELENGTH 1000
#define MAXLINES 1000
#define MAXFILENAME 100
#define IN 0  /*are we in a comment?*/
#define OUT 1 /*are we out of a comment?*/

void main()
{
    int i;                                   /* use for looping to collect input from user */
    i = 0;                                   /* declare i as 0 */
    int j;                                   /*use for looping to spit file being read into string array*/
    j = 0;                                   /* declare j as 0 */
    int x;                                   /*use in for loop to count up in the nocomments array. this goes up when there are no comments */
    int w;                                   /*used to keep track of where we are - IN or OUT of a comment? */
    w = OUT;                                 /*start as out of a comment*/
    x = 0;                                   /*declare x as 0*/
    int y;                                   /*use in for loop to count up in the comments array - this goes up when there are no comments, and when there are comments*/
    y = 0;                                   /*declare y as 0*/
    int linewereon;                          /* keep track of what line we are on in our string array while copying input file to it*/
    linewereon = 0;                          /*initialize linewereon at 0*/
    int linelength;                          /*how long each line I am taking from my file is*/
    linelength = 0;                          /*initialize at 0 */
    char filename[MAXFILENAME];              /* this will be where we store the name of our filename */
    char nocomment[MAXLINES][MAXLINELENGTH]; /*this is where I am storing the uncommented line after processing*/
    char comment[MAXLINES][MAXLINELENGTH];   /*array of strings we will store the file with comments in*/
    char filetempcontents[MAXLINELENGTH];    /*this is where we store the text of our file as we read it line by line temporarily */

    // ASK THE USER WHAT FILE THEY WANT TO WORK ON

    printf("What is the name of the file you wish to remove comments from in this directory?\n\n");
    while ((i < 98) && (filename[i] = getc(stdin)) != EOF)
    { /* have user type in filename */
        if (filename[i] != '\n')
        { /*take user input into filename before they hit enter*/
            i++;
        }
        else
        {
            filename[i] = '\0'; /* null terminate filename character array once user hits enter */
            break;              /*end acceptance of while loop that accepts user input into filename[] once they hit enter*/
        }
    }

    // OPEN THE FILE THE USER HAS CHOSEN TO WORK ON

    FILE *program = fopen(filename, "r");                           /*open file specified above and assign to *program pointer */
    printf("The filename you want me to open is %s\n\n", filename); /*Confirm I am opening the correct file*/

    if (program == NULL)
    { /*error handling if it cannot open the file*/
        perror("Error opening file");
    }
    else
    {
        printf("%p\n\n", (void *)program); /*tell me the file as a memory address if it did open*/
    }

    // COPY THE CONTENTS OF THE FILE TO A MULTI STRING ARRAY SO WE MAY SEARCH IT FOR COMMENTS

    while (fgets(filetempcontents, MAXLINELENGTH, program) != NULL)
    {
        linelength = 0;
        while (filetempcontents[linelength] != '\0')
        {
            linelength++;
        }
        for (int x = 0; x <= linelength; x++) /*copy the contents of each line of the file over to a line in our string array*/
        {
            comment[linewereon][x] = filetempcontents[x];
        }
        linewereon++; /* each time the while loop loops we're on a new line, so iterate the line we're on in the string array */
    }

    // PRINT THE C PROGRAM LOADED INTO THE PROGRAM, WITH COMMENTS

    for (int x = 0; x < linewereon; x++) /*this prints the file I loaded into my string array just to make sure I stored it properly*/
    {
        printf("%s", comment[x]);
    } /*print the program */

    printf("\n\nTHIS IS THE COMMENTED VERSION OF THE PROGRAM!\n\n");

    /*everything below is a total mess at the moment*/

    // REMOVE COMMENTS FROM THE FILE LOADED INTO THE MULTI STRING ARRAY comment[][] AND MOVE IT TO char nocomment[][]

    for (int a = 0; a <= linewereon; a++, x = 0, y = 0)
    {
        if (w == OUT)
        { /*if we out of a comment, do the following*/

            /*write the logic for not iterating upwards when a /* is seen until a */ // is seen.
            while (comment[a][y] != '\0' && y < MAXLINELENGTH - 1)
            {
                w = OUT;
                if (comment[a][y] != '/' && comment[a][y + 1] != '*')
                {
                    if (comment[a][y] == '/' && comment[a][y + 1] == '/') /* handling single line comments - // - when outside a comment */
                    {
                        printf("a is %d, comment[%d][%d] is %c, comment[%d][%d] is %c DEBUGOUTPUTLOLOL\n\n", a, a, y, comment[a][y], a, y + 1, comment[a][y + 1]); /*for debugging*/
                    }
                    else
                    {            /*if we do not see the first part of a comment, copy the commented array to the non-commented array directly*/
                        w = OUT; /*we are OUT of a comment*/
                        nocomment[a][x] = comment[a][y];
                        printf("DEBUGOUTPUT w is %d nocomment[%d][%d] is %c, comment[%d][%d] is %c\n\n", w, a, x, nocomment[a][x], a, y, comment[a][y]); /*FOR DEBUGGING*/
                        x++;
                        y++;
                    }
                }
                else /*if we DO see a comment, iterate the commented array up*/
                {
                    y = y + 2;                                                                        /*move past the two characters that begin the comment*/
                    w = IN;                                                                           /*we are IN a comment*/
                    while (comment[a][y] != '*' && comment[a][y + 1] != '/' && y < MAXLINELENGTH - 1) /*this runs until we see the characters that end the comment*/
                    {
                        y++;                                                                                                                             /* once we see the two characters that begin the comment, we iterate y for the commented array up without iterating x for the non-commented array*/
                        printf("DEBUGOUTPUT w is %d nocomment[%d][%d] is %c, comment[%d][%d] is %c\n\n", w, a, x, nocomment[a][x], a, y, comment[a][y]); /*FOR DEBUGGING*/

                        if (comment[a][y] == '*' && comment[a][y + 1] == '/') /*Look out for the two characters that end the comment block!*/
                        {
                            y = y + 2; /* add 2 to y so that we skip over it in the commented array!*/
                            w = OUT;   /*we are OUT of a comment again*/
                            break;     /*break out of this loop, as we have broken out of the comment!*/
                        }
                    }
                }
            }
        }
        else
        {                                                                                     /*if W = IN, we are in a comment as we enter a new line:*/
            while (comment[a][y] != '*' && comment[a][y + 1] != '/' && y < MAXLINELENGTH - 1) /*this runs until we see the characters that end the comment*/
            {
                y++;                                                  /* once we see the two characters that begin the comment, we iterate y for the commented array up without iterating x for the non-commented array*/
                if (comment[a][y] == '*' && comment[a][y + 1] == '/') /*Look out for the two characters that end the comment block!*/
                {
                    y = y + 2; /* add 2 to y so that we skip over it in the commented array!*/
                    w = OUT;   /*we are OUT of a comment again*/
                    break;     /*break out of this loop, as we have broken out of the comment!*/
                }
            }
        }
    }

    // PRINT THE C PROGRAM PROCESSED BY THE PROGRAM, WITHOUT COMMENTS

    for (int x = 0; x < linewereon; x++) /*this prints the processed output without comments*/
    {
        // printf("DEBUGOUTPUT linewereon is %d, x is %d from nocomment[%d] which is %s\n\n", linewereon, x, x, nocomment[x]); /*FOR DEBUGGING*/
        printf("%s", nocomment[x]);
    } /*print the processed, uncommented program */

    printf("\n\nTHIS IS THE UN-COMMENTED, PROCESSED VERSION OF THE PROGRAM!\n\n");
}
