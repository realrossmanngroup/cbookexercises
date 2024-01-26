#include <stdio.h>

#define NONBLANK 'a'

int main(void) {
	
	int c, prevchar;
	prevchar = NONBLANK;

	while ((c = getchar()) != EOF)
	{
		if (c == ' ' && prevchar == ' ') {
			continue;
		}
		
		putchar(c);
		prevchar = c;
		/*debug	printf("elseisworking"); */ 
	}
}
