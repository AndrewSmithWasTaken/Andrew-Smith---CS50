#include <stdio.h>
#include <cs50.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int main(int argc, string argv[])
{ 
   //int key_as_int = atoi(argv[1]);
   if (argc != 2)
   {
        printf("Usage: ./caesar <key>\n");
        return 1;
   }
   
   int key = atoi(argv[1]);
   
   if (key <= 0)
   {
        printf("Key must be a non-negative integer.\n");
        //printf("You chose: %s\n", argv[1]);
   }
   
   string plaintext;
   plaintext = GetString();
   int plaintext_length = strlen(plaintext);
      
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
