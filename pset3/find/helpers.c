/**
 * helpers.c
 *
 * Computer Science 50
 * Problem Set 3
 *
 * Helper functions for Problem Set 3.
 */
       
#include <cs50.h>
#include <stdio.h>
#include "helpers.h"

/**
 * Returns true if value is in array of n values, else false.
 */
 
bool search(int value, int values[], int n)
{
    // iterative binary search implementation
    int ixlow = 0;
    int ixhigh = n - 1;
    
    while (ixlow <= ixhigh)
    {
        int mid = (ixlow + ixhigh) / 2;
        
        if (values[mid] < value)
        {
            ixlow = mid + 1;
        }
        else if (values[mid] > value)
        {
            ixhigh = mid - 1;
        }
        else 
        {
            return true;
        }
    }
    return false;
}  
    
    /* linear search implementation
    for ( int i = 0; i < n; i++ )
    {
        if (values[i] == value)
        {
            return true;
        }
    }
    return false;*/

/**
 * Sorts array of n values.
 */
void sort(int values[], int n)
{
    // bubble sort implementation, optimized to decrement n each pass
    int swapped = 0;

    for ( int i = 0; i < n - 1; i++ )
    {
        if ( values[i] > values[i+1] )
        {
            int switch_value = values[i+1];
            values[i+1] = values[i];
            values[i] = switch_value;
            swapped ++;
        }
    }
    n = n - 1;

    if (!swapped)
    ;  
    return;
}
