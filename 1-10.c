#include <stdio.h>

main()
{
int c, tab, backspace, backslash;

while ((c = getchar()) != EOF){
	if (c == '\t')
	printf("\\t");
	else if (c == '\b')
	printf("\\b");
	else if (c == '\\')
	printf("\\\\");
	else putchar(c);
	}
}	