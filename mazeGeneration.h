#ifndef MAZE_MAZEGENERATION_H
#define MAZE_MAZEGENERATION_H

#include "dataTypes.h"

void generate_maze(struct cell *current_cell);
int initialize_maze(struct cell ***maze, unsigned rows, unsigned cols);
void destroy_maze(struct cell **maze);
void set_values_maze(struct cell **maze, unsigned rows, unsigned cols);
void print_maze_from_cells(struct cell **maze);
int maze_to_memory(struct cell **maze,char ***maze_image);
void destroy_maze_image(char **maze_image);


#endif //MAZE_MAZEGENERATION_H