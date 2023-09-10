#ifndef MAZEPRINTING_H
#define MAZEPRINTING_H

#include <stdio.h>
#include "dataTypes.h"

void print_maze(char **maze_image,struct player *player_position,int mode);
void print_maze_mode_1(char **maze_image);
void print_maze_mode_2(char **maze_image,struct point *player_position);
void print_maze_mode_3(char **maze_image, struct point *player_position);
void print_maze_mode_4(char **maze_image, struct point *player_position, char** small_buffer);
void mode_2_to_array(char **maze_image, struct point *player_position,char **small_buffer);
int is_visible(char **maze_image,struct point *player_position,int x, int y);
char **buffer_for_mode_4();
void destroy_mode_4_array(char **buffer);



#endif // MAZEPRINTING_H