/*Before I got the logic to remove stuff inside comments down inside of a multi-line string array char thing which I have never dealt with,
I wanted to make sure I had it down for a single character array. That is what I am doing here.*/

#include <stdio.h>
#include <string.h> /* Include the string.h library for strcpy function */

#define MAXLINELENGTH 1000
#define IN 0
#define OUT 1

void main()
{

  int w; /*used to keep track of where we are - IN or OUT of a comment? */
  w = 0;
  int x; /*use in for loop to count up in the nocomments array. this goes up when there are no comments */
  x = 0; /*declare x as 0*/
  int y; /*use in for loop to count up in the comments array - this goes up when there are no comments, and when there are comments*/
  y = 0; /*declare y as 0*/

  char nocomment[MAXLINELENGTH]; /*this is where I am storing the uncommented line after processing - just for debugging*/
  char comment[MAXLINELENGTH];   /*this is where I am storing the commented line before processing - just for debugging*/

  strcpy(comment, "This is the first line. I am coding. /* THIS IS TEXT INSIDE OF A COMMENT FIELD */ and now I have exited the comment field");

  /*write the logic for not iterating upwards when a /* is seen until a */ // is seen.
  while (comment[y] != '\0' && y < MAXLINELENGTH - 1)
  {
    w = OUT;
    if (comment[y] != '/' && comment[y + 1] != '*')
    {          /*if we do not see the first part of a comment, copy the commented array to the non-commented array directly*/
      w = OUT; /*we are OUT of a comment*/
      nocomment[x] = comment[y];
      x++;
      y++;
    }
    else /*if we DO see a comment, iterate the commented array up*/
    {
      y = y + 2;                                                                  /*move past the two characters that begin the comment*/
      w = IN;                                                                     /*we are IN a comment*/
      while (comment[y] != '*' && comment[y + 1] != '/' && y < MAXLINELENGTH - 1) /*this runs until we see the characters that end the comment*/
      {
        y++;                                            /* once we see the two characters that begin the comment, we iterate y for the commented array up without iterating x for the non-commented array*/
        if (comment[y] == '*' && comment[y + 1] == '/') /*Look out for the two characters that end the comment block!*/
        {
          y = y + 2; /* add 2 to y so that we skip over it in the commented array!*/
          w = OUT;   /*we are OUT of a comment again*/
          break;     /*break out of this loop, as we have broken out of the comment!*/
        }
      }
    }
  }

  printf("comment: %s\n\nno comment: %s\n\n", comment, nocomment); /*print the output - did I copy everything over properly?*/
}
