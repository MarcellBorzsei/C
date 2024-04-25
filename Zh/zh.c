#include<stdio.h>
#include<stdbool.h>

int tabla[6][7];
int sorSzam = 6;
int oszlopSzam = 7;

void init()
{
    for (int i = 0; i < sorSzam; i++)
    {
        for (int j = 0; j < oszlopSzam; j++)
        {
            tabla[i][j] = 0;
        }
    }
}

void printTable()
{
    for (int i = 0; i < sorSzam; i++)
    {
        for (int j = 0; j < oszlopSzam; j++)
        {
            if (j == 6)
            {
                printf("%d\n", tabla[i][j]);
            }
            else
            {
                printf("%d ", tabla[i][j]);
            }
        }
    }
}

void submit (int jatekos, int kertOszlop)
{
    int aktOszlop = kertOszlop-1;
    bool szabadE = false;
    for (int i = sorSzam-1; i >= 0; i--)
    {
        if (tabla[i][aktOszlop] == 0)
        {
            szabadE = true;
            tabla[i][aktOszlop] = jatekos;
            break;
        }
    }
    if (szabadE == false)
    {
        printf("Nem legalis lepes tortent.\n");
    }
}

int evaluate ()
{
    // Sorokban való szűrés

    int nyertE = 0;
    for (int i = 0; i < sorSzam; i++)
    {
        for (int j = 0; j <= 4; j++)
        {
            if (tabla[i][j] != 0)
            {
                if ((tabla[i][j] == tabla[i][j+1]) && (tabla[i][j+1] == tabla[i][j+2]))
                {
                    if (tabla[i][j] == 1)
                    {
                        nyertE = 1;
                        break;
                        return nyertE;
                    }
                    else
                    {
                        nyertE = 2;
                        break;
                        return nyertE;
                    }
                    
                }

            }
            
        }
    }
    for (int i = 0; i < oszlopSzam; i++)
    {
        for (int j = 0; j <= 3; j++)
        {
            if (tabla[j][i] != 0)
            {
                if ((tabla[j][i] == tabla[j+1][i]) && (tabla[j+1][i] == tabla[j+2][i]))
                {
                    if (tabla[j][i] == 1)
                    {
                        nyertE = 1;
                        break;
                        return nyertE;
                    }
                    else
                    {
                        nyertE = 2;
                        break;
                        return nyertE;
                    }
                }
            }
        }
    }
    return nyertE;
}

void game(char* lepesek)
{
    for (int i = 0; lepesek[i] != '\0' ; i++)
    {
        if ((i+2) % 2 == 0)
        {
            if (lepesek[i] == 'A')
            {
                submit(1,1);
            }
            if (lepesek[i] == 'B')
            {
                submit(1,2);
            }
            if (lepesek[i] == 'C')
            {
                submit(1,3);
            }
            if (lepesek[i] == 'D')
            {
                submit(1,4);
            }
            if (lepesek[i] == 'E')
            {
                submit(1,5);
            }
            if (lepesek[i] == 'F')
            {
                submit(1,6);
            }
            if (lepesek[i] == 'G')
            {
                submit(1,7);
            }
        }
        else
        {
            if (lepesek[i] == 'A')
            {
                submit(2,1);
            }
            if (lepesek[i] == 'B')
            {
                submit(2,2);
            }
            if (lepesek[i] == 'C')
            {
                submit(2,3);
            }
            if (lepesek[i] == 'D')
            {
                submit(2,4);
            }
            if (lepesek[i] == 'E')
            {
                submit(2,5);
            }
            if (lepesek[i] == 'F')
            {
                submit(2,6);
            }
            if (lepesek[i] == 'G')
            {
                submit(2,7);
            }
        }
    }
    printTable();
    if (evaluate() == 1)
    {
        printf("First player wins.\n");
    }
    else if (evaluate() == 2)
    {
        printf("Second player wins.\n");
    }
    else
    {
        printf("Draw.\n");
    }
}

int main()
{
    init();
    char lista[] = "ABDCAGEEE"; //Például, ez lehet bemenet.
    game(lista);
    
    return 0;
}




