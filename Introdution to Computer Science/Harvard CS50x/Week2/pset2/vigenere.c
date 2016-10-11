#include <stdio.h>
#include <cs50.h> 
#include <string.h> 
#include <ctype.h>

char CryptCaesar(char c, int key);

int main(int argc, char *argv[])
{
     if (argc != 2)
    {
        printf("Usage: %s <keyword>\n", argv[0]);
        return 1;
    }
    
    string keyword = argv[1];
    
    for(int i = 0; i<strlen(keyword);i++)
    {
        if (isdigit(keyword[i]))
        {
            printf("Keyword must only contain letters A-Z and a-z\n");
            return 1; 
        }
    }
    
    int currentKeywordIndex = 0; 
    
    string phrase = GetString(); 
    
    for(int i = 0; i<strlen(phrase); i++)
    {

        char letter = keyword[currentKeywordIndex];
        if (isupper(phrase[i]) || islower(phrase[i]))
        {
            int key = tolower(letter)-97;
            printf("%c", CryptCaesar(phrase[i], key));
            currentKeywordIndex = (currentKeywordIndex + 1) % strlen(keyword);
        }
        else
        {
            printf("%c", phrase[i]);
        }
        
    }
    printf("\n");
    return 0; 
}

char CryptCaesar(char c, int key)
{
    int current = (int) c; 
    
    if (islower(current))
    {
        current += key;            
        if (current > 'z')
        {
            current = (current - 'z') + ('a'-1);
        }
    }
    else if (isupper(current))
    {
        current += key;
        if (current > 'Z')
        {
            current = (current - 'Z') + ('A'-1);
        }
    }
    return (char)current;
}