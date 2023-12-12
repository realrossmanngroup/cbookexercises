#ifndef SYNTAX_TRACKING_H
#define SYNTAX_TRACKING_H

int stringinorout(int keeptrackofstring, int keeptrackofchar, char currentchar, char previouschar, int comment);

void trackchars(char openchar, char closechar, int *counter, int *closecounter,
                int *maxcount, int *maxclosed, int ifthisis0youclosedit[], int extraclosedtrackingarray[],
                int opencolumn[], int openline[], int closecolumn[], int closeline[]);

void trackquotes(char openchar, char closechar, int *counter, int *closecounter,
                 int *maxcount, int *maxclosed, int ifthisis0youclosedit[], int extraclosedtrackingarray[],
                 int opencolumn[], int openline[], int closecolumn[], int closeline[]);

#endif
