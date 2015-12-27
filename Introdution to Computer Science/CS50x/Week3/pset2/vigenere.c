#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>

char CryptVigenere(char key, char letter);
char CryptCaesar(char c, int key);
int NumberForLetter(char c);

int main(int argc, char* argv[])
{
  if (argc != 2)
  {
    printf("Use vigenere <key>\n");
    return 1;
  }

  string key = argv[1];
  printf("Enter the phrase to encrpt: ");
  string phrase = GetString();
  int currentKeyIndex = 0;

  for(int i = 0; i < strlen(phrase); i++)
  {
      if(isalpha(phrase[i]))
      {
        printf("%c", CryptVigenere(key[currentKeyIndex], phrase[i]));
        currentKeyIndex = (currentKeyIndex + 1) % strlen(key);
      }
      else
      {
        printf("%c", phrase[i]);
      }
    }

  printf("\n");

}

char CryptVigenere(char key, char letter)
{
  letter = CryptCaesar(letter, NumberForLetter(key));
  return letter;
}

int NumberForLetter(char c)
{
  int character = tolower(c);
  return character - 97;
}

// Note this function is the same used in caesar.c
// I could have created a header file, but I decided that it would be easier
// for someone grading
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
