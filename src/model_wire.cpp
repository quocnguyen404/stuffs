#include "model_wire.h"

#include "penger.h"

void ModelRun() {
    vertexs = penger_vertexs;
    faces = penger_faces;

    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Penger");

    while(!WindowShouldClose()) {
        angle += PI * GetFrameTime();
        
        BeginDrawing();
        ClearBackground(BLACK);

        for(auto& f : faces) {
            for(int i = 0; i < f.size(); i++) {
                Vector3 v1 = vertexs[f[i]];
                Vector3 v2 = vertexs[f[(i+1)%f.size()]];

                Vector3 rot1 = Rotate_XZ(v1, angle);
                Vector3 rot2 = Rotate_XZ(v2, angle);
                rot1.z += camera_z;
                rot2.z += camera_z;

                Vector2 screen1 = ToScreen(Project(rot1));
                Vector2 screen2 = ToScreen(Project(rot2));

                DrawLine(screen1.x, screen1.y, screen2.x, screen2.y, WIRE_COLOR);
            }
        }

        EndDrawing();
    }

    CloseWindow();
}

Vector2 ToScreen(Vector2 pos) {
    return {
        (pos.x + 1) * 0.5 * SCREEN_WIDTH,
        (1 - (pos.y + 1) * 0.5) * SCREEN_HEIGHT
    };
}

Vector2 Project(Vector3 pos) {
    return {
        pos.x / pos.z,
        pos.y / pos.z
    };
}

Vector3 Rotate_XZ(Vector3 pos, float angle) {
    const float c = cosf(angle);
    const float s = sinf(angle);
    return {
        pos.x * c - pos.z * s,
        pos.y,
        pos.x * s + pos.z * c
    };
}