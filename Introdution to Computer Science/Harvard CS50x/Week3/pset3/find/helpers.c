/**
 * helpers.c
 *
 * Computer Science 50
 * Problem Set 3
 *
 * Helper functions for Problem Set 3.
 */

#include <cs50.h>

#include "helpers.h"

/**
 * Returns true if value is in array of n values, else false.
 */
bool search(int value, int values[], int n)
{
    int middle = n / 2;

    if (n <= 0)
    {
        return false;
    }

    if (value < values[middle])
    {
        return search(value, values, n - middle);
    }
    else if (value > values[middle])
    {
        return search(value, &values[middle], n - middle);
    }
    else if (value == values[middle])
    {
        return true;
    }
    return false;

}

/**
 * Sorts array of n values.
 */
void sort(int values[], int n)
{
    if (n < 2)
    {
        return;
    }
    else
    {
        int largestIndex;
        int largestNum = -1;

        for (int i = 0; i < n; i++)
        {
            if (values[i] > largestNum || largestNum == -1)
            {
                largestIndex = i;
                largestNum = values[i];
            }
        }

        int temp = values[n-1];
        values[n-1] = values[largestIndex];
        values[largestIndex] = temp;
        sort(values, n-1);
    }

    return;
}
