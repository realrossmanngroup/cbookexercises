#include <stdio.h>
#define MAXLINELENGTH 1000
#define MAXLINES 1000
#define MAXFILENAME 100

void main()
{

  int i;                                      /* use for looping to collect input from user */
  i = 0;                                      /* declare i as 0 */
  int j;                                      /*use for looping to spit file being read into string array*/
  j = 0;                                      /* declare j as 0 */
  int x;                                      /*use in for loop to count up in the nocomments array. this goes up when there are no comments */
  x = 0;                                      /*declare x as 0*/
  int y;                                      /*use in for loop to count up in the comments array - this goes up when there are no comments, and when there are comments*/
  y = 0;                                      /*declare y as 0*/
  int linewereon;                             /* keep track of what line we are on in our string array while copying input file to it*/
  linewereon = 0;                             /*initialize linewereon at 0*/
  int linelength;                             /*how long each line I am taking from my file is*/
  linelength = 0;                             /*initialize at 0 */
  char filename[MAXFILENAME];                 /* this will be where we store the name of our filename */
  char nocomment[MAXLINELENGTH];              /*this is where I am storing the uncommented line after processing - just for debugging*/
  char comment[MAXLINELENGTH;]                /*this is where I am storing the commented line before processing - just for debugging*/
      char filetempcontents[MAXLINELENGTH];   /*this is where we store the text of our file as we read it line by line temporarily */
  char filecontents[MAXLINES][MAXLINELENGTH]; /*array of strings we will store the file in*/
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

  FILE *program = fopen(filename, "r"); /*open file specified above and assign to *program pointer */

  printf("The filename you want me to open is %s\n\n", filename); /*Confirm I am opening the correct file*/

  if (program == NULL)
  { /*error handling if it cannot open the file*/
    perror("Error opening file");
  }
  else
  {
    printf("%p\n\n", (void *)program); /*tell me the file as a memory address if it did open*/
  }

  while (fgets(filetempcontents, MAXLINELENGTH, program) != NULL)
  {
    linelength = 0;
    while (filetempcontents[linelength] != '\0')
    {
      linelength++;
    }
    for (int x = 0; x <= linelength; x++) /*copy the contents of each line of the file over to a line in our string array*/
    {
      filecontents[linewereon][x] = filetempcontents[x];
    }
    linewereon++; /* each time the while loop loops we're on a new line, so iterate the line we're on in the string array */
  }
  /* printf("%s is the contents of my program within the while loop DEBUGOUTPUT \n\n", filecontents); /*for debugging*/

  for (int x = 0; x < linewereon; x++) /*this prints the file I loaded into my string array just to make sure I stored it properly*/
  {
    printf("%s", filecontents[x]); /*print the program */
  }
}
