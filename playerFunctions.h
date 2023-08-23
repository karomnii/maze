#ifndef PLAYER_FUNCTIONS_H
#define PLAYER_FUNCTIONS_H

#include <stdio.h>
#include <stdlib.h>
#include "dataTypes.h"

void add_player(char **maze_image, struct point enterance_point, struct point *player_position);
int get_rows(char **maze_image);
int get_columns(char **maze_image);
int board_is_empty(char **maze_image);
void add_exit(char **maze_image, struct point exit_point);
void add_treasure(char **maze_image, struct point treasure_point);
int move_player(char **maze_image, struct point *player_position, enum direction player_move);
void player_won(int score);
void end_game();


#endif // PLAYER_FUNCTIONS_H