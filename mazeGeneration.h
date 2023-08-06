#ifndef MAZE_MAZEGENERATION_H
#define MAZE_MAZEGENERATION_H

#include "dataTypes.h"

void generate_maze(struct cell *current_cell);
int initialize_maze(struct cell ***maze, unsigned rows, unsigned cols);
void destroy_maze(struct cell **maze);
void set_values_maze(struct cell **maze, unsigned rows, unsigned cols);
void print_maze(struct cell **maze);

#endif //MAZE_MAZEGENERATION_H