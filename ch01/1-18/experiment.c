#include <stdio.h>

int main()
{

char s[12];

s[0] = 'h';
s[1] = 'e';
s[2] = 'l';
s[3] = 'l';
s[4] = 'o';
/* s[5] = ' '; */
s[6] = 'w';
s[7] = 'o';
s[8] = 'r';
s[9] = 'l';
s[10] = 'd';

printf("this is going to print the full char array: %s\n",s);
printf("this is going to print only the stuff after the blank in hello world we neglected to store to s[5] in the char array, %c%c%c%c%c\n",s[6], s[7], s[8], s[9], s[10]);

}

