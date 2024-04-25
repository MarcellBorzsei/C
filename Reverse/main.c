#include "reverse.h"



int main(int argc, char** argv)
{
    parameters adatok;

    adatok = arguments(argc, argv, adatok);
    if(argumentCheck(argc, argv))
    {
        if(argc == 3)
        {
            executeInStdInput(adatok);
        }
        else
        {
            executeInFile(argc, argv, adatok);
        }
    }
    
    return 0;
}

