#include <stdio.h>
#include <stdlib.h>

int main()
{
    int rows = 0, cols = 0;
    scanf("%d", &rows);
    scanf("%d", &cols);

    int* field = NULL;
    field = (int*)malloc(sizeof(int) * rows * cols);
    for (int i = 0; i < rows * cols; i++)
        field[i] = 0;
    
    int turtle_count = 1;
    int turtle[3][3] = {{0,0,0},{0,0,0},{0,0,0}};

    char ch = '0';
    while (ch != (char)'x')
    {
        scanf("%c", &ch);
        if (ch == (char)'o')
            for (int i = 0; i < turtle_count; i++)
            { 
                int tmp;
                if (field[turtle[i][1] + turtle[i][2] * cols] == 1)
                    tmp = 0;
                else
                    tmp = 1;
                field[turtle[i][1] + turtle[i][2] * cols] = tmp;
            }
        else if (ch == (char)'r')
            for (int i = 0; i < turtle_count; i++)
            { 
                if (turtle[i][0] == 0)
                    turtle[i][0] = 3;
                else
                    turtle[i][0]--;
            }
        else if (ch == (char)'l')
            for (int i = 0; i < turtle_count; i++)
            {
                if (turtle[i][0] == 3)
                    turtle[i][0] = 0;
                else
                    turtle[i][0]++;
            }
        else if (ch == (char)'m')
            for (int i = 0; i < turtle_count; i++)
            {
                if (turtle[i][0] == 0)
                {
                    turtle[i][1]++;
                    if (turtle[i][1] > cols-1)
                        turtle[i][1] = 0;
                }
                else if (turtle[i][0] == 1)
                {
                    turtle[i][2]--;
                    if (turtle[i][2] < 0)
                        turtle[i][2] = rows-1;
                }
                else if (turtle[i][0] == 2)
                {
                    turtle[i][1]--;
                    if (turtle[i][1] < 0)
                        turtle[i][1] = cols-1;
                }
                else if (turtle[i][0] == 3)
                {
                    turtle[i][2]++;
                    if (turtle[i][2] > rows-1)
                        turtle[i][2] = 0;
                }
            }
        else if (ch == (char)'f' && turtle_count < 3)
            turtle_count++;
    }

    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            if (field[i*cols + j] == 1)
                printf("o");
            else
                printf(".");
        }
        printf("\n");
    }

    free(field);
    field = NULL;

    return 0;
}