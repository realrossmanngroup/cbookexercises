#include <stdio.h>
#define MAXSIZE 100

void main()
{

int i; /* use for looping to collect input from user */
i = 0; /* declare i as 0 */
char filename[100]; /* this will be where we store the name of our filename */
printf("What is the name of the file you wish to remove comments from in this directory?\n\n"); 
while((i < 98) && (filename[i] = getc(stdin)) != '\n') { /* have user type in filename */
i++;
}

printf("i is equal to %d DEBUGOUTPUT \n\n",i); /*for debugging */
filename[i +1] = '\0'; /* null terminate my input so it works */

FILE *program = fopen(filename, "r");

/* FILE *program = fopen("1-23_delete.c", "r"); */


printf("The filename you want me to open is %s\n\n",filename);

if (program == NULL) {
	perror("Error opening file"); }
else{
printf("%p\n\n",(void *)program);}

for (int x = 0; x < (i + 2); x++){ /*debug, figure out wtf is wrong with my filename */
printf("%c\n",filename[x]);
if (filename[x] == '\\0') {
printf("\0");
}
} 

}
