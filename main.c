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
    printf("Enter the number of rows and columns of the maze[example: \"10 10 -enter-\"]: ");
    if(scanf("%u %u",  &rows,  &cols) != 2)
    {
        printf("Incorrect input\n Exiting...\n");
        return 1;
    }
    printf("Choose game mode\n 1-You see the whole labyrinth\n 2-you see maximum 3 spaces ahead\n 3-you see maximum 1 spaces ahead\n mode: ");
    unsigned int game_mode;
    if(scanf("%u",  &game_mode) != 1)
    {
        printf("Incorrect input\n Exiting...\n");
        return 1;
    }
    if(game_mode>3) {
        printf("Incorrect input data\n Exiting...\n");
        return 2;
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
    char **maze_image;
    maze_to_memory(maze,&maze_image);
    destroy_maze(maze);
    //only chars for now
    struct point player_location;
    struct point start;
    start.x=1;
    start.y=1;
    struct point end;
    end.x=(cols)*4-1;
    end.y=(rows)*2-1;
    add_player(maze_image,start,&player_location);
    add_exit(maze_image,end);
    print_maze_image(maze_image);
    
    //need to get into this for now chatgpt generated
    HANDLE hStdin = GetStdHandle(STD_INPUT_HANDLE);
    DWORD mode;
    GetConsoleMode(hStdin, &mode);
    SetConsoleMode(hStdin, mode & (~ENABLE_ECHO_INPUT) & (~ENABLE_LINE_INPUT)); //sets console to input without pressing enter
    char current=' ';
    int score=0;
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
                    player_won(score);
                    return 0;
                }
                if(result==2) score++;
                if(result!=1) continue;
                break;
            case 'a':
            case 'A':
            case (char)37: //arows are not working
                result=move_player(maze_image,&player_location,LEFT);
                if(result==3){
                    destroy_maze_image(maze_image);
                    player_won(score);
                    return 0;
                }
                if(result==2) score++;
                if(result!=1) continue;
                break;
            case 's':
            case 'S':
            case (char)40: //arows are not working
                result=move_player(maze_image,&player_location,DOWN);
                if(result==3){
                    destroy_maze_image(maze_image);
                    player_won(score);
                    return 0;
                }
                if(result==2) score++;
                if(result!=1) continue;
                break;
            case 'd':
            case 'D':
            case (char)39: //arows are not workingfds
                result=move_player(maze_image,&player_location,RIGHT);
                if(result==3){
                    destroy_maze_image(maze_image);
                    player_won(score);
                    return 0;
                }
                if(result==2) score++;
                if(result!=1) continue;
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
            if(game_mode==1) print_maze_image(maze_image);
            else if(game_mode==2) print_maze_mode_2(maze_image,&player_location);
        }
    }
}
