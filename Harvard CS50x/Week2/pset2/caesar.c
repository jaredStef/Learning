#include <stdio.h>
#include <cs50.h> 
#include <string.h> 
#include <ctype.h>

char CryptCaesar(char c, int key);

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Usage %s <key>\n", argv[0]);
        return 1;
    }
    
    int key = atoi(argv[1]);
    
    if (key > 26)
    {
        key %= 26;
    }
    
    string message = GetString(); 
    
    for (int i = 0; i < strlen(message); i++) 
    {
        printf("%c", CryptCaesar(message[i], key));
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