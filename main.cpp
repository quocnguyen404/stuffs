#include <string>
#include <vector>
#include <cmath>

#include <raylib.h>

static int width = 800;
static int height = 450;

static int radius = 5;
static float angle = 0.0;

struct Node {
    Vector3 pos;
    Vector3 nPos;
};

static std::vector<Node> nodes;
static std::vector<std::vector<int>> faces;

void UpdateNode(Node &);
void DrawNode(const Node &);
Vector2 ToScreen(Vector2);
Vector2 Project(Vector3);
Vector3 Rotate_XZ(const Vector3, float);

int main() {
    InitWindow(width, height, "3D formula");
    // SetTargetFPS(60);

    nodes = {
        {{-0.5,  0.5,  0.5}},   //0
        {{-0.5,  0.5, -0.5}},   //1

        {{ 0.5,  0.5,  0.5}},   //2
        {{ 0.5,  0.5, -0.5}},   //3

        {{-0.5, -0.5,  0.5}},   //4
        {{-0.5, -0.5, -0.5}},   //5

        {{ 0.5, -0.5,  0.5}},   //6
        {{ 0.5, -0.5, -0.5}}    //7
    };

    // faces = {
    //     {0, 1, 2, 3},
    //     {4, 5, 6, 7},
    //     {0, 4},
    //     {1, 5},
    //     {2, 6},
    //     {3, 7}
    // };

    while(!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(BLACK);

        angle += PI * GetFrameTime();

        for(Node& n : nodes) {
            UpdateNode(n);
            DrawNode(n);
        }

        // for(auto& f : faces) {
        //     for(int i = 0; i < f.size(); i++) {

        //     }
        // }

        DrawFPS(10, 10);

        EndDrawing();
    }

    CloseWindow();
}

void UpdateNode(Node &node) {
    Vector3 rotPos = Rotate_XZ(node.pos, angle);
    rotPos.z += 3;
    node.nPos = rotPos;
}

void DrawNode(const Node &node) {
    Vector2 projectPos = Project(node.nPos);
    Vector2 screenPos = ToScreen(projectPos);
    DrawCircleV(screenPos, radius, WHITE);
}

// void DrawWire(Vector3 p1, Vector3 p2) {
//     DrawLine(p1.x, p1.y, p2.x, p2.y, WHITE);
// }

Vector2 ToScreen(const Vector2 pos) {
    return {
        (pos.x + 1) * .5 * width,
        (1 - (pos.y + 1) * .5) * height
    };
}

Vector2 Project(const Vector3 pos) {
    return {
        pos.x / pos.z,
        pos.y / pos.z
    };
}

Vector3 Rotate_XZ(const Vector3 pos, float theta) {
    const float c = cosf(theta);
    const float s = sinf(theta);
    return {
        pos.x * c - pos.z * s,
        pos.y,
        pos.x * s + pos.z * c,
    };
}