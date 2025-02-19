#include <stdio.h>
#include <stdlib.h>

#define IN_A_WORD 1
#define NOT_IN_WORD 0

void main(){

	
	int WHERE_ARE_WE;
	int c;
    int wordlength[100]; //Where we keep track of how many words are wordlength[x] length, with x being the length of a word
	int charcount;	//Where we keep track of length of each word
	charcount = 0;
	WHERE_ARE_WE = NOT_IN_WORD; //We start out not in a word
		
	//get text from user & assign to c while program is running
	while ((c = getchar()) != EOF){
		//if a normal character has been typed, we're in a word
		if (((c >= 'A') && (c <= 'Z')) || ((c >= 'a') && (c <= 'z')) || (c == '\'')){
			WHERE_ARE_WE = IN_A_WORD;
			if(charcount < 98){
				charcount++;
			} else {
				exit(1);
				}}

	//condition for when we've exited a word
			else if (WHERE_ARE_WE != NOT_IN_WORD){
				WHERE_ARE_WE = NOT_IN_WORD; 
				}
				charcount = 0;
				}
				/*If we are OUT of a word and have not typed a normal character,
				keep the program going without any change or doing anything. */
				else {
					continue;
				}
		}
	
	


/*NEW BRAINSTORMING

1) to count number of each word length, once word done, before resetting
charcount to 0 you have to iterate wordlength[charcount]

2) Make sure that charcount can't go over 98 everywhere for memory security

3) add loop that, for each wordlength[x] makes a # for that amount 

4) add newline at the end of each.

1) No need to store a word anymore, remove this
*/