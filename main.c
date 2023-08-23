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
    destroy_maze(maze);
    //only chars for now
    print_maze_image(maze_image);
    struct point player_location;
    struct point start;
    start.x=1;
    start.y=1;
    struct point end;
    end.x=(cols)*4-1;
    end.y=(rows)*2-1;
    print_maze_image(maze_image);
    add_player(maze_image,start,&player_location);
    print_maze_image(maze_image);
    add_exit(maze_image,end);
    print_maze_image(maze_image);
    
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
            case (char)38: //arows are not working
                result=move_player(maze_image,&player_location,UP);
                if(result==3){
                    destroy_maze_image(maze_image);
                    player_won();
                    return 0;
                }
                if(result!=1) continue;
                break;
                break;
            case 'a':
            case 'A':
            case (char)37: //arows are not working
                result=move_player(maze_image,&player_location,LEFT);
                if(result==3){
                    destroy_maze_image(maze_image);
                    player_won();
                    return 0;
                }
                if(result!=1) continue;
                break;
            case 's':
            case 'S':
            case (char)40: //arows are not working
                result=move_player(maze_image,&player_location,DOWN);
                if(result==3){
                    destroy_maze_image(maze_image);
                    player_won();
                    return 0;
                }
                if(result!=1) continue;
                break;
                break;
            case 'd':
            case 'D':
            case (char)39: //arows are not workingfds
                result=move_player(maze_image,&player_location,RIGHT);
                if(result==3){
                    destroy_maze_image(maze_image);
                    player_won();
                    return 0;
                }
                if(result!=1) continue;
                break;
                break;
            case 'q':
            case 'Q':
                destroy_maze_image(maze_image);
                end_game();
                return 0;
            default:
                continue;
            }
            system("cls");
            print_maze_image(maze_image);
        }
    }
}
