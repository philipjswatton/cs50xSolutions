#include <cs50.h>
#include <stdio.h>

int get_height(void);


int main(void)
{
    int h = get_height();
    for(int i = 1; i <= h; i++)
    {
        for (int w = 1; w <= h - i; w++)
        {
            printf(" ");
        }
        for (int j = 0; j < i; j++)
        {
            printf("#");
        }
        printf("\n");
    }
}


int get_height(void)
{
    int h;
    do
    {
        h = get_int("Height: ");
    }
    while(h < 1 || h > 8);
    return h;
}