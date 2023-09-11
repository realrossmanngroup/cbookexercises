#include <stdio.h>

main()
{
	int c; /* variable containing what I typed. I made this an integer instead of a char because I inhaled too much leaded solder fumes as a boy, but it works anyway for some reason */
	while ((c = getchar()) != EOF) /* get a character */
		if (c == ' ') /* if it's a blank */
		{
			putchar(c); /* we'll let *ONE* blank slide! */
				while ((c = getchar()) == ' ') /* when getchar is a blank AGAIN(two blanks in a row)*/
				; /* don't do anything.  */
			/* putchar(c);  once you have killed the blanks, you are safe to put a character because it will not be a blank */
		}
		else putchar(c); /* if it's NOT a blank, fuck the loop above, just put the character(a, b, c etc.) onto the screen */
}


/* This is the algorithm I attempted to do above

	get character  C
        if character is blank {
        print character}
                if last character is blank, print any character not blank!
                else, putchar c
                go back to beginning    */
