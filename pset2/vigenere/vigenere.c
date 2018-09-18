#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

int main(int argc, string argv[])
{
    if (argc != 2)
    {
        printf("Usage: ./vigenere k\n");
        return 1;
    }
    string keyword = argv[1];
    for (int i = 0; i < strlen(keyword); i++)
    {
        if (!isalpha(keyword[i]))
        {
            printf("Usage: ./vigenere k\n");
            return 1;
        }
    }
    string plain = get_string("plaintext: ");
    printf("ciphertext: ");

    int key_letter_index = 0;

    for (int i = 0; i < strlen(plain); i++)
    {
        char letter = plain[i];

        if (!isalpha(letter))
        {
            printf("%c", letter);
        }
        else
        {
            char key_letter = keyword[key_letter_index % strlen(keyword)];
            int key;

            if (isupper(key_letter))
            {
                key = ((int) key_letter) - 65;
            }
            else
            {
                key = ((int) key_letter) - 97;
            }

            if (isupper(letter))
            {
                int new_letter_num = (((int) letter) + key);
                if (new_letter_num > 90)
                {
                    new_letter_num -= 26;
                }
                printf("%c", new_letter_num);
            }
            else
            {
                int new_letter_num = (((int) letter) + key);
                if (new_letter_num > 122)
                {
                    new_letter_num -= 26;
                }
                printf("%c", new_letter_num);
            }
            key_letter_index += 1;
        }
    }
    printf("\n");
    return 0;
}