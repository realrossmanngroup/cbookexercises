#include <stdio.h>

#define MAXLINE 1000
#define LINELENGTH 60 /*how long before we cut off the line?*/

int main()
{
    int howfarin;               /*store where I am the in line*/
    int endposttruncate;        /*end of line, go back from here, this part will go onto the next line with word wrap*/
    int endpretruncate;         /*end of line, go back to here, this stays on line 1 when word wrapped*/
    int line2nullterminatorpos; /*where the null terminator goes on line 2*/
    int c, i, j, k, l;          /*for for loops*/
    char s[MAXLINE];            /*this character array stores what we type*/
    char line1array[MAXLINE];   /*this character array will take everything that fits on line 1 from s[MAXLINE]*/
    char line2array[MAXLINE];   /*grab what's after endpretruncate and before endposttruncate on s[MAXLINE], which is what I typed,
    and store it here to be placed on line 2 for */

    howfarin = endposttruncate = endpretruncate = line2nullterminatorpos = c = i = j = k = l = 0;

    for (i = 0; i < MAXLINE - 1 && (c = getchar()) != EOF && c != '\n'; i++) /* get text as long as it's smaller than MAXLINE*/
    {
        howfarin++;
        endpretruncate++; /*make sure this follows up as we type forward*/
        s[i] = c;         /*store text as char array*/
    }

    if (i > LINELENGTH) /*Once we are further than the specified line length into our typed line, find*/
    {
        endposttruncate = i;
        i = LINELENGTH;
        while (s[i] != EOF) /*count backwards from the part we need to put on the 2nd line, look for first blank/tab to use as a cut point*/
        {
            i--;                             /* count backwards*/
            if (s[i] == ' ' || s[i] == '\t') /*if it's a blank or a tab*/
            {
                endpretruncate = i + 1; /*set the START point for our cut, to the point that is a tab or a blank*/
                                        /* printf("line %d says that we set endpretruncate %d equal to s[%d] %c\n", __LINE__, endpretruncate, i, s[i]); DEBUG CODE*/
                break;                  /*since a while loop will keep going and set endpretruncate to the first i in the line, i want to END this part of the program the moment we find the first blank or tab*/
            }
        }
    }

    for (l = 0; l <= MAXLINE; l++)
    { /*ERASE LINE1ARRAY BEFORE USING IT!*/
        line1array[l] = ' ';
    }
    for (j = 0; j <= endpretruncate + 1; j++) /*set line 1 to what we typed, up until the first cut point*/
    {                                         /*add truncated line to array for line 1*/
        line1array[j] = s[j];                 /* define line1array as a character array being what we typed(s[j]), with J ending at first cutpoint)*/
        /* printf("line %d code, line1array[%d] is %c, s[%d] is %c, endpretruncate is %d, endposttruncate is %d\n", __LINE__, j, line1array[j], j, s[j], endpretruncate, endposttruncate); /* DEBUG CODE */
    }
    line1array[endpretruncate] = '\0'; /*add null terminator to the end of line 1 so it's a proper character array*/
    printf("%s\n", line1array);        /* print line 1, truncated*/

    /*create the character array from line 2 by taking the excess text between endpretruncate  and endpostruncate(cut points) from our character array of typed text, s[]*/
    for (l = 0, k = endpretruncate; l <= endposttruncate - endpretruncate, k <= endposttruncate; l++, k++)
    {
        line2array[l] = s[k];
        /* printf("line %d code, line2array[%d] is %c, s[%d] is %c, endpretruncate is %d, endposttruncate is %d\n", __LINE__, l, line2array[l], k, s[k], endpretruncate, endposttruncate); */ /* DEBUG CODE */
    }
    line2array[l] = '\0';
    printf("%s\n", line2array);
}