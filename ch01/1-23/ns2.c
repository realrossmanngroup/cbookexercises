
#include <stdio.h>
#define MAXLINELENGTH 1000
#define MAXLINES 1000
#define MAXFILENAME 100
#define IN 0  
#define OUT 1 
#define YES 1 
#define NO 0  


FILE *openfile()
{

    char inputfilename[MAXFILENAME]; 
    int i = 0;                       
    
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

void main()
{
    int j = 0;                               
    int x = 0;                               
    int w = OUT;                             
    int y = 0;                               
    int linewereon = 0;                      
    int wheretoplacenullterminator = 0;      
    int linelength = 0;                      
    int singlelinecomment = NO;              
    char nocomment[MAXLINES][MAXLINELENGTH]; 
    char comment[MAXLINES][MAXLINELENGTH];   
    char filetempcontents[MAXLINELENGTH];    

    FILE *inputfile = openfile(); 

    
    while (fgets(filetempcontents, MAXLINELENGTH, inputfile) != NULL)
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

    
    printf("\nTHIS IS THE COMMENTED, UNPROCESSED VERSION OF THE PROGRAM!\n\n");
    for (int x = 0; x < linewereon; x++) 
    {

        printf("%s", comment[x]);
    } 

    

    
    for (int a = 0; a <= linewereon; a++, x = 0, y = 0)
    {
        if (singlelinecomment == YES)
        {
            singlelinecomment = NO;
            continue;
        }
        if (w == OUT)
        { 

             
            {
                if ((comment[a][y] == '/') && (comment[a][y + 1] == '/')) 
                {
                    printf("DEBUGOUTPUT I DETECTED A SINGLE LINE COMMENT AT comment[%d][%d] which is %c (should be a slash) and comment[%d][%d] which is %c (should be a slash)! w is %d\n", a, y, comment[a][y], a, y + 1, comment[a][y + 1], w); 
                    singlelinecomment = YES;
                    nocomment[a][x] = '\n'; 
                    break;                  
                }
                else if ((comment[a][y] != '/') && (comment[a][y + 1] != '*'))
                {            
                    w = OUT; 
                    nocomment[a][x] = comment[a][y];
                    printf("DEBUGOUTPUT copying stuff from comment to nocomment on line 1, NOT in comment: w is %d, nocomment[%d][%d] is %c, comment[%d][%d] is %c, comment[%d][%d] is %c \n", w, a, x, nocomment[a][x], a, y, comment[a][y], a, y + 1, comment[a][y + 1]); 
                    x++;
                    y++;
                }
                else if ((comment[a][y] == '/') && (comment[a][y + 1] == '*'))                                                                                            
                {                                                                                                                                                         
                    y = y + 2;                                                                                                                                            
                    w = IN;                                                                                                   
                    while (((comment[a][y] != '*') || (comment[a][y + 1] != '/')) && (y < MAXLINELENGTH - 2) && ((comment[a][y] != '\0') || (comment[a][y + 1] != '\0'))) 
                    {
                        w = IN;
                        printf("DEBUGOUTPUT inside a MULTILINE comment on line 1: w is %d, nocomment[%d][%d] is %c, comment[%d][%d] is %c, comment[%d][%d] is %c \n", w, a, x, nocomment[a][x], a, y, comment[a][y], a, y + 1, comment[a][y + 1]); 

                        y++;
                        if ((y == MAXLINELENGTH - 3) || (comment[a][y] == '\0') || (comment[a][y + 1] == '\0'))
                            { 
                                nocomment[a][x] = '\n';
                            }                                                     
                        if ((comment[a][y] == '*') && (comment[a][y + 1] == '/')) 
                        {
                            printf("DEBUGOUTPUT end of multiline comment on line 1: w is %d, nocomment[%d][%d] is %c, comment[%d][%d] is %c, comment[%d][%d] is %c \n", w, a, x, nocomment[a][x], a, y, comment[a][y], a, y + 1, comment[a][y + 1]); 
                            y = y + 2;                                                                                                                                                                                                               
                            w = OUT;                                                                                                                                                                                                                 
                            break;                                                                                                                                                                                                                   
                        }
                    }
                }
                else if ((comment[a][y] != '/') && (comment[a][y + 1] == '*'))
                {            
                    w = OUT; 
                    nocomment[a][x] = comment[a][y];
                    printf("DEBUGOUTPUT outside comment on line 1, asterisk on right: w is %d, nocomment[%d][%d] is %c, comment[%d][%d] is %c, comment[%d][%d] is %c \n", w, a, x, nocomment[a][x], a, y, comment[a][y], a, y + 1, comment[a][y + 1]); 
                    x++;
                    y++;
                }
                else if ((comment[a][y] == '*') && (comment[a][y + 1] != '/'))
                {            
                    w = OUT; 
                    nocomment[a][x] = comment[a][y];
                    printf("DEBUGOUTPUT outside comment on line 1, asterisk on left: w is %d, nocomment[%d][%d] is %c, comment[%d][%d] is %c, comment[%d][%d] is %c \n", w, a, x, nocomment[a][x], a, y, comment[a][y], a, y + 1, comment[a][y + 1]); 
                    x++;
                    y++;
                }
                else if ((comment[a][y] == '/') && ((comment[a][y + 1] != '*') || (comment[a][y + 1] != '/')))
                {            
                    w = OUT; 
                    nocomment[a][x] = comment[a][y];
                    printf("DEBUGOUTPUT outside comment on line 1, slash on left: w is %d, nocomment[%d][%d] is %c, comment[%d][%d] is %c, comment[%d][%d] is %c \n", w, a, x, nocomment[a][x], a, y, comment[a][y], a, y + 1, comment[a][y + 1]); 
                    x++;
                    y++;
                }
                else if ((comment[a][y] != '/') || ((comment[a][y] != '*') && (comment[a][y + 1] == '/')))
                {            
                    w = OUT; 
                    nocomment[a][x] = comment[a][y];
                    printf("DEBUGOUTPUT outside comment on line 1, asterisk on right : w is %d, nocomment[%d][%d] is %c, comment[%d][%d] is %c, comment[%d][%d] is %c \n", w, a, x, nocomment[a][x], a, y, comment[a][y], a, y + 1, comment[a][y + 1]); 
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
            while (((comment[a][y] != '*') || (comment[a][y + 1] != '/')) && (y < MAXLINELENGTH - 2) && ((comment[a][y] != '\0') || (comment[a][y + 1] != '\0'))) 
            {
                w = IN;
                printf("DEBUGOUTPUT INSIDE multiline comment on line 2, w is %d, nocomment[%d][%d] is %c, comment[%d][%d] is %c, comment[%d][%d] is %c \n", w, a, x, nocomment[a][x], a, y, comment[a][y], a, y + 1, comment[a][y + 1]); 
                y++;                                                                                                                                                                                                                     
                if ((comment[a][y] == '/') && (comment[a][y + 1] == '/'))                                                                                                                                                                
                {

                    printf("DEBUGOUTPUT WE FOUND A SINGLELINE 
                    y = y + 2; 
                    w = IN;
                }
                if (comment[a][y] == '*' && comment[a][y + 1] == '/') 
                {
                    printf("DEBUGOUTPUT end of multiline comment on line 1: w is %d, nocomment[%d][%d] is %c, comment[%d][%d] is %c, comment[%d][%d] is %c \n", w, a, x, nocomment[a][x], a, y, comment[a][y], a, y + 1, comment[a][y + 1]); 

                    y = y + 2; 
                    w = OUT;   
                    break;
                    
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
