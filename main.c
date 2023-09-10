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
#include "mazeprinting.h"



int main() {
    srand(time(NULL));
    unsigned input_rows, input_cols;
    printf("Enter the number of rows and columns of the maze[example: \"10 10 -enter-\"]: ");
    if(scanf("%u %u",  &input_rows,  &input_cols) != 2)
    {
        printf("Incorrect input\n Exiting...\n");
        return 1;
    }
    system("cls");
    printf("Choose game mode\n 1-You see the whole labyrinth(boring)\n 2-you can't see through walls and your view is maximum 3 spaces ahead \n 3-you can see through walls but it is only 5 sapces ahead(better for bigger labyrinths)\n 4-mode 2 but with 2x2 arts\n mode: ");
    unsigned int game_mode;
    if(scanf("%u",  &game_mode) != 1)
    {
        printf("Incorrect input\n Exiting...\n");
        return 1;
    }
    if(game_mode>4) {
        printf("Incorrect input data\n Exiting...\n");
        return 2;
    }
    system("cls");
    char **mode_4_buffer;
    if(game_mode==4){
        mode_4_buffer=buffer_for_mode_4();
        if(mode_4_buffer==NULL){
            printf("Memory allocation error\n Exiting...\n");
            return 4;
        }
    }
    struct cell **maze;
    int result = initialize_maze(&maze, input_rows, input_cols);
    if(result == 1)
    {
        if(game_mode==4) destroy_mode_4_array(mode_4_buffer);
        printf("Incorrect input data\n Exiting...\n");
        return 2;
    }
    if(result == 4)
    {
        if(game_mode==4) destroy_mode_4_array(mode_4_buffer);
        printf("Memory allocation error\n Exiting...\n");
        return 4;
    }
    generate_maze((*maze + (int)input_cols/2));
    char **maze_image;
    maze_to_memory(maze,&maze_image);
    destroy_maze(maze);
    //only chars from now on
    struct player player_location;
    struct point start={1,1};
    struct point end={(input_cols)*4-1,(input_rows)*2-1};
    add_player(maze_image,start,&player_location.position);
    add_exit(maze_image,end);

    int rows=get_rows(maze_image),cols=get_columns(maze_image); //get rows and cols of the image
    
    // Get handles to the standard input
    HANDLE hStdin = GetStdHandle(STD_INPUT_HANDLE);

    DWORD mode;
    GetConsoleMode(hStdin, &mode);
    // sets console to input mode without pressing enter
    SetConsoleMode(hStdin, mode & (~ENABLE_ECHO_INPUT) & (~ENABLE_LINE_INPUT));
    // not working
    // HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
    // CONSOLE_FONT_INFOEX fontInfo;
    // fontInfo.cbSize = sizeof(CONSOLE_FONT_INFOEX);
    // GetCurrentConsoleFontEx(hStdOut, FALSE, &fontInfo);
    // fontInfo.dwFontSize.X = 8; // Font width
    // fontInfo.dwFontSize.Y = 16; // Font height
    // SetCurrentConsoleFontEx(hStdOut, FALSE, &fontInfo);

    // Get handle to the standard output
    HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
    // Change console properties
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(hStdOut, &csbi);

    COORD newSize; // Set the new size (columns, rows)
    switch (game_mode)
    {
    case 1:
        newSize.X =cols;
        newSize.Y =rows+1;
        break;
    case 2:
        newSize.X =8;
        newSize.Y =6;
        break;
    case 3:
        newSize.X =18;
        newSize.Y =12;
        break;
    case 4:
        newSize.X =14;
        newSize.Y =10;
        break;

    default:
        newSize.X =200;
        newSize.Y =100;
        break;
    }
    SMALL_RECT srWindow = {0, 0, newSize.X - 1, newSize.Y - 1};
    SetConsoleWindowInfo(hStdOut, TRUE, &srWindow);
    SetConsoleScreenBufferSize(hStdOut, newSize);
    newSize.X =200;
    newSize.Y =100;

    // Change text color
    SetConsoleTextAttribute(hStdOut, FOREGROUND_RED | FOREGROUND_INTENSITY);

    if(game_mode==4) print_maze_mode_4(maze_image,&(player_location.position),mode_4_buffer); 
    else print_maze(maze_image,&player_location,game_mode);
    char current=' ';
    int score=0;
     while (1) {
        if (_kbhit()) {
            current = (char)_getch();
            switch (current)
            {
            case 'w':
            case 'W':
                result=move_player(maze_image,&player_location,UP);
                if(result==3){
                    if(game_mode==4) destroy_mode_4_array(mode_4_buffer);
                    destroy_maze_image(maze_image);
                    SetConsoleTextAttribute(hStdOut, csbi.wAttributes);
                    SetConsoleScreenBufferSize(hStdOut, newSize);
                    player_won(score);
                    return 0;
                }
                if(result==2) score++;
                if(result!=1) continue;
                break;
            case 'a':
            case 'A':
                result=move_player(maze_image,&player_location,LEFT);
                if(result==3){
                    if(game_mode==4) destroy_mode_4_array(mode_4_buffer);
                    destroy_maze_image(maze_image);
                    SetConsoleTextAttribute(hStdOut, csbi.wAttributes);
                    SetConsoleScreenBufferSize(hStdOut, newSize);
                    player_won(score);
                    return 0;
                }
                if(result==2) score++;
                if(result!=1) continue;
                break;
            case 's':
            case 'S':
                result=move_player(maze_image,&player_location,DOWN);
                if(result==3){
                    if(game_mode==4) destroy_mode_4_array(mode_4_buffer);
                    destroy_maze_image(maze_image);
                    SetConsoleTextAttribute(hStdOut, csbi.wAttributes);
                    SetConsoleScreenBufferSize(hStdOut, newSize);
                    player_won(score);
                    return 0;
                }
                if(result==2) score++;
                if(result!=1) continue;
                break;
            case 'd':
            case 'D':
                result=move_player(maze_image,&player_location,RIGHT);
                if(result==3){
                    if(game_mode==4) destroy_mode_4_array(mode_4_buffer);
                    destroy_maze_image(maze_image);
                    SetConsoleTextAttribute(hStdOut, csbi.wAttributes);
                    SetConsoleScreenBufferSize(hStdOut, newSize);
                    player_won(score);
                    return 0;
                }
                if(result==2) score++;
                if(result!=1) continue;
                break;
            case 'q':
            case 'Q':
                if(game_mode==4) destroy_mode_4_array(mode_4_buffer);
                destroy_maze_image(maze_image);
                SetConsoleTextAttribute(hStdOut, csbi.wAttributes);
                end_game();
                return 0;
            default:
                continue;
            }
            system("cls");
            if(game_mode==4) print_maze_mode_4(maze_image,&(player_location.position),mode_4_buffer); else
            print_maze(maze_image,&player_location,game_mode);
        }
    }
}
