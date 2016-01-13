#include <stdio.h>
#include <cs50.h>
#include <string.h>

void PrintInitialsInString(string characters);

int main (void)
{
  // return first initals of entered strings ex  Jared STefaneicz = JS
  printf("Enter your name: ");
  string name = GetString();
  PrintInitialsInString(name);
  return 0;
}

void PrintInitialsInString(string characters)
{
  bool inWord = false;

  for (int i = 0; i < strlen(characters);i++)
  {
    if (characters[i] == ' ')
    {
      inWord = false;
    }
    else
    {
      // if I am not in a word, but it's not a space (so start of word)
      // and it's not the null termintor print it as first character
      if (!inWord && characters[i] != 0)
      {
        char c = characters[i];
        // if it is lowercase make capital per ASCII chart
        if (c > 96)
        {
          c -= 32;
        }
        printf("%c",c);
      }
      inWord = true;
    }
  }
  printf("\n");
}
