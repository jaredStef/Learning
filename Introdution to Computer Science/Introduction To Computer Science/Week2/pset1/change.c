#include <stdio.h>
#include <cs50.h>

int minCoinsForDollar(float amount);

int main(void)
{
  while(true)
  {
    printf("Enter the amount to find the least amount of coins it can be made into: ");
    float amount = GetFloat();
    if(amount > 0.0)
    {
      int coins = minCoinsForDollar(amount);
      printf("%d\n", coins);
      break;
    }
    else
    {
      printf("You must enter a value greater than 0\n");
    }
  }
}

int minCoinsForDollar(float amount)
{
    int wholeDollars = (int)amount;
    float centsInAmount = amount - wholeDollars;
    int cents = (wholeDollars * 100) + (centsInAmount * 100);
    int coinsTaken = 0;
    // coin amounts
    int amounts[] = {25, 10, 5, 1};

    printf("%d\n", wholeDollars);
    printf("%f\n", centsInAmount);
    printf("%d\n", cents);
    printf("%d\n", coinsTaken);

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
