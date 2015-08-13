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
        printf("Usage: ./vigenere <key>\n");
        return 1;
   }
   
   //working with variables and error checking
   string keyword = argv[1];
   int keyword_length = strlen(keyword);
   
   for (int i = 0, n = keyword_length; i < n; i++)
   {
        if ( isdigit(keyword[i]) )
        {
            printf("no numbers please..\n");
            return 1;
        }
   }
   
   //working with variables
   string plaintext;
   plaintext = GetString();
   int plaintext_length = strlen(plaintext);
   char encrypted_char;
   
   //iterating, enciphering as appropriate and printing
   for (int i = 0, j = 0; i < plaintext_length; i++, j++)
   {
        if ( isalpha(plaintext[i]) && isupper(plaintext[i]) && isupper(keyword[j % keyword_length]) )
        {
            encrypted_char = ((plaintext[i] - 'A') + (keyword[j % keyword_length] - 'A')) % 26 + 'A';
            printf("%c", encrypted_char);
        }
        else if ( isalpha(plaintext[i]) && isupper(plaintext[i]) && islower(keyword[j % keyword_length]))
        {
            encrypted_char = ((plaintext[i] - 'A') + (keyword[j % keyword_length] - 'a')) % 26 + 'a';
            printf("%c", encrypted_char);
        }
        else if ( isalpha(plaintext[i]) && islower(plaintext[i]) && islower(keyword[j % keyword_length]))
        {
            encrypted_char = ((plaintext[i] - 'a') + (keyword[j % keyword_length] - 'a')) % 26 + 'a';
            printf("%c", encrypted_char);
        }
        else if ( isalpha(plaintext[i]) && islower(plaintext[i]) && isupper(keyword[j % keyword_length]))
        {
            encrypted_char = ((plaintext[i] - 'a') + (keyword[j % keyword_length] - 'A')) % 26 + 'a';
            printf("%c", encrypted_char);
        }
        else
        {
            printf("%c", plaintext[i]);
            j--;
        }
   }
   printf("\n");
   return 0;
}
