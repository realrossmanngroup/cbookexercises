#include <stdio.h>
#define MAXLINELENGTH 1000
#define MAXLINES 1000
#define MAXFILENAME 100
#define IN 0  
#define OUT 1 

void main()
{
    int i;                                   
    i = 0;                                   
    int j;                                   
    j = 0;                                   
    int x;                                   
    int w;                                   
    w = OUT;                                 
    x = 0;                                   
    int y;                                   
    y = 0;                                   
    int linewereon;                          
    linewereon = 0;                          
    int wheretoplacenullterminator;          
    wheretoplacenullterminator = 0;          
    int linelength;                          
    linelength = 0;                          
    char filename[MAXFILENAME];              
    char nocomment[MAXLINES][MAXLINELENGTH]; 
    char comment[MAXLINES][MAXLINELENGTH];   
    char filetempcontents[MAXLINELENGTH];    

    
    printf("What is the name of the file you wish to remove comments from in this directory?\n\n");
    while ((i < 98) && (filename[i] = getc(stdin)) != EOF)
    { 
        if (filename[i] != '\n')
        { 
            i++;
        }
        else
        {
            filename[i] = '\0'; 
            break;              
        }
    }

    
    FILE *program = fopen(filename, "r");                           
    printf("The filename you want me to open is %s\n\n", filename); 

    if (program == NULL)
    { 
        perror("Error opening file");
    }
    else
    {
        printf("%p\n\n", (void *)program); 
    }

    
    while (fgets(filetempcontents, MAXLINELENGTH, program) != NULL)
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

    
    for (int x = 0; x < linewereon; x++) 
    {

        printf("%s", comment[x]);
    } 

    printf("\n\nTHIS IS THE COMMENTED VERSION OF THE PROGRAM!\n\n");

    

    
    for (int a = 0; a <= linewereon; a++, x = 0, y = 0)
    {

        if (w == OUT)
        { 

             
            {
                if ((comment[a][y] != '/') && (comment[a][y + 1] != '*'))
                {            
                    w = OUT; 
                    nocomment[a][x] = comment[a][y];
                    x++;
                    y++;
                }
                else if ((comment[a][y] == '/') && (comment[a][y + 1] == '*')) 
                { 
                    printf("DEBUGOUTPUT we just entered a comment on the original line: nocomment[%d][%d] is %c, comment[%d][%d] is %c (should be a slash), comment[%d][%d] is %c (should be an asterisk) \n", a, x, nocomment[a][x], a, y, comment[a][y], a, y + 1, comment[a][y + 1]); 
                    y = y + 2;                                                                                                                                                                                                                                                           
                    w = IN;                                                                                                                                                                                                                  
                    while (((comment[a][y] != '*') || (comment[a][y + 1] != '/')) && (y < MAXLINELENGTH - 2) && ((comment[a][y] != '\0') || (comment[a][y + 1] != '\0')))                                                                                                                
                    {
                        printf("DEBUGOUTPUT in comment original line nocomment[%d][%d] is %c, comment[%d][%d] is %c, comment[%d][%d] is %c \n", a, x, nocomment[a][x], a, y, comment[a][y], a, y + 1, comment[a][y + 1]); 

                        y++;                                                      
                        if ((comment[a][y] == '*') && (comment[a][y + 1] == '/')) 
                        {
                            printf("DEBUGOUTPUT we just found the two characters that end a comment on the original line: nocomment[%d][%d] is %c, comment[%d][%d] is %c (should be an asterisk), comment[%d][%d] is %c (should be a slash) \n", a, x, nocomment[a][x], a, y, comment[a][y], a, y + 1, comment[a][y + 1]); 
                            y = y + 2;                                                                                                                                                                                                                                                                                     
                            printf("DEBUGOUTPUT we just supposedly fast forwarded past the two characters that end a comment on the original line: nocomment[%d][%d] is %c, comment[%d][%d] is %c, comment[%d][%d] is %c \n", a, x, nocomment[a][x], a, y, comment[a][y], a, y + 1, comment[a][y + 1]);                    
                            w = OUT;                                                                                                                                                                                                                                                                                       
                            break;                                                                                                                                                                                                                                                                                         
                        }
                    }
                } else{printf("If you're seeing this, something is wrong with this program\n");
                                        printf("DEBUGOUTPUT in first else statement - not a comment, not not a comment, so what is this? original line nocomment[%d][%d] is %c, comment[%d][%d] is %c, comment[%d][%d] is %c \n", a, x, nocomment[a][x], a, y, comment[a][y], a, y + 1, comment[a][y + 1]); 

                break;}
            }
        }
        else
        {                                                                                                                                                         
            while (((comment[a][y] != '*') || (comment[a][y + 1] != '/')) && (y < MAXLINELENGTH - 2) && ((comment[a][y] != '\0') || (comment[a][y + 1] != '\0'))) 
            {
                printf("DEBUGOUTPUT in comment NEW line! nocomment[%d][%d] is %c, comment[%d][%d] is %c and comment[%d][%d] is  %c\n", a, x, nocomment[a][x], a, y, comment[a][y], a, y + 1, comment[a][y + 1]); 
                y++;                                                                                                                                                                                             
                if (comment[a][y] == '*' && comment[a][y + 1] == '/')                                                                                                                                            
                {
                    printf("DEBUGOUTPUT leavingcomment on NEW line: nocomment[%d][%d] is %c, comment[%d][%d] is %c (should be an asterisk) and comment[%d][%d] is %c (should be a slash) \n", a, x, nocomment[a][x], a, y, comment[a][y], a, y + 1, comment[a][y + 1]); 

                    y = y + 2; 
                    w = OUT;   
                    break;
                    
                }
            }
        }
    }

    
    for (int x = 0; x < linewereon; x++) 
    {
        
    } 

    printf("\n\nTHIS IS THE UN-COMMENTED, PROCESSED VERSION OF THE PROGRAM!\n\n");
}
