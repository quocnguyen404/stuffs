#include "salt.h"

static std::random_device rd;
static std::mt19937 gen(rd());
static std::uniform_real_distribution<> distr(0.0, 1.0);

float GetRandom() {
    return distr(gen);
}

int GetRange(int a, int b) {
    std::uniform_int_distribution<> d(a, b);
    return d(gen);
}

float GetRangeF(float a, float b) {
    std::uniform_real_distribution<> d(a, b);
    return d(gen);
}

void DrawTextCenter(std::string text, Vector2 pos, int fontSize, Color color) {
    int textWidth = MeasureText(text.c_str(), fontSize);
    DrawText(text.c_str(), pos.x - textWidth*.5, pos.y - fontSize*.5, fontSize, color);
}