// Problem 37 - Sudoku solver
// https://leetcode.com/problems/sudoku-solver/

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>

#define SIZE (9)

// Sudoku board
typedef struct Sudoku {
    uint8_t board[SIZE][SIZE];  // Entire 9x9 sudoku board (values 0 to 9, 0 means unfilled)
    
    // Which 1 to 9 values were used in each row, column, or 3x3 subgrid
    bool row[SIZE][SIZE+1]; // Rows from top to bottom
    bool col[SIZE][SIZE+1]; // Columns from left to right
    bool box[SIZE][SIZE+1]; // Subgrids from left to right, then top to bottom
} Sudoku;

// Set the cell at a given (x,y) coordinate to a value from 0 to 9
// A value of 0 means that the cell is empty.
static inline void set_value(Sudoku* puzzle, size_t y, size_t x, uint8_t value)
{
    if (value > 9) __builtin_unreachable();
    
    // Index of the 3x3 subgrid
    const size_t s = (y/3) * 3 + (x/3);
    
    if (value != 0)
    {
        // Place the value to the board
        puzzle->board[y][x] = value;
        puzzle->row[y][value] = puzzle->col[x][value] = puzzle->box[s][value] = true;
    }
    else // value == 0
    {
        // Remove the value from the board
        const uint8_t n = puzzle->board[y][x];  // Old value
        puzzle->board[y][x] = 0;
        puzzle->row[y][n] = puzzle->col[x][n] = puzzle->box[s][n] = false;
    }
}

static void solve(Sudoku* puzzle, bool* solved)
{
    if (*solved) return;

    // Coordinates of the cell with the least amount of value's possibilities 
    size_t max_i = 0;       // Row's index
    size_t max_j = 0;       // Column's index
    size_t max_count = 0;   // Maximum counter of the amount of different values
    size_t filled = 0;      // How many cells are filled with a value from 1 to 9

    // Find the cell with the least amount of value's possibilities
    for (size_t i = 0; i < SIZE; i++)
    {
        for (size_t j = 0; j < SIZE; j++)
        {
            // Skip filled cells
            if (puzzle->board[i][j] != 0)
            {
                filled++;
                continue;
            }
            
            const size_t k = (i/3) * 3 + (j/3); // Index of the 3x3 subgrid
            size_t count = 0;   // Amount of different values in the row, column, and subgrid

            // Count the different values
            for (size_t n = 1; n <= SIZE; n++)
            {
                if (puzzle->row[i][n] || puzzle->col[j][n] || puzzle->box[k][n])
                {
                    count++;
                }
            }
            
            // Update the coordinates of the cell with the least amount of value's possibilities
            if (count > max_count)
            {
                max_i = i;
                max_j = j;
                max_count = count;
                if (count == SIZE - 1) goto exit_loop;  // If count is 8 there is only one possibility for the value
            }
        }
    }

    exit_loop:

    // Check if all cells are filled, which means that the puzzle was solved
    if (filled >= (SIZE * SIZE))
    {
        *solved = true;
        return;
    }

    // If there are no possible values, we reached an dead end
    if (max_count == 0) return;

    // Test all possible values for the cell
    for (uint8_t n = 1; n <= SIZE; n++)
    {
        const size_t max_k = (max_i/3) * 3 + (max_j/3);
        if (!(puzzle->row[max_i][n] || puzzle->col[max_j][n] || puzzle->box[max_k][n]))
        {
            // Place the value on the cell and try solving the resulting board
            set_value(puzzle, max_i, max_j, n);
            solve(puzzle, solved);
            
            // Check if the puzzle was solved
            if ( !(*solved) )
            {
                // Remove the value if led to a dead end
                set_value(puzzle, max_i, max_j, 0);
            }
            else
            {
                // Keep the value if it led to the solution
                return;
            }
        }
    }
}

void solveSudoku(char** board, int boardSize, int* boardColSize)
{
    Sudoku puzzle = {0};
    
    // Iterate over the rows
    for (size_t i = 0; i < SIZE; i++)
    {
        // Iterate over the columns
        for (size_t j = 0; j < SIZE; j++)
        {
            // Place the value on the board
            if (board[i][j] != '.')
            {
                const uint8_t num = board[i][j] - '0';  // 1 to 9 value of the cell
                set_value(&puzzle, i, j, num);
            }
        }
    }

    bool solved = false;
    solve(&puzzle, &solved);

    // Copy the solved board to the output
    for (size_t i = 0; i < SIZE; i++)
    {
        for (size_t j = 0; j < SIZE; j++)
        {
            board[i][j] = puzzle.board[i][j] + '0';
        }
    }

    *boardColSize = SIZE;
}
