#include <stdio.h>
#include <stdlib.h>

int get_integer_size(int number);
void fill_array(int* array, int numbers_count, int interval);
void draw_horizontal_histogram(int* array, int interval);
void draw_vertical_histogram(int* array);

int main()
{
    char drawing_type;
    scanf("%c", &drawing_type);
    
    if (drawing_type != (char)'h' && drawing_type != (char)'v')
    {
        printf("Neplatny mod vykresleni\n");
        return 1;
    }

    int numbers_count, interval;
    scanf("%d%d",&numbers_count,&interval);

    if (numbers_count < 0 || interval < 0)
        return 1;

    if (drawing_type == (char)'v')
        interval = 1;



    int array[10];
    fill_array(array, numbers_count, interval);

    if (drawing_type == (char)'h')
    {
        draw_horizontal_histogram(array, interval);
    }
    else
    {
        draw_vertical_histogram(array);
    }

    printf("\n");

    return 0;
}

void draw_horizontal_histogram(int* array, int interval)
{
    int numberSize = get_integer_size(interval+8);

    for (int i = 0; i < 10; i++)
    {
        if (i == 9)
        {
            if (array[9] > 0)
            {
                printf("\ninvalid: ");
                for (int j = 0; j < array[i]; j++)
                {
                    printf("#");
                }
            }
        }
        else
        {
            if (get_integer_size(interval + i) < numberSize) {
                printf(" ");
            }
            printf("%d", interval + i);
            if (array[i] > 0)
                printf(" ");
            for (int j = 0; j < array[i]; j++)
            {
                printf("#");
            }
        }
        if (i < 8)
        {
            printf("\n");
        }
    }
}

void draw_vertical_histogram(int* array)
{
    int height = 0;
    for (int i = 0; i < 10; i++)
    {
        if (array[i] > height)
            height = array[i];
    }

    int height_ = height;
    for (int i = 0; i < height_; i++)
    {
        if (array[9] >= height)
            printf("#");
        else
            printf(" ");

        for (int j = 0; j < 9; j++)
        {
            if (array[j] >= height)
                printf("#");
            else
                printf(" ");
        }
        height--;
        printf("\n");
    }

    printf("i");
    for (int i = 0; i < 9; i++)
    {
        printf("%d",i+1);
    }
}

void fill_array(int* array, int numbers_count, int interval)
{
    for (int i = 0; i < 10; i++)
        array[i] = 0;

    for (int i = 0; i < numbers_count; i++)
    {
        int tmp_number = 0;
        scanf("%d", &tmp_number);
        if (tmp_number < interval || tmp_number > interval + 8)
            array[9]++;
        else
        {
            for (int j = 0; j < 9; j++)
            {
                if (tmp_number == interval + j)
                    array[j]++;
            }
        }
    }
}

int get_integer_size(int number)
{
    int size = 1;
    while (number >= 10)
    {
        number /= 10;
        size++;
    }
    return size;
}