#include <stdio.h>

#define IN_A_WORD 1
#define NOT_IN_WORD 0

void main(){

	
	int WHERE_ARE_WE;
	int c;
	int wordcount;
	
	wordcount = 0;
	WHERE_ARE_WE = NOT_IN_WORD;
	
	while ((c = getchar()) != EOF){
		if (((c >= 'A') && (c <= 'Z')) || ((c >= 'a') && (c <= 'z')) || (c == '\'')){
			WHERE_ARE_WE = IN_A_WORD;}
			else if (WHERE_ARE_WE != NOT_IN_WORD){
				WHERE_ARE_WE = NOT_IN_WORD;
				wordcount++;}
				else {
					continue;
				}
	
	}
	printf("\n\n You typed %d words! Good job.\n\n",wordcount);
	}


//PSUEDOCODE/BRAINSTORMING BELOW:

/*
We have to figure out if we are in a word. 

If a letter has been typed, we're in a word. We must account for both
capitalized & lowercase letters, using '' around the letter so the program
knows to check for the ASCII value of the letter, rather than a variable 
called A, B, C, etc that does not exist in my program. It is convenient
that ASCII's numbers that represent letters are in order so I can make the
if statement checking if I typed a letter nice and neat!

If anything that isn't a letter has been typed, we're likely outside of a word. 

There are special cases such as using apostrophes. Simply typing an apostrophe 
if the word's going to use one does not mean we have entered a separate
word. "word's" is not two words. We will account for this edge case, as well as
for capital & 


once a character between a & z has been hit, we are back in a word.

When we are OUT of a word is when we add to wordcount, 
BUT ONLY IF WE ARE NOT ALREADY OUTSIDE OF A WORD!!

*/

// WHAT IS WRONG WITH BOOK'S CODE:

/*
The book does not take into account that dashes and punctuation are not words.
This program I made will not count "----" or "&#^#" as a word. Anytime there is
a space put after a word, whether in the form of newline/tab/space, it thinks
that we're in a new word. Random junk is not a word though! Words are made up
of characters from the English language & alphabet. 
*/
