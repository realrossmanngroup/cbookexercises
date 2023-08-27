#include <stdio.h>

#define NONBLANK 'a'

main()

{

int c, prevchar;

prevchar = NONBLANK;

	while ((c = getchar()) != EOF){
		if (c == ' ' && prevchar != ' '){
		putchar(c);
		prevchar = c;
	/*debug	printf("firstifworking"); */ 
		}
		else if (c != ' '){
		putchar(c);
		prevchar = c;
	/*debug	printf("elseisworking"); */ }
	}
}

