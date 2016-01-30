#include <stdio.h>
#include <cs50.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int main(int argc, string argv[])
{ 
   //input error checking with argc count
   if (argc != 2)
   {
        printf("Usage: ./caesar <key>\n");
        return 1;
   }
   
   //declaring and assigning cipher key, input error checking
   int key = atoi(argv[1]);
   
   if (key <= 0)
   {
        printf("Key must be a non-negative integer.\n");
   }
   
   //working with variables
   string plaintext;
   plaintext = GetString();
   int plaintext_length = strlen(plaintext);
   
   //iterating, enciphering as appropriate and printing 
   for (int i=0; i < plaintext_length; i++)
   {
        if ( isalpha(plaintext[i]) && isupper(plaintext[i]))
        {
            char encrypted_char = (((plaintext[i] - 65) + key) % 26 + 65);
            printf("%c", encrypted_char);
        }
        else if ( isalpha(plaintext[i]) && islower(plaintext[i]))
        {
            char encrypted_char = (((plaintext[i] - 97) + key) % 26 + 97);
            printf("%c", encrypted_char);
        }
        else
        {
            printf("%c", plaintext[i]);
        }
   }
   printf("\n");
   return 0;
}
