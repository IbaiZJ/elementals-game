#ifndef ENTITIES_H
#define ENTITIES_H

typedef struct s_position {
    float x;
    float y;
} POSITION;

typedef enum {
    IDLE,
    MOVING,
    HIT,
    DEAD
} STATE;

typedef struct s_formula {
    double hill;
    double sin;
    double cos;
} FORMULA;



#endif