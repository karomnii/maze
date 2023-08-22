#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>
#include <math.h>
#include <conio.h> 
#include <windows.h>

#include "dataTypes.h"
#include "mazeGeneration.h"
#include "playerFunctions.h"



int main() {
    srand(time(NULL));
    unsigned rows, cols;
    printf("Enter the number of rows and columns of the maze: ");
    if(scanf("%u %u",  &rows,  &cols) != 2)
    {
        printf("Incorrect input\n Exiting...\n");
        return 1;
    }
    system("cls");
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
    while (getchar() != '\n');
    char **maze_image;
    maze_to_memory(maze,&maze_image);
    print_maze_image(maze_image);
    struct point player_location;
    struct point start;
    start.x=1;
    start.y=1;
    struct point end;
    end.x=cols*4-1;
    end.y=rows*2-1;
    add_player(maze_image,start,&player_location);
    add_exit(maze_image,end);
    
    //need to get into this for now chatgpt generated
    HANDLE hStdin = GetStdHandle(STD_INPUT_HANDLE);
    DWORD mode;

    GetConsoleMode(hStdin, &mode);
    SetConsoleMode(hStdin, mode & (~ENABLE_ECHO_INPUT) & (~ENABLE_LINE_INPUT)); //sets console to input without pressing enter
    // a little bit of chatgpt work
    // while (1) {
    //     if (_kbhit()) {
    //         int key = _getch();  // Get the key without waiting
    //         if (key == 27) {     // Check for the Esc key (ASCII value 27)
    //             break;           // Exit the loop if Esc is pressed
    //         }
    //         printf("Key pressed: %c\n", key);
    //     }
    // }
    char current=' ';
     while (1) {
        if (_kbhit()) {
            current = (char)_getch();
            switch (current)
            {
            case 'w':
            case 'W':
                printf("UP\n");
                break;
            case 'a':
            case 'A':
                printf("LEFT\n");
                break;
            case 's':
            case 'S':
                printf("DOWN\n");
                break;
            case 'd':
            case 'D':
                printf("RIGHT\n");
                break;
            case 'q':
            case 'Q':
                system("cls");
                printf("QUIT\n");
                destroy_maze_image(maze_image);
                printf("\nPress Enter to continue...");
                while (getchar() != '\n');
                destroy_maze(maze);
                return 0;
            default:
                printf("INVALID INPUT\n");
                break;
            }
        }
    }
}
