#include <stdio.h>
#include <cs50.h>

int main(void)
{
    //Get user input.
    long long num = 0;
    do
    {
        printf("Number: ");
        num = get_long_long();
    }
    while (num == 0);

    //Check if valid.
    int sum = 0;
    int i = 0;
    long long num_copy = num;

    if (num_copy >= 4000000000000 && num_copy < 5600000000000000)
    {
        while (num_copy)
        {
            if (i % 2 == 1)
            {
                int sub_num = (num_copy % 10) * 2;
                int sub_sum = 0;

                while (sub_num)
                {
                    sub_sum += sub_num % 10;
                    sub_num /= 10;
                }
                sum += sub_sum;
            }
            else
            {
                sum += num_copy % 10;
            }
            num_copy /= 10;
            i++;
        }

        if (sum % 10 == 0)
        {
            if (i == 13)
            {
                if (num >= 4000000000000 && num < 5000000000000)
                {
                    printf("VISA\n");
                }
            }
            else if (i == 15)
            {
                if ((num >= 340000000000000 && num < 350000000000000) || (num >= 370000000000000 && num < 380000000000000))
                {
                    printf("AMEX\n");
                }
                else
                {
                    printf("INVALID\n");
                }
            }
            else if (i == 16)
            {
                if (num >= 4000000000000000 && num < 5000000000000000)
                {
                    printf("VISA\n");
                }
                else if (num >= 5100000000000000 && num < 5600000000000000)
                {
                    printf("MASTERCARD\n");
                }
            }
            else
            {
                printf("INVALID\n");
            }
        }
        else
        {
            printf("INVALID\n");
        }
    }
    else
    {
        printf("INVALID\n");
    }

    return 0;
}