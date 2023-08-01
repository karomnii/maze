#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>
#include <math.h>

#include "dataTypes.h"
#include "mazeGeneration.h"

#include <ctype.h> // for isalpha(), isdigit(), islower(), isupper(), tolower(), toupper() functions
#include <windows.h> // for Sleep() function
#include <limits.h> // for INT_MAX and INT_MIN
#include <float.h> // for FLT_MAX and FLT_MIN
#include <assert.h> // for assert() function 
#include <locale.h> // for setlocale() function
#include <iso646.h> // for and, or, not 
#include <stdarg.h> // for va_start(), va_arg(), va_end() macros
#include <stddef.h> // for NULL macro
#include <stdint.h> // for intmax_t, uintmax_t types
#include <fenv.h> // for floating-point control functions


#define ROWS 10
#define COLS 10






int main() {
    srand(time(NULL));
    struct cell maze[ROWS][COLS];
    for (size_t i = 0; i < ROWS; i++)
    {
        for (size_t j = 0; j < COLS; j++)
        {
            maze[i][j].x = i;
            maze[i][j].y = j;
            maze[i][j].visited = false;
            if(i == 0)
                maze[i][j].up = NULL;
            else
                maze[i][j].up = &maze[i-1][j];
            if(i == ROWS-1)
                maze[i][j].down = NULL;
            else
                maze[i][j].down = &maze[i+1][j]; 
            if(j == 0)
                maze[i][j].left = NULL;
            else
                maze[i][j].left = &maze[i][j-1];
            if(j == COLS-1)
                maze[i][j].right = NULL;
            else
                maze[i][j].right = &maze[i][j+1];
            maze[i][j].up_wall = true;
            maze[i][j].down_wall = true;
            maze[i][j].left_wall = true;
            maze[i][j].right_wall = true;
        }
    }
    generate_maze(maze, &maze[0][0]);

    printf("Generated Perfect Maze:\n");
    for (size_t i = 0; i < ROWS; i++)
    {
        for (size_t j = 0; j < COLS; j++)
        {
            printf("+");
            if(maze[i][j].up_wall == true)
                printf("---");
            else
                printf("   ");
        }
        printf("+\n");
        for (size_t j = 0; j < COLS; j++)
        {
            if(maze[i][j].left_wall == true)
                printf("|");
            else
                printf(" ");
            if(maze[i][j].visited == true)
                printf(" * ");
            else
                printf("   ");
        }
        if(maze[i][COLS-1].right_wall == true)
            printf("|");
        else
            printf(" ");
        printf("\n");
    }
    for (size_t j = 0; j < COLS; j++)
        {
            printf("+");
            printf("---");
        }
    printf("+");
    return 0;
}
