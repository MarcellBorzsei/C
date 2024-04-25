#ifndef REVERSE_H
#define REVERSE_H
#include<stdbool.h>


typedef struct parameters
{
    bool needLine;
    int maxCharNum;
} parameters;

bool argumentCheck(int argc, char **argv);
parameters arguments(int argc, char **argv, parameters adatok);
void reverseWord(char* word);
void executeInStdInput(parameters adatok);
void executeInFile(int argc, char **argv, parameters adatok);

#endif