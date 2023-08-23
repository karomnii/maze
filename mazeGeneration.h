#ifndef MAZE_MAZEGENERATION_H
#define MAZE_MAZEGENERATION_H

#include "dataTypes.h"

void generate_maze(struct cell *current_cell);
int initialize_maze(struct cell ***maze, unsigned rows, unsigned cols);
void destroy_maze(struct cell **maze);
void set_values_maze(struct cell **maze, unsigned rows, unsigned cols);
void print_maze(struct cell **maze);
int maze_to_memory(struct cell **maze,char ***maze_image);
void destroy_maze_image(char **maze_image);
void print_maze_image(char **maze_image);
void print_maze_mode_2(char **maze_image,struct point *player_position);
int is_visible(char **maze_image,struct point *player_position,int x, int y);

#endif //MAZE_MAZEGENERATION_H