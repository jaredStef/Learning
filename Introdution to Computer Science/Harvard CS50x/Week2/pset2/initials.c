#include <stdio.h>
#include <cs50.h>
#include <string.h> 
#include <ctype.h>

int main(int argc, char *argv[])
{
    string name = GetString(); 
    char* currentWord = strtok(name, " ");
    
    while (currentWord != NULL)
    {
        char firstChar = currentWord[0];
        
        if (islower(firstChar))
        {
            firstChar = toupper(firstChar);
        }
        
        printf("%c", firstChar);
        currentWord = strtok(NULL, " "); 
    }
    
    printf("\n");
    return 0; 
}