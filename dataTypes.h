#ifndef MAZE_DATATYPES_H
#define MAZE_DATATYPES_H

#include <stdbool.h>

struct cell {
    unsigned x;
    unsigned y;
    bool visited;
    struct cell *up;
    struct cell *down;
    struct cell *left;
    struct cell *right;
    bool up_wall;
    bool down_wall;
    bool left_wall;
    bool right_wall;
};

enum direction{
    UP,
    DOWN,
    LEFT,
    RIGHT
};

struct point{
    unsigned int x;
    unsigned int y;
};

struct player{
    struct point position;
    struct point previous_position;
};
// struct board_information{
//     bool is_player;
//     point player_position;
//     position_section block_part;
// }

#endif //MAZE_DATATYPES_H