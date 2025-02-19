#include <stdio.h>

// count character types entered

void main() {

  int c = 0; // declare what is storing text i type
  int newline = 1;
  int newtab = 0;
  int newblank = 0;

  while ((c = getchar()) != EOF) {
    if (c == '\n') {
      newline++;
    }
    if (c == '\t') {
      newtab++;
    }
    if (c == ' ') {
      newblank++;
    }
  }

  printf("\nline count: %d\ntab count: %d\nblank count: %d\n", newline, newtab,
         newblank);
}
