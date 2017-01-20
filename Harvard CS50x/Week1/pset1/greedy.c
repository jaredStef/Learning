#include <stdio.h>
#include <cs50.h>
#include <math.h>

int minCoinsForDollar(int cents);

int main(void)
{
  while(true)
  {
    printf("O hai! How much change is owed?\n");
    float amount = GetFloat();
    if(amount > 0.0)
    {
      int coins = minCoinsForDollar(roundf(amount*100));
      printf("%d\n", coins);
      break;
    }
  }
}

int minCoinsForDollar(int cents)
{

    int coinsTaken = 0;
    // coin amounts
    int amounts[] = {25, 10, 5, 1};

    // goes through all the amounts and if it can remove it adds 1 to coins used
    while (cents != 0)
    {
      for (int i = 0; i < 4; i++)
      {
        if(cents >= amounts[i])
        {
          coinsTaken++;
          cents -= amounts[i];
          break;
        }
      }
    }
    return coinsTaken;
}
