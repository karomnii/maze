#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>
#include <math.h>

#include "dataTypes.h"
#include "mazeGeneration.h"
#include "playerFunctions.h"


void generate_maze(struct cell *current_cell) {
    current_cell->visited = true;
    while (true)
    {
        int direction = rand() % 4;
        if(direction == 0 && current_cell->up != NULL && current_cell->up->visited == false) {
            current_cell->up_wall = false;
            current_cell->up->down_wall = false;
            generate_maze(current_cell->up);
        }
        else if(direction == 1 && current_cell->down != NULL && current_cell->down->visited == false) {
            current_cell->down_wall = false;
            current_cell->down->up_wall = false;
            generate_maze(current_cell->down);
        }
        else if(direction == 2 && current_cell->left != NULL && current_cell->left->visited == false) {
            current_cell->left_wall = false;
            current_cell->left->right_wall = false;
            generate_maze(current_cell->left);
        }
        else if(direction == 3 && current_cell->right != NULL && current_cell->right->visited == false) {
            current_cell->right_wall = false;
            current_cell->right->left_wall = false;
            generate_maze(current_cell->right);
        }
        else if(current_cell->up != NULL && current_cell->up->visited == false) {
            current_cell->up_wall = false;
            current_cell->up->down_wall = false;
            generate_maze(current_cell->up);
        }
        else if(current_cell->down != NULL && current_cell->down->visited == false) {
            current_cell->down_wall = false;
            current_cell->down->up_wall = false;
            generate_maze(current_cell->down);
        }
        else if(current_cell->left != NULL && current_cell->left->visited == false) {
            current_cell->left_wall = false;
            current_cell->left->right_wall = false;
            generate_maze(current_cell->left);
        }
        else if(current_cell->right != NULL && current_cell->right->visited == false) {
            current_cell->right_wall = false;
            current_cell->right->left_wall = false;
            generate_maze(current_cell->right);
        }
        else {
            break;
        }
    }
}
int initialize_maze(struct cell ***maze, unsigned rows, unsigned cols){
    if(maze == NULL || rows < 3 || cols < 3) {
        return 1;
    }
    *maze = calloc(rows+1,sizeof(struct cell *));
    if(*maze == NULL) {
        return 4;
    }
    for (size_t i = 0; i < rows; i++)
    {
        *(*maze+i) = calloc(cols,sizeof(struct cell));
        if(*(*maze+i) == NULL) {
            destroy_maze(*maze);
            return 4;
        }
    }
    set_values_maze(*maze,rows,cols);
    return 0;
}
void destroy_maze(struct cell **maze){
    if(maze == NULL) {
        return;
    }
    int i = 0;
    while (*(maze+i) != NULL)
    {
        free(*(maze+i));
        i++;
    }
    free(maze);
}
void set_values_maze(struct cell **maze, unsigned rows, unsigned cols){
    if(maze == NULL || rows < 3 || cols < 3) {
        return;
    }
    for (size_t i = 0; i < rows; i++)
    {
        for (size_t j = 0; j < cols; j++) {
            (*(*(maze+i)+j)).x = i;
            (*(*(maze+i)+j)).y = j;
            (*(*(maze+i)+j)).visited = false;
            if(i == 0)
                (*(*(maze+i)+j)).up = NULL;
            else
                (*(*(maze+i)+j)).up = (*(maze+i-1)+j);
            if(i == rows-1)
                (*(*(maze+i)+j)).down = NULL;
            else
                (*(*(maze+i)+j)).down = (*(maze+i+1)+j); 
            if(j == 0)
                (*(*(maze+i)+j)).left = NULL;
            else
                (*(*(maze+i)+j)).left = (*(maze+i)+j-1);
            if(j == cols-1)
                (*(*(maze+i)+j)).right = NULL;
            else
                (*(*(maze+i)+j)).right = (*(maze+i)+j+1);
            (*(*(maze+i)+j)).up_wall = true;
            (*(*(maze+i)+j)).down_wall = true;
            (*(*(maze+i)+j)).left_wall = true;
            (*(*(maze+i)+j)).right_wall = true;
        }
    }
}
void print_maze(struct cell **maze){
    if(maze == NULL) {
        return;
    }
    int i = 0;
    while(*(maze+i) != NULL) {
        int j = 0;
        while((*(*(maze+i)+j)).right != NULL) {
            if((*(*(maze+i)+j)).up_wall == true)
                printf("+---");
            else
                printf("+   ");
            j++;
        }
        if((*(*(maze+i)+j)).up_wall == true)
            printf("+---");
        else
            printf("+   ");
        printf("+\n");
        j = 0;
        while((*(*(maze+i)+j)).right != NULL) {
            if((*(*(maze+i)+j)).left_wall == true)
                printf("| * ");
            else
                printf("  * ");
            j++;
        }
        if((*(*(maze+i)+j)).left_wall == true)
            printf("| * ");
        else
            printf("  * ");
        printf("|\n");
        i++;
    }
    for (size_t j = 0; (*(*(maze+0)+j)).right != NULL; j++)
        {
            printf("+---");
        }
    printf("+---+\n");
}
int maze_to_memory(struct cell **maze,char ***maze_image){
    if(maze==NULL||maze_image==NULL) return 1;
    unsigned int rows=0, cols=0;
    while (*(maze+rows)!=NULL) rows++;
    if(rows<3) return 1;
    while ((*maze+cols)->right!=NULL) cols++; cols++;
    if(cols<3) return 1;
    *maze_image=calloc(2*rows+2,sizeof(char *));
    if(*maze_image==NULL) return 4;
    for (unsigned int i = 0; i < rows*2+1; i++)
    {
        *(*maze_image+i)=calloc(4*cols+1+1,sizeof(char));
        if(*(*maze_image+i)==NULL){
            destroy_maze_image(*maze_image);
            return 4;
        }
    }
    for (size_t i = 0; i < rows; i++)
    {
        for (size_t j = 0; j < cols; j++)
        {
            if((*(*(maze+i)+j)).up_wall==true) sprintf(*(*maze_image+i*2),"%s%s",*(*maze_image+i*2),"+---");
            else sprintf(*(*maze_image+i*2),"%s%s",*(*maze_image+i*2),"+   ");
            if((*(*(maze+i)+j)).left_wall==true) sprintf(*(*maze_image+i*2+1),"%s%s",*(*maze_image+i*2+1),"|   ");
            else sprintf(*(*maze_image+i*2+1),"%s%s",*(*maze_image+i*2+1),"    ");
        }
        sprintf(*(*maze_image+i*2),"%s%c",*(*maze_image+i*2),'+');
        sprintf(*(*maze_image+i*2+1),"%s%c",*(*maze_image+i*2+1),'|');
    }
    for (size_t j = 0; j < cols; j++)
        {
            sprintf(*(*maze_image+rows*2),"%s%s",*(*maze_image+rows*2),"+---");
        }
    sprintf(*(*maze_image+rows*2),"%s%c",*(*maze_image+rows*2),'+');
    return 0;
}
void destroy_maze_image(char **maze_image){
    if(maze_image==NULL) return;
    for (size_t i = 0; *(maze_image+i)!=NULL; i++) free(*(maze_image+i));
    free(maze_image);
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
int is_visible(char **maze_image,struct point *player_position,int x, int y){
    if(maze_image==NULL||player_position==NULL||x<0||y<0) return 0;

    if(((x+1==player_position->x)&&(y+1==player_position->y))
    ||((x-1==player_position->x)&&(y+1==player_position->y))
    ||((x+1==player_position->x)&&(y-1==player_position->y))
    ||((x-1==player_position->x)&&(y-1==player_position->y))) return 1; //player corners
    
    if(((x+2==player_position->x)&&(y+1==player_position->y)&&*(*(maze_image+player_position->y)+player_position->x-1)==' '&&*(*(maze_image+player_position->y-1)+player_position->x-1)==' ')
    ||((x+2==player_position->x)&&(y-1==player_position->y)&&*(*(maze_image+player_position->y)+player_position->x-1)==' '&&*(*(maze_image+player_position->y+1)+player_position->x-1)==' ')
    ||((x-2==player_position->x)&&(y+1==player_position->y)&&*(*(maze_image+player_position->y)+player_position->x+1)==' '&&*(*(maze_image+player_position->y-1)+player_position->x+1)==' ')
    ||((x-2==player_position->x)&&(y-1==player_position->y)&&*(*(maze_image+player_position->y)+player_position->x+1)==' '&&*(*(maze_image+player_position->y+1)+player_position->x+1)==' ')) return 1;
    
    if(((x+1==player_position->x)&&(y+2==player_position->y)&&*(*(maze_image+player_position->y-1)+player_position->x-1)==' '&&*(*(maze_image+player_position->y-1)+player_position->x)==' ')
    ||((x-1==player_position->x)&&(y+2==player_position->y)&&*(*(maze_image+player_position->y-1)+player_position->x+1)==' '&&*(*(maze_image+player_position->y-1)+player_position->x)==' ')
    ||((x+1==player_position->x)&&(y-2==player_position->y)&&*(*(maze_image+player_position->y+1)+player_position->x-1)==' '&&*(*(maze_image+player_position->y+1)+player_position->x)==' ')
    ||((x-1==player_position->x)&&(y-2==player_position->y)&&*(*(maze_image+player_position->y+1)+player_position->x+1)==' '&&*(*(maze_image+player_position->y+1)+player_position->x)==' ')) return 1;

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
    return 0;
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
