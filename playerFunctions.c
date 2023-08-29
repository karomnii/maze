#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>
#include <math.h>

#include "dataTypes.h"
#include "playerFunctions.h"

int get_rows(char **maze_image){
    //returns -1=invalid function input otherwise returns number of rows
    if(maze_image==NULL) return -1;
    else{
        int i=0;
        while(*(maze_image+i)!=NULL) i++;
        return i;
    }
}
int get_columns(char **maze_image){
    //returns -1=invalid function input otherwise returns number of columns
    if(maze_image==NULL) return -1;
    else{
        int i=0;
        while(*(*(maze_image)+i)!='\0') i++;
        return i;
    }
}
int board_is_empty(char **maze_image){
    //returns -1=invalid function input 0= is NOT empty 1=is empty 
    if(maze_image==NULL) return -1;
    int rows=get_rows(maze_image);
    int columns=get_columns(maze_image);
    for(int i=0;i<rows;i++){
        for(int j=0;j<columns;j++){
            if(*(*(maze_image+i)+j)!=' '&&*(*(maze_image+i)+j)!='+'&&*(*(maze_image+i)+j)!='|'&&*(*(maze_image+i)+j)!='-') return 0;
        }
    }
    return 1;
}
void add_player(char **maze_image, struct point enterance_point, struct point *player_position){
    //returns: -1,-1=invalid function x,y=valid enterance point
    if(maze_image==NULL) return;
    if(player_position==NULL) return;
    int rows=get_rows(maze_image);
    int columns=get_columns(maze_image);
    if(enterance_point.x<0 || enterance_point.x>=columns || enterance_point.y<0 || enterance_point.y>=rows){
        player_position->x=-1;
        player_position->y=-1;
        return;
    }
    if(*(*(maze_image+enterance_point.y)+enterance_point.x)!=' '){
        player_position->x=-1;
        player_position->y=-1;
        return;
    }
    else{
        *(*(maze_image+enterance_point.y)+enterance_point.x)='@';
        player_position->x=enterance_point.x;
        player_position->y=enterance_point.y;
    }
}
void add_exit(char **maze_image, struct point exit_point){
    if(maze_image==NULL) return;
    int rows=get_rows(maze_image);
    int columns=get_columns(maze_image);
    if(exit_point.x<0 || exit_point.x>=columns || exit_point.y<0 || exit_point.y>=rows){
        return;
    }
    if(*(*(maze_image+exit_point.y)+exit_point.x)!=' '){
        return;
    }
    else{
        *(*(maze_image+exit_point.y)+exit_point.x)='X';
    }
}
void add_treasure(char **maze_image, struct point treasure_point){
    if(maze_image==NULL) return;
    int rows=get_rows(maze_image);
    int columns=get_columns(maze_image);
    if(treasure_point.x<0 || treasure_point.x>=columns || treasure_point.y<0 || treasure_point.y>=rows){
        return;
    }
    if(*(*(maze_image+treasure_point.y)+treasure_point.x)!=' '){
        return;
    }
    else{
        *(*(maze_image+treasure_point.y)+treasure_point.x)='$';
    }
}
int move_player(char **maze_image, struct point *player_position, enum direction player_move){
    //returns: -1=invalid function input 0=invalid move 1=valid move 2=tresure 3=finish
    if(maze_image==NULL||player_position==NULL) return -1;
    int rows=get_rows(maze_image);
    int columns=get_columns(maze_image);
    if((player_position->x<0) || (player_position->x>=columns) || (player_position->y<0) || (player_position->y>=rows)){
        return -1;
    }
    char new_board_value;
    switch (player_move)
    {
    case UP:
        if(player_position->y-1<0) return 0;
        new_board_value=*(*(maze_image+player_position->y-1)+player_position->x);
        if((new_board_value==' ') || (new_board_value=='$') || (new_board_value=='X')){
            *(*(maze_image+player_position->y-1)+player_position->x)='@';
            *(*(maze_image+player_position->y)+player_position->x)=' ';
            player_position->y--;
        } else return 0;
        break;
    case DOWN:
        if(player_position->y+1>rows) return 0;
        new_board_value=*(*(maze_image+player_position->y+1)+player_position->x);
        if((new_board_value==' ') || (new_board_value=='$') || (new_board_value=='X')){
            *(*(maze_image+player_position->y+1)+player_position->x)='@';
            *(*(maze_image+player_position->y)+player_position->x)=' ';
            player_position->y++;
        } else return 0;
        break;
    case LEFT:
        if(player_position->x-1<0) return 0;
        new_board_value=*(*(maze_image+player_position->y)+player_position->x-1);
        if((new_board_value == ' ') || (new_board_value=='$') || (new_board_value=='X')){
            *(*(maze_image+player_position->y)+player_position->x-1)='@';
            *(*(maze_image+player_position->y)+player_position->x)=' ';
            player_position->x--;
        } else return 0;
        break;
    case RIGHT:
        if(player_position->x+1>columns) return 0;
        new_board_value=*(*(maze_image+player_position->y)+player_position->x+1);
        if((new_board_value==' ') || (new_board_value=='$') || (new_board_value=='X')){
            *(*(maze_image+player_position->y)+player_position->x+1)='@';
            *(*(maze_image+player_position->y)+player_position->x)=' ';
            player_position->x++;
        } else return 0;
        break;
    default:
        return -1;
    }
    switch (new_board_value)
        {
        case ' ':
            return 1;
        case '$':
            return 2;
        case 'X':
            return 3;
        default:
            return -1;
        }
}
void player_won(int score){
    system("cls");
    fflush(stdin);
    printf("Congratulations you have won =) and scored %d points\n",score);
    printf("\nPress Enter to continue...");
    while (getchar() != '\n');
}
void end_game(){
    system("cls");
    printf("QUIT\n");
    printf("\nPress Enter to continue...");
    while (getchar() != '\n');
}