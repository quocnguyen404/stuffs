#include "ss.h"


void InitSS() {
    arr.clear();
    isDone = false;
    index_1 = 0;
    index_2 = 0;

    for(int i = 0; i < COL_NUM; i++) {
        int e = GetRange(MIN_HEIGHT, MAX_HEIGHT);
        arr.push_back(e);
    }
}

void RunSS() {
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Sort");

    InitSS();

    while(!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(BG_COLOR);

        if(IsKeyDown(KEY_R)) {
            InitSS();
        }

        UpdateSS();
        DrawSS();
        
        DrawFPS(10, 10);

        EndDrawing();
    }

    CloseWindow();
}

void UpdateSS() {
    if(isDone)
        return;

    for(int step = 0; step < STEP_PER_FRAME; step++) {
        if(index_1 == COL_NUM) {
            isDone = true;
            return;
        }

        if(arr[index_1] < arr[index_2]) {
            int t = arr[index_1];
            arr[index_1] = arr[index_2];
            arr[index_2] = t;
        }

        index_2++;
        if(index_2 == COL_NUM) {
            index_1++;
            index_2 = 0;
        }
    }
}

void DrawSS() {
    for(int i = 0; i < COL_NUM; i++) {
        int e = arr[i];

        //Draw column
        DrawRectangle(i * COL_WIDTH, SCREEN_HEIGHT - e, COL_WIDTH,
                      e, isDone ? COL_DONE_COLOR : COL_NOT_DONE_COLOR);
        
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