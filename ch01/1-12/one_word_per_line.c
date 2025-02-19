#include <stdio.h>
#include <stdlib.h>

#define IN_A_WORD 1
#define NOT_IN_WORD 0

void main(){

	
	int WHERE_ARE_WE;
	int c;
	int wordcount;
	char word[100];	//Where we store each word that is typed
	int charcount;	/*Where we keep track of length of each word so we know
					 how far into word[] we need to print for each word */
	wordcount = 0;
	charcount = 0;
	WHERE_ARE_WE = NOT_IN_WORD; //We start out not in a word
	
	//erase array that stores the typed word. or "initialize" but my brain isn't there yet
	for(int x = 0; x < 100; x++){ 
		word[0] = x;
	}
	
	//get text from user & assign to c while program is running
	while ((c = getchar()) != EOF){
		//if a normal character has been typed, we're in a word
		if (((c >= 'A') && (c <= 'Z')) || ((c >= 'a') && (c <= 'z')) || (c == '\'')){
			WHERE_ARE_WE = IN_A_WORD;
			word[charcount] = c;
			if(charcount < 98){
				charcount++;
			} else {
				exit(1);
				}}

	//if we're in a word but a space/enter/tab/anything else was hit, we're now out of a word
			else if (WHERE_ARE_WE != NOT_IN_WORD){
				WHERE_ARE_WE = NOT_IN_WORD;
				for(int charinword = 0; charinword < charcount; charinword++){
					printf("%c",word[charinword]);
				}
				printf("\n");
				charcount = 0;
				wordcount++;
				//erase array that stores the typed word.
				for(int x = 0; x < 100; x++){
					word[0] = x;
					}
				}
				/*If we are OUT of a word and have not typed a normal character,
				keep the program going without any change or doing anything. */
				else {
					continue;
				}
		}
	
	printf("\n\n You typed %d words! Good job.\n\n If this worked, each word was on a new line. :)\n\n",wordcount);
	
}

/*NEW BRAINSTORMING


To print one line at a time, we have to modify the
word counter program to STORE the word.
Once out of a word, it needs to print the contents of the word 
and a newline before it returns to in a word. 

THIS MEANS WE WILL DO THE FOLLOWING: 

1) Create a character array that can store the word

2) Count how many characters are in the word so that we know 
how long the for loop to print the word needs to be.
charcount should start at 0, and for loop must end
at < charcount rather than <= charcount 
since word[0] is first character. if a word is 
2 characters, word[1] will be the 2nd character 
and word[2] would print out of bounds nonsense. 

3) initialize char array charcount empty

4) make sure charcount[100] for 99 spaces 

5) make sure if word more than 98 characters we 
exit program just incase I do something dumb to retain memory safety
6) for loop to print the word with newline character
each time we are OUT of a word
7) initialize charcount as 0 before going back into a word.

*/