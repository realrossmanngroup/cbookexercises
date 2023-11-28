

#include <stdio.h>
#define MAXLINELENGTH 1000
#define MAXLINES 1000
#define MAXFILENAME 100
#define IN 0    
#define OUT 1   
#define YES 1   
#define NO 0    
#define FALSE 0 
#define TRUE 1  
int linewereon = 0;                      
char comment[MAXLINES][MAXLINELENGTH];   



int stringinorout(int keeptrackofstring, int keeptrackofchar, char currentchar, char previouschar, int y)
{
    
    if (currentchar == '\"' && (y == 0 || previouschar != '\\'))
    {
        keeptrackofstring = (keeptrackofstring == OUT) ? IN : OUT;
    }

    
    if (currentchar == '\'' && (y == 0 || previouschar != '\\'))
    {
        if (keeptrackofstring == OUT)
        { 
            keeptrackofchar = (keeptrackofchar == OUT) ? IN : OUT;
        }
    }

    
    if (currentchar == '\\' && (y > 0 && (previouschar == '\\' || previouschar == '\'')))
    {
        y++; 
    }

    return keeptrackofstring; 
}



FILE *openfile()
{

    char inputfilename[MAXFILENAME]; 
    int i = 0;                       
    
    printf("What is the name of the INPUT file you wish to remove comments from in this directory?\n\n");
    while ((i < MAXFILENAME - 1) && (inputfilename[i] = getc(stdin)) != EOF)
    { 
        if (inputfilename[i] != '\n')
        { 
            i++;
        }
        else
        {
            inputfilename[i] = '\0'; 
            break;                   
        }
    }

    

    FILE *program = fopen(inputfilename, "r");                           
    printf("The filename you want me to open is %s\n\n", inputfilename); 

    if (program == NULL)
    { 
        perror("Error opening file");
    }
    else
    {
        printf("%p is open, that's filename: %s\n\n", (void *)program, inputfilename); 
        return program;                                                                
    }
}



FILE *savefile()
{

    char outputfilename[MAXFILENAME]; 
    int i = 0;                        
    
    printf("What is the name of the OUTPUT file you wish to save your uncommented code to in this directory?\n\n");
    while ((i < MAXFILENAME - 1) && (outputfilename[i] = getc(stdin)) != EOF)
    { 
        if (outputfilename[i] != '\n')
        { 
            i++;
        }
        else
        {
            outputfilename[i] = '\0'; 
            break;                    
        }
    }

    

    FILE *outputfile = fopen(outputfilename, "w");                              
    printf("The filename you want me to save to is is %s\n\n", outputfilename); 

    if (outputfile == NULL)
    { 
        perror("Error creating file");
    }
    else
    {
        printf("%p is open, that's filename: %s and is ready for writing\n\n", (void *)outputfile, outputfilename); 
        return outputfile;                                                                                          
    }
}



char filetoarray(FILE *file)
{
char array[MAXLINES][MAXLINELENGTH]; 
    int linelength = 0; 

    int wheretoplacenullterminator = 0; 

    char filetempcontents[MAXLINELENGTH]; 

    while (fgets(filetempcontents, MAXLINELENGTH, file) != NULL)
    { 
        linelength = 0;
        while (filetempcontents[linelength] != '\0')
        {
            linelength++;
        }
        for (int x = 0; x <= linelength; x++) 
        {
            comment[linewereon][x] = filetempcontents[x];
            wheretoplacenullterminator = x;
        }
        comment[linewereon][wheretoplacenullterminator] = '\0'; 

        linewereon++; 
    }
}

