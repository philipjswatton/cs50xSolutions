#include <cs50.h>
#include <stdio.h>

int get_height(void);
void print_spaces(int h, int i);
void print_hashtags(int i);


int main(void)
{
    int h = get_height();
    for(int i = 1; i <= h; i++)
    {
        print_spaces(h, i);
        print_hashtags(i);
        printf("  ");
        print_hashtags(i);
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

void print_spaces(int h, int i)
{
    for (int w = 1; w <= h - i - a; w++)
        {
            printf(" ");
        }
}


void print_hashtags(int i)
{
    for (int j = 0; j < i; j++)
        {
            printf("#");
        }
}