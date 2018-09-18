#import <stdio.h>
#import <cs50.h>

int main(void)
{
    int height = 0;
    do
    {
        printf("Height: ");
        height = get_int();
    }
    while (height > 23 || height < 0);

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < (height - 1 - i); j++)
        {
            printf(" ");
        }
        for (int k = 0; k < (i + 2); k++)
        {
            printf("#");
        }
        printf("\n");
    }
}