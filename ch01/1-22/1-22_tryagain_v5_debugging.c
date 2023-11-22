#include <stdio.h>

#define MAXLINE 1000
#define LINELENGTH 60 /*how long before we cut off the line?*/

char *wordwrap(char b[]); /*function that will print one line wrapped and shrink character array down to be everything that was not wrapped*/
char s[MAXLINE];          /*this character array stores what we type as a global variable so it doesn't get fucked up when messing with it inside/outside of a function*/

int main()
{
    int endofinput;             /*end of whatever we typed, we need to add a null terminator after this so we need to keep track of where this is*/
    int line2nullterminatorpos; /*where the null terminator goes on line 2*/
    int c, i, j, k, l;          /*for for loops*/
    endofinput = line2nullterminatorpos = c = i = j = k = l = 0;

    for (i = 0; i < MAXLINE - 1 && (c = getchar()) != EOF && c != '\n'; i++) /* get text as long as it's smaller than MAXLINE*/
    {
        s[i] = c;                                                         /*store text as char array*/
        printf("this is s[%d] in the for loop capturing input: %c\n\n", i, s[i]); /*for debugging*/
        /* endofinput++; /*make sure this follows up as we type forward*/ /*I commented this out while debugging*/
    }

    /*place a null terminator at the end of the input
    s[endofinput + 1] = '\0'; */
    /*I commented this out while debugging*/

    /*test whether it actually captured my input*/
    printf("this is my input after my capture to char array s is done: %s\n\n", s); /*this line is for debugging*/

    while ((sizeof(s) / sizeof(s[0])) > LINELENGTH) /*as long as the character array is longer than the size of a line, run the code below*/
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
    printf("%s", s);
}

/*function that will wordwrap*/
char *wordwrap(char b[])
{
    int wheretoputnullterminatoronw2, t, u, w, x, y, z, wheretowrap;
    wheretoputnullterminatoronw2 = t = u = w = x = y = z = wheretowrap = 0;
    char w1[MAXLINE]; /*this is the character array for the line we have wrapped, before the cut(the shrunk part)*/
    char w2[MAXLINE]; /*this is the character array for the line we have wrapped, after the cut(everything that is left)*/

    /*x will be initialized at LINELENGTH, which is the maximum length a single line can be*/
    x = LINELENGTH;
    printf("the s array(what s is) is as follows: %s\n\n",s); /*for debugging purposes*/
    printf("the b array(what s becomes when I pass it to wordwrap function) is as follows: %s\n\n",b); /*for debugging purposes*/
    printf("If you see what you typed above, it means your array has been passed to the wordwrap function properly!");
    printf("x is %d before the while loop in my function\n\n", x); /*for debugging purposes*/
    /*start at the end of line 1 of my character array and go backwards to find a blank or a tab I can use as a cut point.
    I can't cut in the middle of a word, I have to cut at a blank or a tab if I am going to wrap properly to the next line*/

    while (b[x] != ' ' && b[x] != '\t')
    {
        if (x < 1)
        {
            exit(0);
        }
        /*count backwards from the end of the line, x is end of the line(linelength)*/
        printf("x is %d within the while loop\n\n", x);             /*this is for debugging*/
        printf("the character in the b array we are at is %c\n\n", b[x]); /*this is for debugging*/
        x--;
        wheretowrap = x - 1;
    }

    /*make a new character array with the first line*/
    for (y = 0; y <= wheretowrap; y++)
    {
        w1[y] = b[y];
    }
    /*add a null terminator to the end of the first line character array*/
    w1[wheretowrap + 1] = '\0';
    printf("%s\n", w1);

    /*fill up w2 character array, which is everything after line 1, with everything that you did not print in line 1.*/

    for (w = wheretowrap, z = 0; b[w] != '\0'; w++, z++)
    {
        w2[z] = b[w];
        wheretoputnullterminatoronw2 = w;
    }
    /*place null terminator at the end*/
    w2[wheretoputnullterminatoronw2 + 1] = '\0';

    /*erase the global array, s, which held the user's typed input*/

    for (u = 0; u <= sizeof(s); u++)
    {
        s[u] = '\0';
    }

    /*set the global array, s, which held the user's typed input to w2, which is all of the text after cutting off the first line & wrapping*/

    for (t = 0; w2[t] != '\0'; t++)
    {
        s[t] = w2[t];
        wheretoputnullterminatoronw2 = t;
    }

    s[wheretoputnullterminatoronw2 + 1] = '\0';
}
