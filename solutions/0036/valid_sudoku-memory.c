// Problem 36 - Valid Sudoku
// https://leetcode.com/problems/valid-sudoku/description/

// Note: this version of the solution aims to minimize memory usage

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>

#define SIZE (9)

// Which 1 to 9 values were used in each row, column, or 3x3 subgrid
typedef struct Sudoku {
    bool row[SIZE][SIZE];   // Rows from top to bottom
    bool col[SIZE][SIZE];   // Columns from left to right
    bool box[SIZE][SIZE];   // 3x3 subgrids from left to right, then top to bottom
} Sudoku;

bool isValidSudoku(char** board, int boardSize, int* boardColSize)
{
    Sudoku sudoku = {0};
    
    // Iterate over the rows
    for (size_t i = 0; i < SIZE; i++)
    {
        // Iterate over the columns
        for (size_t j = 0; j < SIZE; j++)
        {
            if (board[i][j] != '.')
            {
                const size_t num = board[i][j] - '0' - 1;   // 0 to 8 index of the cell
                const size_t k = (i/3) * 3 + (j/3);         // Index of the 3x3 subgrid
                
                // Check if the value is already present in the row, column, or subgrid
                if (sudoku.row[i][num] || sudoku.col[j][num] || sudoku.box[k][num])
                {
                    return false;
                }
                else
                {
                    sudoku.row[i][num] = sudoku.col[j][num] = sudoku.box[k][num] = true;
                }
            }
        }
    }

    return true;
}
