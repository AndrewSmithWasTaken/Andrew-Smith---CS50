#include <stdio.h>
#include <cs50.h>
#include <math.h>

int main(void)
{
    float dollar_amount = 0;
    int cent_amount = 0;
    int coin_count = 0;
    int quarter = 25;
    int dime = 10;
    int nickel = 5;
    int penny = 1;
    
    //get the amount in dollars and cents
    do
    {
        printf("how much change is owed in dollars and cents? ");
        dollar_amount=GetFloat();
    }
    while (dollar_amount < 0);
    
    //convert the dollar amount to a cents amount and round accurately
    dollar_amount = (dollar_amount*100); 
    cent_amount = round(dollar_amount);   
    
    //skip straight to the end or begin looping
    if (cent_amount % quarter == 0)
    {
        coin_count = cent_amount/quarter;
        cent_amount = 0;  
    }
    while (cent_amount >= quarter)
    {
        coin_count = (cent_amount / quarter);
        cent_amount = cent_amount % quarter;
        //printf("coins used: %i\n", coin_count);
        //printf("cents remaining: %i\n", cent_amount);
    }
    while (cent_amount >= dime)
    {
        coin_count = coin_count + cent_amount/dime;
        cent_amount = cent_amount % dime;
    }
    while (cent_amount >= nickel)
    {
        coin_count = coin_count + cent_amount/nickel;
        cent_amount = cent_amount % nickel;
    }
    while (cent_amount >= penny)
    {
        coin_count = coin_count + cent_amount/penny;
        cent_amount = cent_amount % penny;
    }
    printf("%d\n", coin_count);
}
