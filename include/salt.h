#ifndef SALT_H
#define SALT_H

#include <random>
#include <string>
#include <raylib.h>

float GetRandom();
int GetRange(int, int);
float GetRangeF(float, float);
void DrawTextCenter(std::string, Vector2, int, Color);

#endif //SALT_H