#define _XOPEN_SOURCE
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <cs50.h>

int main(int argc, string argv[])
{
    if (argc != 2)
    {
        printf("Usage: %s hash\n", argv[0]);
        return 1;
    }

    string hash = argv[1];
    char salt[3];
    salt[0] = argv[1][0];
    salt[1] = argv[1][1];
    salt[2] = '\0';

    int length = 1;

    while (length < 6)
    {
        // build starting string
        char guess[length + 1];
        for (int i = 0; i < length; i++)
        {
            guess[i] = 'A';
        }
        guess[length] = '\0';

        while (strncmp(hash, crypt(guess, salt), strlen(hash)))
        {
            if (guess[0] == 'Z')
            {
                guess[0] = 'a';
            }
            else if (guess[0] == 'z' && length > 1)
            {
                guess[0] = 'A';
                if (guess[1] == 'Z')
                {
                    guess[1] = 'a';
                }
                else if (guess[1] == 'z' && length > 2)
                {
                    guess[1] = 'A';
                    if (guess[2] == 'Z')
                    {
                        guess[2] = 'a';
                    }
                    else if (guess[2] == 'z' && length > 3)
                    {
                        guess[2] = 'A';
                        if (guess[3] == 'Z')
                        {
                            guess[3] = 'a';
                        }
                        else if (guess[3] == 'z' && length > 4)
                        {
                            guess[3] = 'A';
                            if (guess[4] == 'Z')
                            {
                                guess[4] = 'a';
                            }
                            else if (guess[4] == 'z')
                            {
                                printf("All possible combinations exhausted.\n");
                                break;
                            }
                            else
                            {
                                guess[4] += 1;
                            }
                        }
                        else if (guess[3] == 'z' && length < 5)
                        {
                            break;
                        }
                        else
                        {
                            guess[3] += 1;
                        }
                    }
                    else if (guess[2] == 'z' && length < 4)
                    {
                        break;
                    }
                    else
                    {
                        guess[2] += 1;
                    }
                }
                else if (guess[1] == 'z' && length < 3)
                {
                    break;
                }
                else
                {
                    guess[1] += 1;
                }
            }
            else if (guess[0] == 'z' && length < 2)
            {
                break;
            }
            else
            {
                guess[0] += 1;
            }
        }
        if (!strncmp(hash, crypt(guess, salt), strlen(hash)))
        {
            //printf("Found: %s\n", guess);
            printf("%s\n", guess);
            break;
        }
        else
        {
            //printf("Nothing found with length %d.\n", length);
            length++;
        }
    }
    return 0;
}