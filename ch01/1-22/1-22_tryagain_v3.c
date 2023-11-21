#include <stdio.h>

#define MAXLINE 1000
#define LINELENGTH 60 /*how long before we cut off the line?*/

int main()
{
    int endposttruncate;        /*end of line, go back from here, this part will go onto the next line with word wrap*/
    int endpretruncate;         /*end of line, go back to here, this stays on line 1 when word wrapped*/
    int line2nullterminatorpos; /*where the null terminator goes on line 2*/
    int c, i, j, k, l;          /*for for loops*/
    extern char s[MAXLINE];            /*this character array stores what we type as a global variable so it doesn't get fucked up when messing with it inside/outside of a function*/
    char line1array[MAXLINE];   /*this character array will take everything that fits on line 1 from s[MAXLINE]*/
    char line2array[MAXLINE];   /*grab what's after endpretruncate and before endposttruncate on s[MAXLINE], which is what I typed,
    and store it here to be placed on line 2 for */

    endposttruncate = endpretruncate = line2nullterminatorpos = c = i = j = k = l = 0;

    for (i = 0; i < MAXLINE - 1 && (c = getchar()) != EOF && c != '\n'; i++) /* get text as long as it's smaller than MAXLINE*/
    {
        endpretruncate++; /*make sure this follows up as we type forward*/
        s[i] = c;         /*store text as char array*/
    }

    while ((sizeof(s) / sizeof(s[0])) > LINELENGTH) /*as long as the character array is longer than the size of a line, run the code below*/
    {
        /*put code here that does the following:
        
        1) Run function that takes char array
        This function should
        a) count backwards from s[LINELENGTH] to find a blank
        b) find the blank
        c) set that number as a variable called wordwrap. 
        d) print the char array from s[0] to s[wordwrap]
        e) take from s[wordwrap] to s[i] and put this into a new character array called truncated[]
        f) erase s[]
        g) take truncated[] and put it into s[]

    }
    
    2) After while loop, print whatever is left in s[], as it will be the last line less than the linelength
        */

}