#include <stdio.h>
#include <cs50.h>

void printSpaces(int blocks);

int main(void)
{
    while (true)
    {
        printf("Height: ");
        int size = GetInt();
        if(size <= 23 && size > 0)
        {
            printSpaces(size);
            break;
        }
        else if (size == 0)
        {
            return 0;
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
    printf("#");
    printf("\n");
  }
}
