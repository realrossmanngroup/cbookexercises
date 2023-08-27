#include <stdio.h>

#define OUTSIDEAWORD 0
#define MAKINGAWORD 1
main()
{
int c, WHEREAREWE, wcount;
WHEREAREWE = OUTSIDEAWORD;
wcount = 0;
    while ((c = getchar()) != EOF){
            if (c == '\n' || c == '\t' || c == ' '){
            WHEREAREWE = OUTSIDEAWORD;}
            else if (WHEREAREWE == OUTSIDEAWORD) {
            WHEREAREWE = MAKINGAWORD;
            ++wcount;}
    }
printf("There were %d new words",wcount);
}