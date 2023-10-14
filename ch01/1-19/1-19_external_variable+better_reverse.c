#include <stdio.h>

#define MAXLINE 1000 /* maximum input line size */

char reversedversion[MAXLINE];

int get_line(char line[], int maxline);
void copy(char to[], char from[]);
void *reverse(char c[]);

/* reverse a character array*/
void *reverse(char b[])
{
    extern char reversedversion[MAXLINE]; /*declare global variable we will move what we're reversing to*/
    int i, g, h, j, sizeofarray;          /*variables for loop. */
    /* h will count up, g will count down while moving things from the old array(forward text) to the new array(backwards text)
    i is used for a for loop that erases the variable reversedversion that stores the backwards text incase there is already something in there.
    j is used for j is used for a while loop that figures out the length of the array.

    /*erase reversedversion if something was already in it*/
    for (i = 0; i <= MAXLINE; i++)
    {
        reversedversion[i] = ' ';
    }
    /*we're going to find out how large the array is in the reverse function so it doesn't have to be specified anymore!*/
    j = 0;
    while (b[j] != '\0')
    {
        j++;
    }
    sizeofarray = j + 2; /*why +2? firstly arrays in c start with 0 not 1, so if i start from 0 a 4 character array is actualy going to end in 3 which would make the sizeofarray 3
    which would be wrong. Secondly we need space for the null terminator at the end, so that's another in the count. So, for instance, the word "the" would show up as 0, 1, 2 with 
    t, h, and e at spaces 0, 1, and 2 in the array. If j stops counting at 2, that means it'll say the size of the array is 2, even though it's 3...
    also, the null terminator has to be at the end, so in reality this array is 4 characters. t, h, e, and '\0'. So if I use j + 2 I get the proper size. */

    /* Set loop to count g up and h down; g up from 0, and h down from the end of the array */    
    for (g = 0, h = sizeofarray - 2; g <= sizeofarray - 2, h >= 0; g++, h--) /
    {
        if (b[g] != '\0') 
        /*Only copy stuff over if it isn't null terminated. Copying the null terminator over would be a fail. Null terminator marks 
        the end of a string, so it's going to be at the end. If this is a reverse function I am taking the string and putting the end of it(null terminator) 
        at the beginning of the new string, that would make the new string end where it begins which makes no sense. 
        I don't want to put the null terminator at the beginning of my new character array!*/
        {
            reversedversion[h] = b[g];  /*set last character of new array as equal to first character of old array, and keep going until loop ends*/
        /*  printf("%c is b[%d] and %c is reversedversion[%d]\n", b[g], g, reversedversion[h], h); /*print what's going on for debugging purposes, COMMENT THIS OUT WHEN DONE!*/
        }
        else
        {
            reversedversion[sizeofarray - 1] = '\0'; /*when we DO get to a null terminator(end of first character array), make sure to put a null terminator on the END of the new char array*/
        }
    }
}

/* get_line: read a line into s, return length */
int get_line(char s[], int lim)
{
    int c, i;
    for (i = 0; i < lim - 1 && (c = getchar()) != EOF && c != '\n'; i++)
    {
        s[i] = c;
    }
    if (c == '\n')
    {
        s[i] = c;
        ++i;
    }
    s[i] = '\0';
    reverse(s);
    printf("%s\n", reversedversion);
    return i;
}

/* copy: copy 'from' into 'to'; assume to is big enough */
void copy(char to[], char from[])
{
    int i;

    i = 0;
    while ((to[i] = from[i]) != '\0')
        ++i;
}

/* print longest input line */
int main()
{
    int len;               /* current line length */
    int max;               /* maximum length seen so far */
    char line[MAXLINE];    /* current input line */
    char longest[MAXLINE]; /* longest line saved here */
    extern char reversed[MAXLINE];
    max = 0;
    while ((len = get_line(line, MAXLINE)) > 0)
    {
        if (len > max)
        {
            max = len;
            copy(longest, line);
        }
    }
    if (max > 0) /* Only print the line if it's over 0 characters*/
    {            /* there was a line */
        reverse(longest);
        printf("%s\n", reversedversion);
    }
    else
    {
        printf("The line was too short to print, sorry bro\n");
    }
    return 0;
}
