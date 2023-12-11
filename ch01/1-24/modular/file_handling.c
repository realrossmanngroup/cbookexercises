#include <stdio.h>
#include <stdlib.h>
#include "file_handling.h"
#include "definitions.h"

// FUNCTION TO OPEN A FILE FOR PROCESSING & REMOVING COMMENTS FROM

FILE *openfile()
{
    char inputfilename[MAXFILENAME];    // this will be where we store the name of our input file
    int i = 0;                          // use for looping to collect input from user
    // ASK THE USER WHAT FILE THEY WANT TO WORK ON
    printf("What is the name of the INPUT file you wish to check for imbalanced parenthesis?\n\n");
    while ((i < MAXFILENAME - 1) && (inputfilename[i] = getc(stdin)) != EOF)
    { // have user type in input filename
        if (inputfilename[i] != '\n')
        { // take user input into filename before they hit enter
            i++;
        }
        else
        {
            inputfilename[i] = '\0'; // null terminate filename character array once user hits enter
            break;                   // end acceptance of while loop that accepts user input into filename[] once they hit enter
        }
    }

    // OPEN THE FILE THE USER HAS CHOSEN TO WORK ON

    FILE *openedfile = fopen(inputfilename, "r");                        // open file specified above and assign to *program pointer
    printf("The filename you want me to open is %s\n\n", inputfilename); // Confirm I am opening the correct file

    if (openedfile == NULL)
    { // error handling if it cannot open the file
        perror("Error opening file");
    }
    else
    {
        printf("%p is open, that's filename: %s\n\n", (void *)openedfile, inputfilename); // tell me the file as a memory address & filename if it did open
        return openedfile;                                                                // return the program to the function so that we have an open file in our program after using this
    }
}

// FUNCTION FOR CREATING A FILE TO SAVE THE PROCESSED, UNCOMMENTED CODE TO

FILE *savefile()
{

    char outputfilename[MAXFILENAME]; // this will be where we store the name of our output file
    int i = 0;                        // use for looping to collect input from user
    // ASK THE USER WHAT FILE THEY WANT TO SAVE TO
    printf("What is the name of the OUTPUT file you wish to save your uncommented code to in this directory?\n\n");
    while ((i < MAXFILENAME - 1) && (outputfilename[i] = getc(stdin)) != EOF)
    { // have user type in filename to save to
        if (outputfilename[i] != '\n')
        { // take user input into filename before they hit enter
            i++;
        }
        else
        {
            outputfilename[i] = '\0'; // null terminate filename character array once user hits enter
            break;                    // end acceptance of while loop that saves program output
        }
    }

    // If file is good, tell the user & return it to the function call

    FILE *outputfile = fopen(outputfilename, "w");                              // open file specified above and assign to *program pointer
    printf("The filename you want me to save to is is %s\n\n", outputfilename); // Confirm I am opening the correct file

    if (outputfile == NULL)
    { // error handling if it cannot open the file
        perror("Error creating file");
    }
    else
    {
        printf("%p is open, that's filename: %s and is ready for writing\n\n", (void *)outputfile, outputfilename); // tell me the file as a memory address & filename if it did open
        return outputfile;                                                                                          // return the program to the function so that we have an open file in our program after using this
    }
}

// FUNCTION FOR COPYING PROGRAM FROM FILE TO program[] ARRAY SO WE CAN PROCESS IT WITHIN THIS PROGRAM

void filetoarray(FILE *file)
{
    char array[MAXLINES][MAXCHARS];     // array we will store each line of file to
    int linelength = 0;                 // how long each line I am taking from my file is
    int wheretoplacenullterminator = 0; // where to place null terminator as we copy each line
    char filetempcontents[MAXCHARS];    // this is where we store the text of our file as we read it line by line temporarily

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
        for (int charposition = 0; charposition <= linelength; charposition++) // copy the contents of each line of the file over to a line in our string array
        {
            program[linecountinput][charposition] = filetempcontents[charposition];
            wheretoplacenullterminator = charposition;
        }
        program[linecountinput][wheretoplacenullterminator] = '\0';         // place null terminator at the end of each line
        howlongisthisline[linecountinput] = wheretoplacenullterminator + 1; // keep track of the length of each line

        if (linecountinput < MAXLINES - 2)
        {
            linecountinput++; // each time the while loop loops we're on a new line, so iterate the line we're on in the string array
        }
        else
        {
		exit(1);

        }
    }
}
