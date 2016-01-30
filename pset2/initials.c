#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>

int main (void)
{
    //declaring and assigning variables, printing first char
    string name;       
    name = GetString();
    printf("%c", toupper(name[0]));
    
    //checking for null value, iterating and printing initials
    if (name != NULL)
    {
        for (int i = 1, n = strlen(name); i < n; i++)
        { 
            if (name[i] == ' ')
            {
               printf("%c", toupper(name[i+1]));
            } 
        }
        printf("\n");
    }   
}
