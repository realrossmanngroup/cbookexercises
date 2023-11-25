#include <stdio.h>
#include <string.h> /* Include the string.h library for strcpy function */

void main()
{

    char lines[100][1000]; /*string array*/
    char line0[100];
    char line1[100];

strcpy(line0, "This is the first line."); 
strcpy(line1, "This is the second line."); 

printf("line 0: %s \n\n line 1: %s \n\n line 1, third character: %c\n\n",line0, line1, line1[2]);
}