#include "ball_bounce.h"

void BBRun() {
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Ball Bounce");

    static float counter;

    while(!WindowShouldClose()) {
        float dt = GetFrameTime();
        counter += dt;

        BeginDrawing();
        ClearBackground(BG_COLOR);

        if(counter >= CALL_TIME) {
            if(IsMouseButtonDown(0)) {
                Vector2 mpos = GetMousePosition();
                Sphere s = {
                    .pos = {mpos.x, mpos.y},
                    .radius = GetRange(10, 20),
                    .color = GetRandomColor(),
                    .vel = {GetRangeF(-SPEED_RANGE, SPEED_RANGE), GetRangeF(-SPEED_RANGE, SPEED_RANGE)}
                };
                balls.push_back(s);
            }

            if(IsMouseButtonDown(1)) {
                if(!balls.empty()) {
                    balls.pop_back();
                }
            }
            counter = 0;
        }

        for(auto& ball : balls) {
            ball.pos.x += ball.vel.x * dt;
            ball.pos.y += ball.vel.y * dt;

            if(ball.pos.x + ball.radius >= SCREEN_WIDTH) {
                ball.pos.x = SCREEN_WIDTH - ball.radius;
                ball.vel.x *= -1;
            } else if(ball.pos.x - ball.radius <= 0) {
                ball.pos.x = ball.radius;
                ball.vel.x *= -1;
            }

            if(ball.pos.y + ball.radius >= SCREEN_HEIGHT) {
                ball.pos.y = SCREEN_HEIGHT - ball.radius;
                ball.vel.y *= -1;
            } else if (ball.pos.y - ball.radius <= 0) {
                ball.pos.y = ball.radius;
                ball.vel.y *= -1;
            }

            DrawCircle(ball.pos.x, ball.pos.y, ball.radius, ball.color);

        }
        
        DrawFPS(10, 10);
        DrawTextCenter(std::to_string(balls.size()).c_str(), {SCREEN_WIDTH*.5, 20}, 30, WHITE);
        EndDrawing();
    }
    CloseWindow();
}

Color GetRandomColor() {
    int ran = GetRange(0, sizeof(colors)/sizeof(Color));
    return colors[ran];
}