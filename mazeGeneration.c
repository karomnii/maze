#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>
#include <math.h>

#include "dataTypes.h"
#include "mazeGeneration.h"


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
            printf("+");
            if((*(*(maze+i)+j)).up_wall == true)
                printf("---");
            else
                printf("   ");
            j++;
        }
        printf("+");
            if((*(*(maze+i)+j)).up_wall == true)
                printf("---");
            else
                printf("   ");
        printf("+\n");
        j = 0;
        while((*(*(maze+i)+j)).right != NULL) {
            if((*(*(maze+i)+j)).left_wall == true)
                printf("|");
            else
                printf(" ");
            if((*(*(maze+i)+j)).visited == true)
                printf(" * ");
            else
                printf("   ");
            j++;
        }
        if((*(*(maze+i)+j)).left_wall == true)
                printf("|");
            else
                printf(" ");
            if((*(*(maze+i)+j)).visited == true)
                printf(" * ");
            else
                printf("   ");
        if((*(*(maze+i)+j)).right_wall == true)
            printf("|");
        else
            printf(" ");
        printf("\n");
        i++;
    }
    for (size_t j = 0; (*(*(maze+0)+j)).right != NULL; j++)
        {
            printf("+");
            printf("---");
        }
    printf("+");
            printf("---");
    printf("+\n");
}
int maze_to_memory(struct cell **maze,char ***maze_image){
    if(maze==NULL||maze_image==NULL) return 1;
    unsigned int rows=0, cols=0;
    while (*(maze+rows)!=NULL) rows++;
    if(rows<3) return 1;
    while ((*maze+cols)->right!=NULL) cols++; cols++;
    if(cols<3) return 1;
    *maze_image=calloc(3*rows+1,sizeof(char *));
    if(*maze_image==NULL) return 4;
    for (unsigned int i = 0; i < rows*3; i++)
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
            // testing, later change to proper maze image
            sprintf(*(*maze_image+i*3),"%s%c",*(*maze_image+i*3),'#');
            sprintf(*(*maze_image+i*3),"%s%d",*(*maze_image+i*3),i);
            sprintf(*(*maze_image+i*3),"%s%d",*(*maze_image+i*3),j);
            sprintf(*(*maze_image+i*3),"%s%c",*(*maze_image+i*3),'#');
            sprintf(*(*maze_image+i*3+1),"%s%c",*(*maze_image+i*3+1),'#');
            sprintf(*(*maze_image+i*3+1),"%s%d",*(*maze_image+i*3+1),i);
            sprintf(*(*maze_image+i*3+1),"%s%d",*(*maze_image+i*3+1),j);
            sprintf(*(*maze_image+i*3+1),"%s%c",*(*maze_image+i*3+1),'#');
            sprintf(*(*maze_image+i*3+2),"%s%c",*(*maze_image+i*3+2),'#');
            sprintf(*(*maze_image+i*3+2),"%s%d",*(*maze_image+i*3+2),i);
            sprintf(*(*maze_image+i*3+2),"%s%d",*(*maze_image+i*3+2),j);
            sprintf(*(*maze_image+i*3+2),"%s%c",*(*maze_image+i*3+2),'#');
        }
        
    }
    
}
void destroy_maze_image(char **maze_image){
    if(maze_image==NULL) return;
    for (size_t i = 0; *(maze_image+i)!=NULL; i++) free(*(maze_image+i));
    free(maze_image);
}
void print_maze_image(char **maze_image){
    if(maze_image==NULL) return;
    for (size_t i = 0; *(maze_image+i)!=NULL; i++)
    {
        printf("%s\n",*(maze_image+i));
    }
}