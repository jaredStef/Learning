#include <stdio.h>
#include <cs50.h>

int main()
{
    printf("minutes: ");
    int mins = GetInt();
    printf("bottles: %i\n", mins*12);

    return 0;
}
