/**
 * fifteen.c
 *
 * Computer Science 50
 * Problem Set 3
 *
 * Implements Game of Fifteen (generalized to d x d).
 *
 * Usage: fifteen d
 *
 * whereby the board's dimensions are to be d x d,
 * where d must be in [DIM_MIN,DIM_MAX]
 *
 * Note that usleep is obsolete, but it offers more granularity than
 * sleep and is simpler to use than nanosleep; `man usleep` for more.
 */
 
#define _XOPEN_SOURCE 500

#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// constants
#define DIM_MIN 3
#define DIM_MAX 9

// board
int board[DIM_MAX][DIM_MAX];

// dimensions
int d;

// prototypes
void clear(void);
void greet(void);
void init(void);
void draw(void);
bool move(int tile);
bool won(void);

int searchIndexOf(int value, int values[], int n);

int main(int argc, string argv[])
{
    // ensure proper usage
    if (argc != 2)
    {
        printf("Usage: fifteen d\n");
        return 1;
    }

    // ensure valid dimensions
    d = atoi(argv[1]);
    if (d < DIM_MIN || d > DIM_MAX)
    {
        printf("Board must be between %i x %i and %i x %i, inclusive.\n",
            DIM_MIN, DIM_MIN, DIM_MAX, DIM_MAX);
        return 2;
    }

    // open log
    FILE* file = fopen("log.txt", "w");
    if (file == NULL)
    {
        return 3;
    }

    // greet user with instructions
    greet();

    // initialize the board
    init();

    // accept moves until game is won
    while (true)
    {
        // clear the screen
        clear();

        // draw the current state of the board
        draw();

        // log the current state of the board (for testing)
        for (int i = 0; i < d; i++)
        {
            for (int j = 0; j < d; j++)
            {
                fprintf(file, "%i", board[i][j]);
                if (j < d - 1)
                {
                    fprintf(file, "|");
                }
            }
            fprintf(file, "\n");
        }
        fflush(file);

        // check for win
        if (won())
        {
            printf("ftw!\n");
            break;
        }

        // prompt for move
        printf("Tile to move: ");
        int tile = GetInt();
        
        // quit if user inputs 0 (for testing)
        if (tile == 0)
        {
            break;
        }

        // log move (for testing)
        fprintf(file, "%i\n", tile);
        fflush(file);

        // move if possible, else report illegality
        if (!move(tile))
        {
            printf("\nIllegal move.\n");
            usleep(5000);
        }

        // sleep thread for animation's sake
        usleep(5000);
    }
    
    // close log
    fclose(file);

    // success
    return 0;
}

/**
 * Clears screen using ANSI escape sequences.
 */
void clear(void)
{
    printf("\033[2J");
    printf("\033[%d;%dH", 0, 0);
}

/**
 * Greets player.
 */
void greet(void)
{
    clear();
    printf("WELCOME TO GAME OF FIFTEEN\n");
    usleep(2000000);
}

/**
 * Initializes the game's board with tiles numbered 1 through d*d - 1
 * (i.e., fills 2D array with values but does not actually print them).  
 */
void init(void)
{
    int num = (d*d);
    for(int i = 0; i < d; i++)
    {
        
        for (int j = 0; j < d; j++)
        {
            num -= 1; 
            if (i == d-1 && j == d-1)
            {
                board[i][j] = 0;
            }
            else 
            {
                board[i][j] = num;
            }
            
        }
    }
    
    if(d == 4)
    {
        // switch the two and one
        board[3][2] = 2;
        board[3][1] = 1;
    }
    
}

/**
 * Prints the board in its current state.
 */
void draw(void)
{
    printf("\n");
    for(int i = 0; i < d; i++)
    {
        if (d == 3)
        {
            printf(" ");
        }
        for (int j = 0; j < d; j++)
        {
            printf(" ");
          
            if (board[i][j] < 10)
            {
                printf(" ");
            }
            if (board[i][j] == 0)
            {
                printf("_");
            }
            else
            {
                printf("%i", board[i][j]);
            }
        }
        printf("\n\n");
    }
}

/**
 * If tile borders empty space, moves tile and returns true, else
 * returns false. 
 */
bool move(int tile)
{
    if (tile > (d*d)-1)
    {
        return false;
    }
    
    int column, row;
    
    for(int i = 0; i < d; i++)
    {
        int place = searchIndexOf(tile, board[i], d); 
        
        if (place != -1)
        {
            row = i;            
            column = place; 
        }
    }
    
    bool hasMove = false; 

    // check above 
    if (row - 1 < d && row - 1 >= 0)
    {
        hasMove = board[row - 1][column] == 0 ? true : hasMove;
    }
    
    // check left 
    if (column - 1 < d && column - 1 >= 0)
    {
        hasMove = board[row][column - 1] == 0 ? true : hasMove; 
    }
    
    // check right 
    if (column + 1 < d && column + 1 >= 0)
    {
        hasMove = board[row][column + 1] == 0 ? true : hasMove; 
    }
    
    // check below 
    if (row + 1 < d && row + 1 >= 0)
    {
        hasMove = board[row + 1][column] == 0 ? true : hasMove; 
    }

    if (hasMove)
    {
        // swap the two items in the data
        
        int blankRow, blankColumn;
        
        for(int i = 0; i < d; i++)
        {
            int place = searchIndexOf(0, board[i], d); 
        
            if (place != -1)
            {
                blankRow = i;            
                blankColumn = place; 
            }
        }
        
        board[blankRow][blankColumn] = tile; 
        board[row][column] = 0;
    }


    return hasMove;
}

/**
 * Returns true if game is won (i.e., board is in winning configuration), 
 * else false.
 */
bool won()
{
    int num = 0; 
    
    for (int i = 0; i < d; i++)
    {
        for (int j = 0; j < d; j++)
        {
            num += 1;
            
            // if the number is what it should be continue
            if(num == board[i][j])
            {
                continue;
            }
            // if it isn't, but is the last item and is 0 then we're done
            else if (board[i][j] == 0 && i == d-1 && j == d-1 && num == d*d)
            {
                return true; 
            }
            // otherwise false
            else 
            {
                return false;
            }
        }
    }
     
    return false; 
}

// lineary searches and returns the index of an item in array
// made linear because we can't assume it's sorted and at most it iterates over 9 places
int searchIndexOf(int value, int values[], int n)
{
    for(int i = 0; i<n; i++)
    {
        if (values[i] == value)
        {
            return i;
        }
    }
    
    return -1;
}
