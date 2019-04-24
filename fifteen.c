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

//#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>

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

int main(int argc, char* argv[])
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
        int tile = 0;
        scanf("%d", &tile);

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
            usleep(500000);
        }

        // sleep thread for animation's sake
        usleep(500000);
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
    usleep(1000000);
}

/**
 * Initializes the game's board with tiles numbered 1 through d*d - 1
 * (i.e., fills 2D array with values but does not actually print them).
 */
void init(void)
{
    // TODO
    // Tile numbers
    int numbers = (d*d) - 1;

    if((numbers%2) == 0)
    {
        for(int i = 0; i < d; i++)
        {
            for(int j = 0; j < d; j++)
            {
                board[i][j] = numbers;
                numbers--;
            }
        }
    }
    else
    {
        for(int i = 0; i < d; i++)
        {
            for(int j = 0; j < d; j++)
            {
                if(numbers == 2)
                    board[i][j] = 1;
                else if(numbers == 1)
                    board[i][j] = 2;
                else
                    board[i][j] = numbers;

                numbers--;
            }
        }
    }
}

/**
 * Prints the board in its current state.
 */
void draw(void)
{
    // TODO
    for(int i = 0; i < d; i++)
    {
        printf("\n  ");
        for(int j = 0; j < d; j++)
        {
            if(board[i][j] == 0)
                printf("  _ ");
            else
                printf(" %2d ", board[i][j]);
        }
        printf("\n");
    }
}

/**
 * If tile borders empty space, moves tile and returns true, else
 * returns false.
 */
bool move(int tile)
{
    // TODO
    int tilePosR, tilePosC, zPosR, zPosC;
    for(int i = 0; i < d; i++)
    {
        for(int j = 0; j < d; j++)
        {
            if(board[i][j] == tile)
            {
                tilePosR = i;
                tilePosC = j;
            }

            if(board[i][j] == 0)
            {
                zPosR = i;
                zPosC = j;
            }
        }
    }

    if((tilePosR == zPosR && (tilePosC == (zPosC+1) || tilePosC == (zPosC-1))) || (tilePosC == zPosC && (tilePosR == (zPosR+1) || tilePosR == (zPosR-1))))
    {
        int tmp = board[tilePosR][tilePosC];
        board[tilePosR][tilePosC] = board[zPosR][zPosC];
        board[zPosR][zPosC] = tmp;
        return true;
    }

    return false;
}

/**
 * Returns true if game is won (i.e., board is in winning configuration),
 * else false.
 */
bool won(void)
{
    // TODO
    int value = 1;

    for(int i = 0; i < d; i++)
    {
        for(int j = 0; j < d; j++)
        {
            if(i == d-1 && j == d-1)
                value = 0;

            if(board[i][j] != value)
                return false;

            value++;
        }
    }

    return true;
}





















