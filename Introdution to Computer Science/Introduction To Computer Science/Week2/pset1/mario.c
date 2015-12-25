#include <stdio.h>
#include <cs50.h>

void printSpaces(int blocks);

int main(void)
{
    while (true)
    {
        printf("Enter half the size of the pyramid: ");
        int size = GetInt();
        if(size > 23 || size <= 0)
        {
            printf("Half the size of the pyramid must be between 1 and 23\n");
        }
        else
        {
           printSpaces(size);
           break;
        }
    }
}

void printSpaces(int blocks)
{
  for(int i = 1; i <= blocks; i++)
  {
    // prints the number of spaces needed for the iteration
    for(int spacesToPrint = blocks - i; spacesToPrint != 0; spacesToPrint--)
    {
      printf(" ");
    }

    // prints the number of blocks needed for each iteration
    for(int blocksToPrint = blocks - i; blocksToPrint != blocks; blocksToPrint++)
    {
      printf("#");
    }
    printf("\n");
  }
}
