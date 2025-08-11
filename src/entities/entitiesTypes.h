#ifndef ENTITIES_H
#define ENTITIES_H

typedef struct s_position {
    float x;
    float y;
} POSITION;

typedef enum {
    HORIZONTAL_RIGHT,
    HORIZONTAL_LEFT
} HORIZONTAL_POSITION;

typedef struct s_formula {
    double hill;
    double sin;
    double cos;
} FORMULA;

typedef struct s_time {
    double start;
    double finish;
} TIME;

#endif