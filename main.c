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


int main() {
    srand(time(NULL));
    unsigned rows, cols;
    printf("Enter the number of rows and columns of the maze: ");
    if(scanf("%u %u",  &rows,  &cols) != 2)
    {
        printf("Incorrect input\n Exiting...\n");
        return 1;
    }
    struct cell **maze;
    int result = initialize_maze(&maze, rows, cols);
    if(result == 1)
    {
        printf("Incorrect input data\n Exiting...\n");
        return 2;
    }
    if(result == 4)
    {
        printf("Memory allocation error\n Exiting...\n");
        return 4;
    }
    generate_maze((*maze + (int)cols/2));
    printf("Generated Perfect Maze:\n");
    print_maze(maze);
    while (getchar() != '\n');
    char **maze_image;
    maze_to_memory(maze,&maze_image);
    print_maze_image(maze_image);
    destroy_maze_image(maze_image);
    printf("\nPress Enter to continue...");
    while (getchar() != '\n');
    destroy_maze(maze);
    return 0;
}
