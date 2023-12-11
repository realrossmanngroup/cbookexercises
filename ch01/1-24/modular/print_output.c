#include <stdio.h>
#include "definitions.h"

// FUNCTION TO PRINT THE LOCATION OF THE ERRORS IN SYNTAX OF CODE AFTER FINDING THEM

int printerrors(int ifthisis0youclosedit[], int maxcount, int openline[], int opencolumn[],
                int closeline[], int closecolumn[], int extraclosedtrackingarray[], int maxclosed,
                char openchar, char closechar)
{
    int sum_open_errors = 0;		
    int sum_closed_errors = 0;		
    int sum_errors = 0;

    for (int whichp = 0; whichp <= maxcount; whichp++)
    {
        if (ifthisis0youclosedit[whichp] != 0)
        {
            printf("There's a mismatched %c on line %d: \n\n", openchar, openline[whichp] + 1);
            int endofline = 0;
            while ((program[openline[whichp]][endofline] != '\0') && (endofline < MAXCHARS - 2))
            {
		// printf("DEBUGline %d: endofline is %d, program[openline[whichp]][endofline] is program[%d][%d] is %c and program[openline[whichp]][endofline + 1] is program[%d][%d] is %c\n", __LINE__, endofline, openline[whichp], endofline, program[openline[whichp]][endofline], openline[whichp], endofline + 1, program[openline[whichp]][endofline + 1]);
                endofline++;
            }
		// printf("%d debugoutput ifthisis0youclosedit[%d] is %d\n", __LINE__, whichp, ifthisis0youclosedit[whichp]);
            for (int charsforcontext = (opencolumn[whichp] >= 10 ? opencolumn[whichp] - 10 : 0); charsforcontext < (opencolumn[whichp] <= endofline - 11 ? opencolumn[whichp] + 10 : endofline); charsforcontext++)
            {
                printf("%c", program[openline[whichp]][charsforcontext]);
            }
            printf("\n\nLook for the code above on line %d and tell me if you find your problem with the location of the %c characters. \n\n", openline[whichp] + 1, openchar);		// make it neat
        }
    }

    for (int whichp = 0; whichp <= maxclosed; whichp++)
    {
        if (extraclosedtrackingarray[whichp] != 0)
        {
            printf("There's a mismatched %c on line %d: \n\n", closechar, closeline[whichp] + 1);
            int endofline = 0;
            while ((program[closeline[whichp]][endofline] != '\0') && (endofline < MAXCHARS - 2))
            {
		// printf("DEBUG %d: endofline is %d, program[closeine[whichp]][endofline] is program[%d][%d] is %c and program[closeline[whichp]][endofline + 1] is program[%d][%d] is %c\n", __LINE__, endofline, closeline[whichp], endofline, program[closeline[whichp]][endofline], closeline[whichp], endofline + 1, program[closeline[whichp]][endofline + 1]);
                endofline++;
            }
		// printf("DEBUGOUTPUT line %d endofline is %d\n", __LINE__, endofline);
		// printf("%d debugoutput extraclosedtrackingarray[%d] is %d\n", __LINE__, whichp, extraclosedtrackingarray[whichp]);
            for (int charsforcontext = (closecolumn[whichp] >= 10 ? closecolumn[whichp] - 10 : 0); charsforcontext < (closecolumn[whichp] <= endofline - 11 ? closecolumn[whichp] + 10 : endofline); charsforcontext++)
            {
                printf("%c", program[closeline[whichp]][charsforcontext]);
		// printf("debugline %d endofline is %d, charsforcontext is %d, closecolumn[whichp] is %d\n", __LINE__, endofline, charsforcontext, closecolumn[whichp]);
            }
            printf("\n\nLook for the code above on line %d and tell me if you find your problem with the location of the %c characters. \n\n", closeline[whichp] + 1, closechar); // make it neat
        }
    }

    for (int i = 0; i <= maxcount; i++)
    {
        sum_open_errors += ifthisis0youclosedit[i];
    }
    for (int i = 0; i <= maxclosed; i++)
    {
        sum_closed_errors += extraclosedtrackingarray[i];
    }
    if ((sum_open_errors + sum_closed_errors) == 0)
        printf("It looks like your %c and %c are balanced just fine! No errors here.\n", openchar, closechar);
}

