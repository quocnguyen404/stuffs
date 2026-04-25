#include "ss.h"


void InitSS() {
    arr.clear();
    isDone = false;
    isStart = false;
    index_1 = 0;
    index_2 = 0;
    min_index = 0;

    for(int i = 0; i < COL_NUM; i++) {
        int e = GetRange(MIN_HEIGHT, MAX_HEIGHT);
        arr.push_back(e);
    }
}

void RunSS() {
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Sort");
    SetTargetFPS(60);
    InitSS();

    static float counter = 0.0;

    std::string entities_str = std::to_string(COL_NUM);

    while(!WindowShouldClose()) {

        counter += GetFrameTime();
        
        if(IsKeyDown(KEY_R)) {
            InitSS();
        }

        if(IsKeyDown(KEY_S)) {
            isStart = true;
        }

        if(isStart && counter >= CALLTIME) {
            UpdateSS();
            counter = 0.0f;
        }

        BeginDrawing();
        ClearBackground(BG_COLOR);

        DrawSS();
        
        DrawFPS(10, 10);
        DrawTextCenter(entities_str, {SCREEN_WIDTH * 0.5, 30}, 30, RAYWHITE);

        EndDrawing();
    }

    CloseWindow();
}

void UpdateSS() {
    if(isDone)
        return;

    for(int step = 0; step < STEP_PER_FRAME; step++) {

        if(index_1 >= COL_NUM - 1) {
            isDone = true;
            return;
        }

        if(index_2 == 0) {
            min_index = index_1;
            index_2 = index_1 + 1;
        }

        if(index_2 < COL_NUM) {
            if(arr[index_2] < arr[min_index]) {
                min_index = index_2;
            }
            index_2++;
        }
        else {
            if(min_index != index_1) {
                int t = arr[index_1];
                arr[index_1] = arr[min_index];
                arr[min_index] = t;
            }

            index_1++;
            index_2 = 0;
        }
    }
}

void DrawSS() {
    for(int i = 0; i < COL_NUM; i++) {
        int e = arr[i];

        Color col_color = COL_NOT_DONE_COLOR;

        if(isStart && (i == index_1 || i == index_2)) {
            col_color = BLUE;
        }

        if(isDone) {
            col_color = COL_DONE_COLOR;
        }
        

        //Draw column
        DrawRectangle(i * COL_WIDTH, SCREEN_HEIGHT - e, COL_WIDTH,
                      e, col_color);
        
        //Top line
        DrawLine(i * COL_WIDTH, SCREEN_HEIGHT - e,
                (i + 1) * COL_WIDTH, SCREEN_HEIGHT - e + 1, COL_OUTLINE_COLOR);

        //Left line
        // DrawLine(i * COL_WIDTH, SCREEN_HEIGHT - e,
        //          i * COL_WIDTH + 1, SCREEN_HEIGHT, COL_OUTLINE_COLOR);

        //Right line
        DrawLine((i + 1) * COL_WIDTH, SCREEN_HEIGHT - e,
                 (i + 1) * COL_WIDTH - 1, SCREEN_HEIGHT, GRAY);
    
    }
}