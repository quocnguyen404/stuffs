#ifndef BALL_BOUNCE_H
#define BALL_BOUNCE_H

#include <vector>

#include <raylib.h>
#include "salt.h"

#define SCREEN_WIDTH    800
#define SCREEN_HEIGHT   450
#define CALL_TIME       0.01
#define SPEED_RANGE     200
#define COLORS_SIZE     4
#define BG_COLOR        BLACK

struct Sphere {
    Vector2 pos;
    int radius;
    Color color;
    Vector2 vel;
};

static std::vector<Sphere> balls;

static Color colors[COLORS_SIZE] = {WHITE, BLUE, YELLOW, RED};

void BBRun();
Color GetRandomColor();

#endif //BALL_BOUNCE_H