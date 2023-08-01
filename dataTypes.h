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


#endif //MAZE_DATATYPES_H