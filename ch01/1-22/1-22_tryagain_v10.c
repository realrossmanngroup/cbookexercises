/*This program is word wrap, exercise 1-22 of Dennis Ritchie's C Programming Language*/

#include <stdio.h>

#define MAXLINE 1000  /*how much can a user type into our program?*/
#define LINELENGTH 60 /*how wide a line can be on screen before it wraps to the next line*/

void wordwrap(char b[]); /*function that prints 1 line wrapped from char array & shrinks character array down to everything - 1st line*/
char s[MAXLINE];         /*this char array stores what we type as a global variable so it doesn't get messed up when messing w/ it inside a function*/
int endofinput;          /*This variable keeps track of the end of our typed input, & must be counted down as we wrap lines*/

int main()
{
    int c, i, j, k, l; /*for for loops*/
    endofinput = c = i = j = k = l = 0;

    for (i = 0; i < MAXLINE - 1 && (c = getchar()) != EOF && c != '\n'; i++) /* get text as long as it's smaller than MAXLINE*/
    {
        s[i] = c;     /*store text as char array*/
        endofinput++; /*make sure this follows up as we type forward*/
    }
    /*place a null terminator at the end of the input*/
    s[endofinput] = '\0';

    while (endofinput > LINELENGTH) /*as long as the character array is longer than the size of a line, run the code below*/
    {
        wordwrap(s); /*function that prints the first 60 characters in the array to its own line at a sensible cutpoint,
                     then deletes what was already printed from the character array */
    }

    printf("%s\n", s); /* The last line will be shorter than LINELENGTH so the above function won't run - print whatever is left in s*/
}

/*function that will wordwrap*/
void wordwrap(char b[])
{
    int w2endofline, x, wheretowrap;
    w2endofline = x = wheretowrap = 0;
    char w1[MAXLINE]; /*this is the char array for the line we have wrapped, that we will print */
    char w2[MAXLINE]; /*this is the char array for everything after the cut - input character array minus the first line*/

    /*x will be initialized at LINELENGTH, which is the maximum width in characters a single line can be*/
    x = LINELENGTH;

    /*This while loop starts at the end of line 1, which is linelength, and counts backwards to find a blank or a tab
    to use as a cut point. If it does not find a single blank or tab to use as a cutpoint, it sets LINELENGTH - 2
    to be the cutpoint. We will only cut in the middle of a word or number if there is no suitable point to cut*/
    while (b[x] != EOF)
    {
        x--;                             /*count backwards starting from linelength*/
        if (b[x] == ' ' || b[x] == '\t') /*Look for a blank or a tab*/
        {
            wheretowrap = x + 1; /*set the start point for the cut to the point after the tab/blank we found*/

            break; /*leave the while loop since we found our cutpoint*/
        }
        else /*if there are no cut points once we are at the very beginning of the line
             because the user of the program is a troll, never fear; we will wrap at LINELENGTH - 2*/
        {
            if (x < 1)
            {
                wheretowrap = (LINELENGTH - 2);
                break; /*leave the while loop since we found our cutpoint*/
            }
        }
    }

    /* erase w2 array which is for the second line after we cut line 1 so it doesn't have junk in it*/
    for (int u = 0; u < sizeof(s); u++)
    {
        w2[u] = '\0';
    }

    /*make a new character array with the first line*/
    for (int u = 0; u <= wheretowrap; u++)
    {
        w1[u] = b[u];
    }
    /*add a null terminator to the end of the first line character array*/
    w1[wheretowrap] = '\0';
    printf("%s\n", w1);

    /*fill up w2 character array, which is everything after line 1, with everything that you did not print on line 1 after chopping off everything past 60 characters.*/

    for (int c = wheretowrap, d = 0; b[c] != '\0'; d++, c++)
    {
        w2[d] = b[c];
        w2endofline = d;
    }
    /*place null terminator at the end*/
    w2[w2endofline + 1] = '\0';

    endofinput = endofinput - wheretowrap;

    /*erase the global array, s, which held the user's typed input*/

    for (int u = 0; u < MAXLINE; u++)
    {
        s[u] = '\0';
    }

    /*set the global array, s, which held the user's typed input to w2, which is all of the text after cutting off the first line & wrapping*/

    for (int t = 0; w2[t] != '\0'; t++)
    {
        s[t] = w2[t];
        w2endofline = t;
    }

    s[w2endofline + 1] = '\0';
}