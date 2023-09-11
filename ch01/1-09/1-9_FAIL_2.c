#include <stdio.h>

#define NONBLANK 'a'

main()
{
        /* Replace blanks with 1 blank*/
	int c, lastc; /* define variables*/
        lastc = NONBLANK; /* set variable that will store blank equal to 0*/
        while((c = getchar()) != EOF){ /* get character from input*/
                if (c != ' ')     /* if it's not a blank*/
                        putchar(c);             /* print the character*/
                else if (lastc != ' ')  /*this is an else, which means
                                        this will happen if the last statement
                                        isn't true. the last statement is doing 
                                        something if c isn't a blank - the else means 
                                        c IS a blank. So, if C is a blank, **AND** 
                                        lastc is NOT a blank, put a character. But set lastc
                                        to being the input so it can re-test if it's a blank. */
                putchar(c);
                lastc = ' '; /* this was my code in error. I don't understand why this doesn't print
                                one blank, and then never print a blank again. Shouldn't the else if on
                                line 13 run, since c was a blank, see that lastc was set to 'a'(NONBLANK) on 
                                line 9, and then putcharc? Once this is done and it sets lastc to a blank i should
                                never get a blanka gain, but upon first run I should be able to get one blank*/
                        
                        
       
        }
}