#include <stdio.h>
#include <stdlib.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>

char CryptCaesar(char c, int key);

int main (int argc, char* argv[])
{
  if (argc != 2)
  {
    printf("Use caesar <key>\n");
    return 1;
  }

  int key = atoi(argv[1]);
  if (key > 26)
  {
    key %= 26;
  }
  printf("Enter the key to encrypt with key of %d: ", key);
  string input = GetString();

  for(int i = 0; i < strlen(input);i++)
  {
    printf("%c", CryptCaesar(input[i], key));
  }
  printf("\n");
}

char CryptCaesar(char c, int key)
{
  int character = c;
  int maxLowercase = 122;
  int maxUpercase = 90;

  int startOfLowercaseOneMinus = 96;
  int startOfUppercaseOneMinus = 64;

  int startOneMinusToUse = 0;
  int maxToUse = 0;

  // checks if is lowercase or uppercase and sets values accordingly
  if(islower(character))
  {
    maxToUse = maxLowercase;
    startOneMinusToUse = startOfLowercaseOneMinus;
  }
  else if(isupper(character))
  {
    maxToUse = maxUpercase;
    startOneMinusToUse = startOfUppercaseOneMinus;
  }
  else
  {
    return character;
  }
  // shifts by key
  character += key;

  // if over end of alphabet starts over from top
  if (character > maxToUse)
  {
    character = (character - maxToUse) + startOneMinusToUse;
  }

  return character;
}
