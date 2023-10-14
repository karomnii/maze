#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>
#include <math.h>

#include "dataTypes.h"
#include "mazeGeneration.h"
#include "playerFunctions.h"
#include "mazeprinting.h"

void print_maze(char **maze_image,struct player *player_position,int mode){
    if(maze_image==NULL || player_position==NULL) return;
    switch(mode){
        case 1:
            print_maze_mode_1(maze_image);
            break;
        case 2:
            print_maze_mode_2(maze_image,&player_position->position);
            break;
        case 3:
            print_maze_mode_3(maze_image,&player_position->position);
            break;
        default:
            return;
    }
}
void print_maze_mode_1(char **maze_image){
    if(maze_image==NULL) return;
    for (size_t i = 0; *(maze_image+i)!=NULL; i++)
    {
        printf("%s\n",*(maze_image+i));
    }
}
void print_maze_mode_2(char **maze_image,struct point *player_position){
    if(maze_image==NULL) return;
    if(player_position==NULL) return;
    int rows=get_rows(maze_image);
    int cols=get_columns(maze_image);
    if((player_position->x<0) || (player_position->x>=cols) || (player_position->y<0) || (player_position->y>=rows)){
        return;
    }
    int start_cols,start_rows,end_cols,end_rows;
    if(player_position->y<=1) start_rows=0;
    else start_rows=player_position->y-2;
    if(player_position->x<=2) start_cols=0;
    else start_cols=player_position->x-3;
    if((rows-player_position->y-1)<=2) end_rows=rows;
    else end_rows=player_position->y+3;
    if((cols-player_position->x-1)<=3) end_cols=cols;
    else end_cols=player_position->x+4;
    // printf("player postion y:%d x:%d rows:%d cols:%d start cols=%d start rows=%d end cols=%d end rows=%d\n",player_position->y,player_position->x,rows,cols,start_cols,start_rows,end_cols,end_rows); // for debugging
    
    if(player_position->y<=1) for (size_t i = 0; i < 2-player_position->y; i++) {
        for (size_t j = 0; j < 7; j++) printf("#");
        printf("\n");
    }
    
    for (size_t i = start_rows; i < end_rows; i++)
    {
        if(player_position->x<=2) for (size_t j = 0; j < 3-player_position->x; j++) printf("#");
        
        for (size_t j = start_cols; j < end_cols; j++)
        {
            if(*(*(maze_image+i)+j)=='@') printf("@");
            else if(*(*(maze_image+i)+j)=='X') printf("X");
            else if(*(*(maze_image+i)+j)==' '&&is_visible(maze_image,player_position,j,i)) printf(" ");
            else printf("#");
        }

        if((cols-player_position->x-1)<=3) for (size_t j = 0; j < 3-(cols-player_position->x-1); j++) printf("#");

        printf("\n");
    }

    if((rows-player_position->y-1)<=2) for (size_t i = 0; i < 2-(rows-player_position->y-1); i++) {
        for (size_t j = 0; j < 7; j++) printf("#");
        printf("\n");
    }
    
}
void print_maze_mode_3(char **maze_image, struct point *player_position){
    if(maze_image==NULL || player_position==NULL) return;
    int cols=get_columns(maze_image);
    int rows=get_rows(maze_image);
    for (size_t i = 0; i < 11; i++)
    {   
        if((player_position->y+i-5)<0) {
            printf("#################\n");
            continue;
        }
        if((player_position->y+i-5)>=rows){
            printf("#################\n");
            continue;
        }
        for (size_t j = 0; j < 17; j++)
        {   
            if((player_position->x+j-8)<0) {
                printf("#");
                continue;
            }
            if((player_position->x+j-8)>(cols-1)) {
                printf("#");
                continue;
            }
            printf("%c",*(*(maze_image+player_position->y+i-5)+player_position->x-8+j));
        }
        printf("\n");
    }
}
int is_visible(char **maze_image,struct point *player_position,int x, int y){
    if(maze_image==NULL||player_position==NULL||x<0||y<0) return 0;

    if(*(*(maze_image+y)+x)!=' ') return 0;

    if(((x+1==player_position->x)&&(y+1==player_position->y))
    ||((x-1==player_position->x)&&(y+1==player_position->y))
    ||((x+1==player_position->x)&&(y-1==player_position->y))
    ||((x-1==player_position->x)&&(y-1==player_position->y))) return 1; //player corners
    
    //the oldest part, doesnt use recursion
    if(y==player_position->y){
        int diff;
        if(player_position->x>x){ //player is to the right of the point
            diff=player_position->x-x;
            switch (diff)
            {
            case 1:
                return 1;
            case 2:
                if(*(*(maze_image+y)+x+1)==' ') return 1;
                else return 0;
            case 3:
                if(*(*(maze_image+y)+x+2)==' '&&*(*(maze_image+y)+x+1)==' ') return 1;
                else return 0;
            default:
                return 0;
            }
        } else //player is to the left of the point
        {
            diff=x-player_position->x;
            switch (diff)
            {
            case 1:
                return 1;
            case 2:
                if(*(*(maze_image+y)+x-1)==' ') return 1;
                else return 0;
            case 3:
                if(*(*(maze_image+y)+x-2)==' '&&*(*(maze_image+y)+x-1)==' ') return 1;
                else return 0;
            default:
                return 0;
            }
        }
    } else if(x==player_position->x){
        int diff;
        if(player_position->y>y){ //player is lower than the point
            diff=player_position->y-y;
            switch (diff)
            {
            case 1:
                return 1;
            case 2:
                if(*(*(maze_image+y+1)+x)==' ') return 1;
                else return 0;
            case 3:
                if(*(*(maze_image+y+2)+x)==' '&&*(*(maze_image+y+1)+x)==' ') return 1;
                else return 0;
            default:
                return 0;
            }
        } else //player is higher than the point
        {
            diff=y-player_position->y;
            switch (diff)
            {
            case 1:
                return 1;
            case 2:
                if(*(*(maze_image+y-1)+x)==' ') return 1;
                else return 0;
            case 3:
                if(*(*(maze_image+y-2)+x)==' '&&*(*(maze_image+y-1)+x)==' ') return 1;
                else return 0;
            default:
                return 0;
            }
        }
    }

    if(((x+2==player_position->x)&&(y+1==player_position->y)&&*(*(maze_image+player_position->y)+player_position->x-1)==' '&&*(*(maze_image+player_position->y-1)+player_position->x-1)==' ')
    ||((x+2==player_position->x)&&(y-1==player_position->y)&&*(*(maze_image+player_position->y)+player_position->x-1)==' '&&*(*(maze_image+player_position->y+1)+player_position->x-1)==' ')
    ||((x-2==player_position->x)&&(y+1==player_position->y)&&*(*(maze_image+player_position->y)+player_position->x+1)==' '&&*(*(maze_image+player_position->y-1)+player_position->x+1)==' ')
    ||((x-2==player_position->x)&&(y-1==player_position->y)&&*(*(maze_image+player_position->y)+player_position->x+1)==' '&&*(*(maze_image+player_position->y+1)+player_position->x+1)==' ')) return 1;
    
    if(((x+1==player_position->x)&&(y+2==player_position->y)&&*(*(maze_image+player_position->y-1)+player_position->x-1)==' '&&*(*(maze_image+player_position->y-1)+player_position->x)==' ')
    ||((x-1==player_position->x)&&(y+2==player_position->y)&&*(*(maze_image+player_position->y-1)+player_position->x+1)==' '&&*(*(maze_image+player_position->y-1)+player_position->x)==' ')
    ||((x+1==player_position->x)&&(y-2==player_position->y)&&*(*(maze_image+player_position->y+1)+player_position->x-1)==' '&&*(*(maze_image+player_position->y+1)+player_position->x)==' ')
    ||((x-1==player_position->x)&&(y-2==player_position->y)&&*(*(maze_image+player_position->y+1)+player_position->x+1)==' '&&*(*(maze_image+player_position->y+1)+player_position->x)==' ')) return 1;

    if((((x+2==player_position->x)&&(y+2==player_position->y))&&is_visible(maze_image,player_position,x+1,y+1))
    ||(((x+2==player_position->x)&&(y-2==player_position->y))&&is_visible(maze_image,player_position,x+1,y-1))
    ||(((x-2==player_position->x)&&(y+2==player_position->y))&&is_visible(maze_image,player_position,x-1,y+1))
    ||(((x-2==player_position->x)&&(y-2==player_position->y))&&is_visible(maze_image,player_position,x-1,y-1))) {
        //felt weird
        // printf("x= %d y= %d\n",x,y);
        return 1;}
    
    if((((x+3==player_position->x)&&(y+2==player_position->y))&&is_visible(maze_image,player_position,x+2,y+1))||
    (((x+3==player_position->x)&&(y-2==player_position->y))&&is_visible(maze_image,player_position,x+2,y-1))||
    (((x-3==player_position->x)&&(y+2==player_position->y))&&is_visible(maze_image,player_position,x-2,y+1))||
    (((x-3==player_position->x)&&(y-2==player_position->y))&&is_visible(maze_image,player_position,x-2,y-1)))  {
        //felt weird v2 bug somewhere there
        printf("x= %d y= %d\n",x,y);
        return 1;}
    
    return 0;
}
void print_maze_mode_4(char **maze_image, struct point *player_position, char** small_buffer){
    if(maze_image==NULL || player_position==NULL) return;
    int cols=get_columns(maze_image);
    int rows=get_rows(maze_image);
    mode_2_to_array(maze_image,player_position,small_buffer);
    for (size_t i = 0; i < 5; i++)
    {
        for (size_t j = 0; j < 7; j++)
        {
            switch (*(*(small_buffer+i)+j))
            {
            case '#':
                printf("#");
                break;
            case ' ':
                printf(".");
                break;
            case '@':
                printf("(");
                break;
            case 'X':
                printf("\\");
                break;
            
            default:
                break;
            }
            switch (*(*(small_buffer+i)+j))
            {
            case '#':
                printf("#");
                break;
            case ' ':
                printf(",");
                break;
            case '@':
                printf(")");
                break;
            case 'X':
                printf("/");
                break;
            
            default:
                break;
            }
        }
        printf("\n");
        for (size_t j = 0; j < 7; j++)
        {
            switch (*(*(small_buffer+i)+j))
            {
            case '#':
                printf("#");
                break;
            case ' ':
                printf(",");
                break;
            case '@':
                printf("/");
                break;
            case 'X':
                printf("/");
                break;
            
            default:
                break;
            }
            switch (*(*(small_buffer+i)+j))
            {
            case '#':
                printf("#");
                break;
            case ' ':
                printf(".");
                break;
            case '@':
                printf("\\");
                break;
            case 'X':
                printf("\\");
                break;
            
            default:
                break;
            }
        }
        printf("\n");
        
    }
    
}
 void mode_2_to_array(char **maze_image, struct point *player_position, char** small_buffer){
    if(maze_image==NULL || player_position==NULL || small_buffer==NULL) return;
    int cols=get_columns(maze_image);
    int rows=get_rows(maze_image);
    if((player_position->x<0) || (player_position->x>=cols) || (player_position->y<0) || (player_position->y>=rows)){
        return;
    }
    int start_cols,start_rows,end_cols,end_rows;
    if(player_position->y<=1) start_rows=0;
    else start_rows=player_position->y-2;
    if(player_position->x<=2) start_cols=0;
    else start_cols=player_position->x-3;
    if((rows-player_position->y-1)<=2) end_rows=rows;
    else end_rows=player_position->y+3;
    if((cols-player_position->x-1)<=3) end_cols=cols;
    else end_cols=player_position->x+4;
    int array_index_y=0;
    int array_index_x=0;
    if(player_position->y<=1) for (size_t i = 0; i < 2-player_position->y; i++) {
        for (size_t j = 0; j < 7; j++) {
            *(*(small_buffer+array_index_y)+array_index_x)='#';
            array_index_x++;
        }
        array_index_y++;
        array_index_x=0;
    }
    for (size_t i = start_rows; i < end_rows; i++)
    {
        if(player_position->x<=2) for (size_t j = 0; j < 3-player_position->x; j++) {
            *(*(small_buffer+array_index_y)+array_index_x)='#';
            array_index_x++;
        }
        
        for (size_t j = start_cols; j < end_cols; j++)
        {
            if(*(*(maze_image+i)+j)=='@') {
            *(*(small_buffer+array_index_y)+array_index_x)='@';
            array_index_x++;
            }
            else if(*(*(maze_image+i)+j)=='X') {
            *(*(small_buffer+array_index_y)+array_index_x)='X';
            array_index_x++;
            }
            else if(*(*(maze_image+i)+j)==' '&&is_visible(maze_image,player_position,j,i)) {
            *(*(small_buffer+array_index_y)+array_index_x)=' ';
            array_index_x++;
            }
            else {
            *(*(small_buffer+array_index_y)+array_index_x)='#';
            array_index_x++;
            }
        }

        if((cols-player_position->x-1)<=3) for (size_t j = 0; j < 3-(cols-player_position->x-1); j++) printf("#");

        array_index_y++;
        array_index_x=0;
    }

    if((rows-player_position->y-1)<=2) for (size_t i = 0; i < 2-(rows-player_position->y-1); i++) {
        for (size_t j = 0; j < 7; j++) {
            *(*(small_buffer+array_index_y)+array_index_x)='#';
            array_index_x++;
        }
        array_index_y++;
        array_index_x=0;
    }
}
char **buffer_for_mode_4(){
    char **temp=calloc(5,sizeof(char*));
    if(temp==NULL) return NULL;
    for (size_t i = 0; i < 7; i++)
    {
        *(temp+i)=calloc(7,sizeof(char));
        if(*(temp+i)==NULL) return NULL;
    }
    return temp;
}
void destroy_mode_4_array(char **buffer){
    if(buffer==NULL) return;
    for (size_t i = 0; i < 5; i++)
    {
        if(*(buffer+i)!=NULL) free(*(buffer+i));
    }
    free(buffer);
}