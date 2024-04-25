#include<stdio.h>
#include "reverse.h"
#include<string.h>
#include<stdbool.h>
#include<ctype.h>
#include<stdlib.h>

bool argumentCheck(int argc, char **argv)
{
    bool igaz1 = false;
    bool igaz2 = false;
    if(argc < 3)
    {
        printf("Usage:\n");
        printf("\trev [SHOW LINE NUMBERS] [MAX LINE LENGTH] files...");
        return false;
    }
    
    if(atoi(argv[2]) > 0 && isdigit(*argv[2]) > 0)
    {
        igaz1 = true;
    }
    
    if( ((strcmp(argv[1], "nolinenums")) == 0) || ((strcmp(argv[1], "linenums")) == 0) )
    {
        if((strcmp(argv[1], "nolinenums")) == 0)
        {
            igaz2 = true;
        }
        if((strcmp(argv[1], "linenums")) == 0)
        {
            igaz2 = true;
        }
        
    }

    if(igaz1 && igaz2)
    {   
        return true;        
    }
    else
    {
        printf("Usage:\n");
        printf("\trev [SHOW LINE NUMBERS] [MAX LINE LENGTH] files...");
        return false;
    }
}

parameters arguments(int argc, char **argv, parameters adatok)
{
    
    if(argc < 3)
    {
        return adatok;
    }
    
    if(atoi(argv[2]) > 0 && isdigit(*argv[2]) > 0)
    {
        adatok.maxCharNum = atoi(argv[2]);
    }
    
    if( ((strcmp(argv[1], "nolinenums")) == 0) || ((strcmp(argv[1], "linenums")) == 0) )
    {
        if((strcmp(argv[1], "nolinenums")) == 0)
        {
            adatok.needLine = false;
        }
        if((strcmp(argv[1], "linenums")) == 0)
        {
            adatok.needLine = true;
        }
        
    }
    return adatok;    
}

void reverseWord(char* word)
{
    int wordLength = strlen(word);
    for(int i = 0; i < (wordLength/2); i++)
    {
        char temp = word[i];
        word[i] = word[wordLength-1-i];
        word[wordLength-1-i] = temp;
    }
    printf("%s\n", word);
    
}

void executeInStdInput(parameters adatok)
{
    int size = 8;      // According to the task, for example: 8
    char** lines = malloc(sizeof(char*) * size);

    if (lines == NULL)
    {
        printf("Memory allocation failed!");
        exit(2);
    }

    int lineMaxLength = adatok.maxCharNum; // The current line's maximum length
   
    char buff[lineMaxLength];
    bool run = true;
    int counter = -1;

    while(run)
    {
        if(counter+1 == size) //if lines is full, then reallocate more space
        {
            size *= 2;
            lines = realloc(lines, sizeof(char*) * size);
            if (lines == NULL)
            {
                printf("Memory allocation failed!");
                exit(2);
            }
        }
        
        char* currentLine = fgets(buff, lineMaxLength+1, stdin);  
        if(currentLine == NULL)
        {
            run = false;
        }
        
        else
        {
            counter += 1;
            int strLen = strlen(buff);
            //printf("%d", stringLength);
            lines[counter] = malloc(strLen * sizeof(char));

            if(lines[counter] == NULL)
            {
                printf("Memory allocation failed!");
                exit(2);
            }

            if(buff[strLen-1] == '\n')
            {
                buff[strLen-1] = '\0';
            }

            strcpy(lines[counter], buff);
            fflush(stdin);
            
            
            
        }       
         
    }

    if(adatok.needLine)
    {
        for(int i = counter; i >= 0; i--)
        {
            printf("%d ", i+1);
            reverseWord(lines[i]);
            
        }
    }
    else
    {
        for(int i = counter; i >= 0; i--)
        {
            reverseWord(lines[i]);
            
        }
    }
    // Free allocated memory
    for (int i = 0; i <= counter; i++) 
    {
        free(lines[i]);
    }
    free(lines);
        
    
          
}


void executeInFile(int argc, char **argv, parameters adatok)
{
    FILE *file;
    int counter = -1;
    int size = 8; // According to the task, for example: 8
    char** lines = malloc(sizeof(char*) * size);

    if(lines == NULL)
    {
        printf("Memory allocation failed!");
        exit(2);
    }


    for(int i = 3; i < argc; i++)
    {
        file = fopen(argv[i], "r");
        
        if(file == NULL)
        {
            fprintf(stderr, "File opening unsuccessful: <%s>\n", argv[i]); 
        }
        else
        {
            
            

            int lineMaxLength = adatok.maxCharNum; // The current line's maximum length
            char buff[lineMaxLength];
            bool run = true;
            

            while(run)
            {
                if(counter+1 == size) //if lines is full, then reallocate more space
                {
                    size *= 2;
                    lines = realloc(lines, sizeof(char*) * size);
                    if (lines == NULL)
                    {
                        printf("Memory allocation failed!");
                        exit(2);
                    }
                }
                
                char* currentLine = fgets(buff, lineMaxLength+1, file);  
                if(currentLine == NULL)
                {
                    run = false;
                }
                else
                {
                    counter += 1;
                    int strLen = strlen(buff);
                    lines[counter] = malloc(strLen + 1); // allocate space for string + null terminator

                    if(lines[counter] == NULL)
                    {
                        printf("Memory allocation failed!");
                        exit(2);
                    }

                    if(buff[strLen-1] == '\n')
                    {
                        buff[strLen-1] = '\0';
                        strcpy(lines[counter], buff);
                    }
                    else
                    {
                        strcpy(lines[counter], buff);
                        while(strstr(buff, "\n") == NULL && fgets(buff, lineMaxLength+1, file) != NULL);
                                                   
                        
                    }           
                    
                    
                }
            }    
            
        }
                
        fclose(file);
    }
    
    if(adatok.needLine)
    {
        for(int i = counter; i >= 0; i--)
        {
            printf("%d ", i+1);
            reverseWord(lines[i]);
        }
    }

    else
    {
        for(int i = counter; i >= 0; i--)
        {
            reverseWord(lines[i]);
        }

    }
            
    
    // Free allocated memory
    for (int i = 0; i <= counter; i++)
    {
        free(lines[i]);
    }
    free(lines);
}