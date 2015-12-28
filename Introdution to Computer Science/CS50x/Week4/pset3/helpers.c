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

void swap(int *x, int *y);

/**
 * Returns true if value is in array of n values, else false.
 */
bool search(int value, int values[], int size)
{
  int lowIndex = 0;
  int highIndex = size - 1;

  while(lowIndex <= highIndex)
  {
    int middleIndex = ((highIndex - lowIndex) + lowIndex) / 2;

    // if the value is less than the middle value go on that side of the split
    if(value < values[middleIndex])
    {
      highIndex = middleIndex - 1;
    }
    // if the value
    else if (value < values[middleIndex])
    {
      lowIndex = middleIndex + 1;
    }
    else
    {
        return true;
    }
  }

  return false;
}

/**
 * Sorts array of n values
 * Uses Bubble Sort O(n^2)
 */
void sort(int values[], int size)
{
  for(int i = 0; i < (size-1); i++)
  {
    for(int j = 0; j < (size-(i+1)); j++)
    {
      // if the current value is smaller than next swap them
      if(values[j] > values[j+1])
      {
        swap(&values[j], &values[j+1]);
      }
    }
  }
  return;
}

void swap(int *x, int *y)
{
  int temp;
  temp = *x;
  *x = *y;
  *y = temp;
}
