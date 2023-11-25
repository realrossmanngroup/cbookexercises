#include <stdio.h>
#define MAXSIZE 100

void main() {

  int i;              /* use for looping to collect input from user */
  i = 0;              /* declare i as 0 */
  char filename[100]; /* this will be where we store the name of our filename */
  printf("What is the name of the file you wish to remove comments from in "
         "this directory?\n\n");
  while ((i < 98) &&
         (filename[i] = getc(stdin)) != EOF) { /* have user type in filename */
    if (filename[i] != '\n') {
      printf("%d is i, filename[%d] is %c before iteration DEBUGOUTPUT\n\n", i,
             i, filename[i]); /*for debugging */
      i++;
      printf("%d is i, filename[%d] is %c after iteration DEBUGOUTPUT\n\n", i,
             i, filename[i]); /* for debugging*/
    } else {
      filename[i] = '\0';
	  printf("filename[%d] is %c DEBUGOUTPUT \n\n",i, filename[i]); /*for debugging*/
      break;
    }
  }

  printf("i is equal to %d DEBUGOUTPUT \n\n", i); /*for debugging */
  /* filename[i] = '\0'; /* null terminate my input so it works */

  FILE *program = fopen(filename, "r");

  printf("The filename you want me to open is %s\n\n", filename);

  if (program == NULL) {
    perror("Error opening file");
  } else {
    printf("%p\n\n", (void *)program);
  }

  for (int x = 0; x < (i + 2);
       x++) { /*debug, figure out wtf is wrong with my filename */
    if (filename[x] == '\0') {
      printf("\\0");
    } else {
      printf("%c\n", filename[x]);
    }
  }
}
