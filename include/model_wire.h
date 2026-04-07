#ifndef MODEL_WIRE
#define MODEL_WIRE

#include <vector>
#include <cmath>

#include <raylib.h>

#define SCREEN_WIDTH    800
#define SCREEN_HEIGHT   800
#define WIRE_COLOR      YELLOW

static float camera_z = 2.0;
static float angle = 0.0;

static std::vector<Vector3> vertexs;
static std::vector<std::vector<int>> faces;

void ModelRun();
Vector2 ToScreen(Vector2);
Vector2 Project(Vector3);
Vector3 Rotate_XZ(Vector3, float);

#endif //MODEL_WIRE