void main()
{
    int j = 0;                               
    int x = 0;                               
    int w = OUT;                             
    int stringliteral;                       
    int charliteral;                         
    int y = 0;                               
    int singlelinecomment = NO;              
    int multilinecommentend = FALSE;         
    char nocomment[MAXLINES][MAXLINELENGTH]; 

    FILE *inputfile = openfile(); 
    filetoarray(inputfile); 
    

        linewereon++; 

    

    printf("\nTHIS IS THE COMMENTED, UNPROCESSED VERSION OF THE PROGRAM!\n\n");
    for (int x = 0; x < linewereon; x++) 
    {

        printf("%s", comment[x]);
    } 

    

    

    for (int a = 0; a <= linewereon; a++, x = 0, y = 0)
    {
        stringliteral = OUT; 

        if (singlelinecomment == YES)
        {
            singlelinecomment = NO;
            continue;
        }
        if (w == OUT)
        { 

             
            while ((comment[a][y] != '\0') && (y < MAXLINELENGTH - 1))
            {
                stringliteral = stringinorout(stringliteral, charliteral, comment[a][y], comment[a][y - 1], y); 
                if (((comment[a][y] == '/') && (comment[a][y + 1] == '/')) && (stringliteral == OUT))           
                {
                    printf("DEBUGOUTPUT line number: %d stringliteral is %d I DETECTED A SINGLE LINE COMMENT AT comment[%d][%d] which is %c (should be a slash) and comment[%d][%d] which is %c (should be a slash)! w is %d\n", __LINE__, stringliteral, a, y, comment[a][y], a, y + 1, comment[a][y + 1], w); 
                                                                                                                                                                                                                                                                                                                
                    nocomment[a][x] = '\n';                                                                                                                                                                                                                                                                     
                    nocomment[a][x + 1] = '\0';                                                                                                                                                                                                                                                                 
                    break;                                                                                                                                                                                                                                                                                      
                }
                else if ((comment[a][y] != '/') && (comment[a][y + 1] != '*'))
                {            
                    w = OUT; 
                    nocomment[a][x] = comment[a][y];
                    printf("DEBUGOUTPUT line number: %d copying stuff from comment to nocomment on line 1, NOT in comment: stringliteral is %d, w is %d, nocomment[%d][%d] is %c, comment[%d][%d] is %c, comment[%d][%d] is %c \n", __LINE__, stringliteral, w, a, x, nocomment[a][x], a, y, comment[a][y], a, y + 1, comment[a][y + 1]); 
                    x++;
                    y++;
                }
                else if (((comment[a][y] == '/') && (comment[a][y + 1] == '*')) && (stringliteral == OUT))                    
                {                                                                                                             
                    y = y + 2;                                                                                                
                    w = IN;                                                       
                    while ((w != OUT) && (y < MAXLINELENGTH - 2) && ((comment[a][y] != '\0') || (comment[a][y + 1] != '\0'))) 
                    {
                        stringliteral = stringinorout(stringliteral, charliteral, comment[a][y], comment[a][y - 1], y); 
                        w = IN;
                        printf("DEBUGOUTPUT line number: %d inside a MULTILINE comment on line 1: stringliteral is %d, w is %d, nocomment[%d][%d] is %c, comment[%d][%d] is %c, comment[%d][%d] is %c \n", __LINE__, stringliteral, w, a, x, nocomment[a][x], a, y, comment[a][y], a, y + 1, comment[a][y + 1]); 

                        y++;
                        if (((y == MAXLINELENGTH - 3) || (comment[a][y] == '\0') || (comment[a][y + 1] == '\0')) && (stringliteral == OUT))
                        { 
                            nocomment[a][x] = '\n';
                        }                                                                                     
                        if (((comment[a][y] == '*') && (comment[a][y + 1] == '/')) && (stringliteral == OUT)) 
                        {
                            printf("DEBUGOUTPUT line number: %d end of multiline comment on line 1: stringliteral is %d, w is %d, nocomment[%d][%d] is %c, comment[%d][%d] is %c, comment[%d][%d] is %c \n", __LINE__, stringliteral, w, a, x, nocomment[a][x], a, y, comment[a][y], a, y + 1, comment[a][y + 1]); 
                            y = y + 2;                                                                                                                                                                                                                                                                             
                            w = OUT;                                                                                                                                                                                                                                                                               
                        }
                    }
                }
                else if ((comment[a][y] != '/') && (comment[a][y + 1] == '*'))
                {            
                    w = OUT; 
                    nocomment[a][x] = comment[a][y];
                    printf("DEBUGOUTPUT line number: %d outside comment on line 1, asterisk on right: stringliteral is %d, w is %d, nocomment[%d][%d] is %c, comment[%d][%d] is %c, comment[%d][%d] is %c \n", __LINE__, stringliteral, w, a, x, nocomment[a][x], a, y, comment[a][y], a, y + 1, comment[a][y + 1]); 
                    x++;
                    y++;
                }
                else if ((comment[a][y] == '*') && (comment[a][y + 1] != '/'))
                {            
                    w = OUT; 
                    nocomment[a][x] = comment[a][y];
                    printf("DEBUGOUTPUT line number: %d outside comment on line 1, asterisk on left: stringliteral is %d, w is %d, nocomment[%d][%d] is %c, comment[%d][%d] is %c, comment[%d][%d] is %c \n", __LINE__, stringliteral, w, a, x, nocomment[a][x], a, y, comment[a][y], a, y + 1, comment[a][y + 1]); 
                    x++;
                    y++;
                }
                else if ((comment[a][y] == '/') && ((comment[a][y + 1] != '*') || (comment[a][y + 1] != '/')))
                {            
                    w = OUT; 
                    nocomment[a][x] = comment[a][y];
                    printf("DEBUGOUTPUT line number: %d outside comment on line 1, slash on left: stringliteral is %d, w is %d, nocomment[%d][%d] is %c, comment[%d][%d] is %c, comment[%d][%d] is %c \n", __LINE__, stringliteral, w, a, x, nocomment[a][x], a, y, comment[a][y], a, y + 1, comment[a][y + 1]); 
                    x++;
                    y++;
                }
                else if ((comment[a][y] != '/') || ((comment[a][y] != '*') && (comment[a][y + 1] == '/')))
                {            
                    w = OUT; 
                    nocomment[a][x] = comment[a][y];
                    printf("DEBUGOUTPUT line number: %d outside comment on line 1, slash on right: stringliteral is %d, w is %d, nocomment[%d][%d] is %c, comment[%d][%d] is %c, comment[%d][%d] is %c \n", __LINE__, stringliteral, w, a, x, nocomment[a][x], a, y, comment[a][y], a, y + 1, comment[a][y + 1]); 
                    x++;
                    y++;
                }

                else
                {
                    printf("If you're here, you're truly lost: I don't know what to tell you\n");
                    break; 
                }
            }
        }
        else
        {
            while ((y < MAXLINELENGTH - 2) && ((comment[a][y] != '\0') || (comment[a][y + 1] != '\0')))
            {

                if (w == IN)
                {
                    
                    while ((y < MAXLINELENGTH - 2) && ((comment[a][y] != '\0') || (comment[a][y + 1] != '\0')) && (w != OUT)) 
                    {
                        stringliteral = stringinorout(stringliteral, charliteral, comment[a][y], comment[a][y - 1], y); 

                        w = IN;
                        printf("DEBUGOUTPUT line number: %d INSIDE multiline comment on line 2: stringliteral is %d, w is %d, nocomment[%d][%d] is %c, comment[%d][%d] is %c, comment[%d][%d] is %c \n", __LINE__, stringliteral, w, a, x, nocomment[a][x], a, y, comment[a][y], a, y + 1, comment[a][y + 1]);
                        y++;                                                                                  
                        if (((comment[a][y] == '/') && (comment[a][y + 1] == '/')) && (stringliteral == OUT)) 
                        {

                            printf("DEBUGOUTPUT line number: %d WE FOUND A SINGLELINE // COMMENT INSIDE multiline comment on line 2, stringliteral is %d, w is %d, nocomment[%d][%d] is %c, comment[%d][%d] is %c, comment[%d][%d] is %c \n", __LINE__, stringliteral, w, a, x, nocomment[a][x], a, y - 1, comment[a][y - 1], a, y, comment[a][y]);
                            w = IN;
                            y = y + 1; 
                            w = IN;
                        }
                        if ((comment[a][y - 1] == '*' && comment[a][y] == '/') && (stringliteral == OUT)) 
                        {
                            printf("DEBUGOUTPUT line number: %d end of multiline comment on line 2: stringliteral is %d, w is %d, nocomment[%d][%d] is %c, comment[%d][%d] is %c, comment[%d][%d] is %c \n", __LINE__, stringliteral, w, a, x, nocomment[a][x], a, y, comment[a][y], a, y + 1, comment[a][y + 1]);
                            
                            y = y + 2; 
                            w = OUT;   
                            printf("DEBUGOUTPUT line number: %d we skipped over the multiline comment on line 2: stringliteral is %d, w is %d, nocomment[%d][%d] is %c, comment[%d][%d] is %c, comment[%d][%d] is %c \n", __LINE__, stringliteral, w, a, x, nocomment[a][x], a, y, comment[a][y], a, y + 1, comment[a][y + 1]);
                        }
                    }
                }
                else
                {  
                    while ((comment[a][y] != '\0') && (y < MAXLINELENGTH - 1))
                    {
                        stringliteral = stringinorout(stringliteral, charliteral, comment[a][y], comment[a][y - 1], y); 

                        if (((comment[a][y] == '/') && (comment[a][y + 1] == '/')) && (stringliteral == OUT)) 
                        {
                            printf("DEBUGOUTPUT line number: %d stringliteral is %d I DETECTED A SINGLE LINE COMMENT AT comment[%d][%d] which is %c (should be a slash) and comment[%d][%d] which is %c (should be a slash)! w is %d\n", __LINE__, stringliteral, a, y, comment[a][y], a, y + 1, comment[a][y + 1], w);
                            singlelinecomment = YES;
                            nocomment[a][x] = '\n';     
                            nocomment[a][x + 1] = '\0'; 
                            break;                      
                        }
                        else if ((comment[a][y] != '/') && (comment[a][y + 1] != '*'))
                        {            
                            w = OUT; 
                            nocomment[a][x] = comment[a][y];
                            printf("DEBUGOUTPUT line number: %d stringliteral is %d copying stuff from comment to nocomment on line 2, NOT in comment: w is %d, nocomment[%d][%d] is %c, comment[%d][%d] is %c, comment[%d][%d] is %c \n", __LINE__, stringliteral, w, a, x, nocomment[a][x], a, y, comment[a][y], a, y + 1, comment[a][y + 1]);
                            x++;
                            y++;
                        }
                        else if (((comment[a][y] == '/') && (comment[a][y + 1] == '*')) && (stringliteral == OUT))                    
                        {                                                                                                             
                            y = y + 2;                                                                                                
                            w = IN;                                                       
                            while ((w != OUT) && (y < MAXLINELENGTH - 2) && ((comment[a][y] != '\0') || (comment[a][y + 1] != '\0'))) 
                            {
                                stringliteral = stringinorout(stringliteral, charliteral, comment[a][y], comment[a][y - 1], y); 

                                w = IN;
                                printf("DEBUGOUTPUT line number: %d inside a MULTILINE comment on line 2: stringliteral is %d, w is %d, nocomment[%d][%d] is %c, comment[%d][%d] is %c, comment[%d][%d] is %c \n", __LINE__, stringliteral, w, a, x, nocomment[a][x], a, y, comment[a][y], a, y + 1, comment[a][y + 1]);

                                y++;
                                if (((y == MAXLINELENGTH - 3) || (comment[a][y] == '\0') || (comment[a][y + 1] == '\0')) && (stringliteral == OUT))
                                { 
                                    nocomment[a][x] = '\n';
                                }                                                                                     
                                if (((comment[a][y] == '*') && (comment[a][y + 1] == '/')) && (stringliteral == OUT)) 
                                {
                                    printf("DEBUGOUTPUT line %d: end of multiline comment on line 2: stringliteral is %d, w is %d, nocomment[%d][%d] is %c, comment[%d][%d] is %c, comment[%d][%d] is %c \n", __LINE__, stringliteral, w, a, x, nocomment[a][x], a, y, comment[a][y], a, y + 1, comment[a][y + 1]);
                                    y = y + 2; 
                                    w = OUT;   
                                }
                            }
                        }
                        else if ((comment[a][y] != '/') && (comment[a][y + 1] == '*'))
                        {            
                            w = OUT; 
                            nocomment[a][x] = comment[a][y];
                            printf("DEBUGOUTPUT line %d: outside comment on line 2, asterisk on right: stringliteral is %d, w is %d, nocomment[%d][%d] is %c, comment[%d][%d] is %c, comment[%d][%d] is %c \n", __LINE__, stringliteral, w, a, x, nocomment[a][x], a, y, comment[a][y], a, y + 1, comment[a][y + 1]);
                            x++;
                            y++;
                        }
                        else if ((comment[a][y] == '*') && (comment[a][y + 1] != '/'))
                        {            
                            w = OUT; 
                            nocomment[a][x] = comment[a][y];
                            printf("DEBUGOUTPUT line %d: outside comment on line 2, asterisk on left: stringliteral is %d, w is %d, nocomment[%d][%d] is %c, comment[%d][%d] is %c, comment[%d][%d] is %c \n", __LINE__, stringliteral, w, a, x, nocomment[a][x], a, y, comment[a][y], a, y + 1, comment[a][y + 1]);
                            x++;
                            y++;
                        }
                        else if ((comment[a][y] == '/') && ((comment[a][y + 1] != '*') || (comment[a][y + 1] != '/')))
                        {            
                            w = OUT; 
                            nocomment[a][x] = comment[a][y];
                            printf("DEBUGOUTPUT line %d: outside comment on line 2, slash on left: stringliteral is %d, w is %d, nocomment[%d][%d] is %c, comment[%d][%d] is %c, comment[%d][%d] is %c \n", __LINE__, stringliteral, w, a, x, nocomment[a][x], a, y, comment[a][y], a, y + 1, comment[a][y + 1]);
                            x++;
                            y++;
                        }
                        else if ((comment[a][y] != '/') || ((comment[a][y] != '*') && (comment[a][y + 1] == '/')))
                        {            
                            w = OUT; 
                            nocomment[a][x] = comment[a][y];
                            printf("DEBUGOUTPUT line %d: outside comment on line 2, asterisk on right: stringliteral is %d, w is %d, nocomment[%d][%d] is %c, comment[%d][%d] is %c, comment[%d][%d] is %c \n", __LINE__, stringliteral, w, a, x, nocomment[a][x], a, y, comment[a][y], a, y + 1, comment[a][y + 1]);
                            x++;
                            y++;
                        }

                        else
                        {
                            printf("If you're here, you're truly lost: I don't know what to tell you\n");
                            break; 
                        }
                    }
                }
            }
        }
    }

    

    FILE *savefilenocomments = savefile();

    for (int x = 0; x < linewereon; x++) 
    {
        fprintf(savefilenocomments, "%s", nocomment[x]);
    }

    

    printf("\nTHIS IS THE UN-COMMENTED, PROCESSED VERSION OF THE PROGRAM!\n\n");

    for (int x = 0; x < linewereon; x++) 
    {
        printf("%s", nocomment[x]);
    } 

    fclose(inputfile);
    fclose(savefilenocomments);
}
