#include <stdio.h>

// type text and figure out if getchar() != EOF is 1 or 0 by displaying on screen

void main()
{

int c = 0 //declare what is storing text i type

testcondition = 0; //declare variable that shows value of getchar != EOF

while ((testcondition = (c = getchar()) != EOF)){
	putchar(c); //show what i typed
		
		printf("\n getchar() != EOF is %d\n", testcondition); /* say whether
															 it's 1 or 0 */
	}
		printf("\n getchar() != EOF is %d\n", testcondition); /*do same
															once program ends
															so when ctrl-d is hit
															you see it turn to 0 */

}
