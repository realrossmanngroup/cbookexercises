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

    
    FILE *program pointer    printf("The filename you want me to open is %s\n\n", filename); 

    if (program == NULL)
    { 
        perror("Error opening file");
    }
    else
    {
        printf("%p\n\n", (void 
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
        }
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

                          while (comment[a][y] != '\0' && y < MAXLINELENGTH - 1)
            {
                w = OUT;
                if (comment[a][y] != '*')
                {
                    if (comment[a][y] == ''  
                    {                                                     "
                        w = IN;                                           
                        a++;                                              
                        x = y = 0;                                        
                        w = OUT;                                          
                        break;                                            
                    }
                    else
                    {            
                        w = OUT; 
                        nocomment[a][x] = comment[a][y];
                        printf("DEBUGOUTPUT w is %d nocomment[%d][%d] is %c, comment[%d][%d] is %c\n", w, a, x, nocomment[a][x], a, y, comment[a][y]); 
                        x++;
                        y++;
                    }
                }
                else 
                {
                    y = y + 2;                                                                        
                    w = IN;                                                                           
                    while (comment[a][y] != ' 
                    {
                        y++;                                                  
                        if (comment[a][y] == ' 
                        {
                            y = y + 2; 
                            w = OUT;   
                            break;     
                        }
                    }
                }
            }
        }
        else
        {                                                                                     
            while (comment[a][y] != ' 
            {
                y++;                                                  
                if (comment[a][y] == ' 
                {
                    y = y + 2; 
                    w = OUT;   
                    break;     
                }
            }
        }
    }

    
    for (int x = 0; x < linewereon; x++) 
    {
         
        printf("%s", nocomment[x]);
    } 

    printf("\n\nTHIS IS THE UN-COMMENTED, PROCESSED VERSION OF THE PROGRAM!\n\n");
}


THIS IS THE UN-COMMENTED, PROCESSED VERSION OF THE PROGRAM!

