#include <stdio.h>

#define MAXLINE 1000
#define LINELENGTH 60 /*how long before we cut off the line?*/

void wordwrap(char b[]); /*function that will print one line wrapped and shrink character array down to be everything that was not wrapped*/
char s[MAXLINE];         /*this character array stores what we type as a global variable so it doesn't get fucked up when messing with it inside/outside of a function*/
int endofinput;          /*end of whatever we typed, we need to add a null terminator after this so we need to keep track of where this is*/

int main()
{
    int line2nullterminatorpos; /*where the null terminator goes on line 2*/
    int c, i, j, k, l;          /*for for loops*/
    endofinput = line2nullterminatorpos = c = i = j = k = l = 0;

    for (i = 0; i < MAXLINE - 1 && (c = getchar()) != EOF && c != '\n'; i++) /* get text as long as it's smaller than MAXLINE*/
    {
        s[i] = c;                                                    /*store text as char array*/
                endofinput++;                                                /*make sure this follows up as we type forward*/
        
    }
    /*place a null terminator at the end of the input*/
    s[endofinput] = '\0';

    
    while (endofinput > LINELENGTH) /*as long as the character array is longer than the size of a line, run the code below*/
    {
        /*put code here that does the following:
        1) Run function that takes char array
        This function should
        a) count backwards from s[LINELENGTH] to find a blank
        b) find the blank
        c) set that number as a variable called wheretowrap.
    d) take s[0] to s[wheretowrap] and put this into a char array called w1, which will be the first line.
        d) print w1, our first line, which will fit.
        e) take from s[wheretowrap] to the end of s[] (everything from s[wheretowrap] to the null terminator at the end of s and put this into a new character array called w2[]
        f) erase s[]
        g) take w2[] and put it into s[] */

        wordwrap(s);
    }

    /* 2) After while loop, print whatever is left in s[], as it will be the last line less than the linelength */
    printf("%s\n", s);
}

/*function that will wordwrap*/
void wordwrap(char b[])
{
    int wheretoputnullterminatoronw2, t, u, w, x, y, z, wheretowrap;
    int w2postwrap; /*this is what the size of line 2 will be after subtracting line 1 from it*/
    w2postwrap; wheretoputnullterminatoronw2 = t = u = w = x = y = z = wheretowrap = 0;
    char w1[MAXLINE]; /*this is the character array for the line we have wrapped, before the cut(the shrunk part)*/
    char w2[MAXLINE]; /*this is the character array for the line we have wrapped, after the cut(everything that is left)*/

    /*x will be initialized at LINELENGTH, which is the maximum length a single line can be*/
    x = LINELENGTH;
    /*start at the end of line 1 of my character array and go backwards to find a blank or a tab I can use as a cut point.
    I can't cut in the middle of a word, I have to cut at a blank or a tab if I am going to wrap properly to the next line*/
    while (b[x] != EOF)
    {
        x--;                             /* count backwards*/
        if (b[x] == ' ' || b[x] == '\t') /*if it's a blank or a tab*/
        {
            wheretowrap = x; /*set the START point for our cut, to the point that is a tab or a blank*/
                                 
            break;               /*since a while loop will keep going, i want to END this part of the program the moment we find the first blank or tab*/
        }
    }

    /*make a new character array with the first line*/
    for (y = 0; y <= wheretowrap; y++)
    {
        w1[y] = b[y];
    }
    /*add a null terminator to the end of the first line character array*/
    w1[wheretowrap] = '\0';
    printf("%s\n", w1);

    /*fill up w2 character array, which is everything after line 1, with everything that you did not print in line 1.*/

    for (w = wheretowrap, z = 0; b[w] != '\0'; w++, z++)
    {
        w2[z] = b[w];
        wheretoputnullterminatoronw2 = w;
    }
    /*place null terminator at the end*/
    w2[wheretoputnullterminatoronw2 + 1] = '\0';
    /*after placing null terminator, what is endofinput? for debugging*/
    
    printf("endofinput after placing null terminator on w2 is %d DEBUGOUTPUT\n\n",endofinput); /*for debugging*/

    w2postwrap = endofinput - wheretowrap;
    printf("endofinput is %d and wheretowrap is %d and w2postwrap is %d DEBUGOUTPUT\n\n",endofinput, wheretowrap, w2postwrap); /*for debugging*/

    endofinput = w2postwrap; 

    printf("endofinput after doing the math to reduce it is %d DEBUGOUTPUT\n\n", endofinput); /*for debugging*/

    printf("w2 is %s DEBUGCODE\n\n", w2); /*for debugging*/

    /*erase the global array, s, which held the user's typed input*/

    for (u = 0; u <= sizeof(s); u++)
    {
        s[u] = '\0';
    }

    printf("endofinput after erasing the s array is %d DEBUGOUTPUT\n\n", endofinput); /*for debugging*/

    /*set the global array, s, which held the user's typed input to w2, which is all of the text after cutting off the first line & wrapping*/

    for (t = 0; w2[t] != '\0'; t++)
    {
        s[t] = w2[t];
        wheretoputnullterminatoronw2 = t;
    }

    printf("endofinput after setting the s array to w2 is %d DEBUGOUTPUT\n\n", endofinput); /*for debugging*/

    s[wheretoputnullterminatoronw2 + 1] = '\0';

    printf("endofinput after putting a null terminator at the end of the new s array is %d DEBUGOUTPUT\n\n", endofinput); /*for debugging*/

    printf("s array is %s  inside function wordwrap DEBUGCODE\n\n",s); /*for debugging*/
    printf("endofinput is %d at the end of the wordwrap DEBUGCODE\n\n", endofinput); /*for debugging*/
}