#include <stdio.h>
#include <stdlib.h>

// What to set `WHERE_ARE_WE` to if in or out of word
#define IN_A_WORD 1
#define NOT_IN_WORD 0

void main(){

	
	int WHERE_ARE_WE;	// Are we in a word, or not in a word?
	int c;				// What stores inpu text			
	int wordcount;		// Count of words in input; iterate w/ each typed word
	char typedword[101];	// Where we store each typed word
	int charcount;
	
	
	wordcount = 0;
	charcount = 0;
	for (int wordarray = 0; wordarray < 100; wordarray++){
		typedword[wordarray] = 0;}
		
	WHERE_ARE_WE = NOT_IN_WORD;	// Start off not in a word
	
	while ((c = getchar()) != EOF){
		if (((c >= 'A') && (c <= 'Z')) || ((c >= 'a') && (c <= 'z')) || (c == '\'')){
			WHERE_ARE_WE = IN_A_WORD;
			if(charcount < 98){
			typedword[charcount] = c;
			charcount++;}
			else{
				exit(1);
				}
			}
			else if (WHERE_ARE_WE != NOT_IN_WORD){
				WHERE_ARE_WE = NOT_IN_WORD;
				wordcount++;
				for (int x = 0; x <= charcount; x++){
					printf("\033[0;32m"); 
					printf("%c",typedword[x]);}
					charcount = 0;
					printf("\n");
						for (int wordarray = 0; wordarray < 100; wordarray++){
							typedword[wordarray] = 0;}
						}
				else {
					continue;
				}
	
	}
	printf("\n\n You typed %d words! Good job.\n\n",wordcount);
	}

/* Use word count program, add following features:
 * 1) Count each CHARACTER and store as a variable. 
 * 2) While in a word, place each typed character into a char array we will use to store the word.
 * 3) When word is over and we are not in a word:
 * 	a) Place `WHERE_ARE_WE` not in a word.
 * 	b) Iterate up the word count, ++.
 * 	c) For loop to print the char array with the word, WITH A NEWLINE CHARACTER!
 * 	d) Reset the character count to 0. 
 * 	b) P
*/
