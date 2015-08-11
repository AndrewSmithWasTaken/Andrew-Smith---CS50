#include <stdio.h>
#include <cs50.h>

int main(void)
{
    int height;
    int space;
    int hash;
    
    //getting the height of the wall and error checking
    do
    {
        printf("please enter a non-negative integer no greater than 23: ");
        height = GetInt();
    }
    while ((height < 0) || (height > 23));
    
    //iterating through the height values, printing the relevant numbers of spaces and octothorpes
    for (int i=1; i<=height; i++)
    {
        for (space = (height - i); space > 0; space--)
        {
            printf(" "); 
        }
        for (hash = 1; hash <= (i + 1); hash++)
        {   
            printf("#"); 
        }
         printf("\n");
    }
}
