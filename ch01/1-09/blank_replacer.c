#include <stdio.h>

void main() {

  int c = 0;      // Where we store input from keyboard
  int blanks = 0; // how we count blanks
  while ((c = getchar()) != EOF) {

    if (c != ' ') {
      putchar(c);
      blanks = 0;
    } else if (blanks == 0) {
      putchar(c);
      blanks++;
    }
  }
}

/*
if c is not a blank put it there
* if c is a blank, put a character there, but up blanks counter.
* as long as blanks counter is more than 1, will not put blanks.
* once non-blank returns, set blanks counter to 0 so that it allows future
blanks through
* */
