#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>

int main(int argc, string argv[]) //argc is ALWAYS the n of arguments + 1 (because command itself is included), argv[] is ALWAYS a string of those arguments -- IN THIS PRECISE ORDER
{
    if (argc != 2) //this makes sure that arg length is exactly 2
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }

    for (int j = 0, keyLength = strlen(argv[1]); j < keyLength; j++) //this ensures that an integer is entered
    {
        int key[keyLength];
        if (isdigit(argv[1][j]) == 0) //checks each individual "character" of the input is an integer -- is.digit returns a 0 if no digit, or an int of equiv to the char's input in all other cases
        {
            printf("Usage: ./caesar key\n");
            return 1;
        }
    }

    int key = atoi(argv[1]); //atoi turns a string into an integer, therefore assigns (verified) value of command line argument to the variable
    string message = get_string("plaintext: "); //gets string to be ciphered

    int min = floor((double) key/26); //the lower number of 'cycles' through the alphabet
    int max = ceil((double) key/26); //the higher number of 'cycles' through the alphabet



    printf("ciphertext: ");
    for (int i = 0, length = strlen(message); i < length; i++)
    {
        if (message[i] >= 97 && message[i] <= 122) //applies to all lowercase ASCII values
        {
            if (message[i] + key <= 122)  //(26 - (key % 26)) gives the last letter on which the minimum number of cycles applies - the +96 puts this in the range of lowercase ASCII
            {
                printf("%c", ((message[i] + key)));
            } else
            {
                printf("%c", ((message[i] - 96 + key) % 26) + 96);
            }
        } else if (message[i] >= 65 && message[i] <= 90) //applies to all uppercase ASCII values
        {
            if (message[i] + key <= 90)  //(26 - (key % 26)) gives the last letter on which the minimum number of cycles applies - the +96 puts this in the range of lowercase ASCII
            {
                printf("%c", ((message[i] + key)));
            } else
            {
                printf("%c", ((message[i] - 64 + key) % 26) + 64);
            }
        } else //any other characters are printed without being cycled
        {
            printf("%c", message[i]);
        }
    }
    printf("\n");
    return 0;
}


// implement caesar's cipher  ci = (pi + k) % 26

