#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>
#include <math.h>

#include "dataTypes.h"
#include "mazeGeneration.h"


void generate_maze(struct cell maze[10][10], struct cell *current_cell) {
    current_cell->visited = true;
    while (true)
    {
        int direction = rand() % 4;
        if(direction == 0 && current_cell->up != NULL && current_cell->up->visited == false) {
            current_cell->up_wall = false;
            current_cell->up->down_wall = false;
            generate_maze(maze, current_cell->up);
        }
        else if(direction == 1 && current_cell->down != NULL && current_cell->down->visited == false) {
            current_cell->down_wall = false;
            current_cell->down->up_wall = false;
            generate_maze(maze, current_cell->down);
        }
        else if(direction == 2 && current_cell->left != NULL && current_cell->left->visited == false) {
            current_cell->left_wall = false;
            current_cell->left->right_wall = false;
            generate_maze(maze, current_cell->left);
        }
        else if(direction == 3 && current_cell->right != NULL && current_cell->right->visited == false) {
            current_cell->right_wall = false;
            current_cell->right->left_wall = false;
            generate_maze(maze, current_cell->right);
        } if(current_cell->up != NULL && current_cell->up->visited == false) {
            current_cell->up_wall = false;
            current_cell->up->down_wall = false;
            generate_maze(maze, current_cell->up);
        }
        else if(current_cell->down != NULL && current_cell->down->visited == false) {
            current_cell->down_wall = false;
            current_cell->down->up_wall = false;
            generate_maze(maze, current_cell->down);
        }
        else if(current_cell->left != NULL && current_cell->left->visited == false) {
            current_cell->left_wall = false;
            current_cell->left->right_wall = false;
            generate_maze(maze, current_cell->left);
        }
        else if(current_cell->right != NULL && current_cell->right->visited == false) {
            current_cell->right_wall = false;
            current_cell->right->left_wall = false;
            generate_maze(maze, current_cell->right);
        }
        else {
            break;
        }
    }
}