#include <iostream>
#include <string>
#include <queue>
#include <vector>

#include <raylib.h>
#include "salt.h"

#define SCREEN_WIDHT 800
#define SCREEN_HEIGHT 450
#define CELL_SIZE 20
#define ROW SCREEN_HEIGHT / CELL_SIZE
#define COL SCREEN_WIDHT / CELL_SIZE
#define BG_COLOR BLACK
#define BLOCK_RATE 0.15
// #define CALL_TIME 0.0

// #define START_INDEX 0
// #define END_INDEX ROW * COL - 1

enum State {
    NOR,
    VISITED,
    FRONTIER,
    BLOCK,
    POINT,
    PATH
};

struct Node {
    State state;
    std::vector<int> nei;
    int parent;
};

Node grid[ROW * COL];

static int START_INDEX;
static int END_INDEX;

void Init();
void DrawGrid(bool);
Color GetNodeColor(State);
void SetUpNode(int, int);

void InitBFS();
void UpdateBFS();
bool IsNotVisit(State);
void CreatePath();

int main() {
    bool debug = false;
    Init();

    InitWindow(SCREEN_WIDHT, SCREEN_HEIGHT, "Path finding");
    // SetTargetFPS(60);

    while(!WindowShouldClose()) {
        
        BeginDrawing();
        ClearBackground(BG_COLOR);

        if(IsKeyDown(KEY_R)) {
            Init();
        }

        if(IsKeyDown(KEY_F)) {
            InitBFS();
        }

        UpdateBFS();
        DrawGrid(debug);

        DrawFPS(10, 10);
        EndDrawing();
    }

    CloseWindow();
}

void Init() {
    START_INDEX = -1;
    END_INDEX = -1;
    for(int i = 0; i < ROW; i++) {
        for(int j = 0; j < COL; j++) {
            int index = i * COL + j;

            if(GetRandom() <= BLOCK_RATE) {
                grid[index].state = BLOCK;
                continue;
            }

            grid[index].state = NOR;
            SetUpNode(i, j);
        }
    }
}

void DrawGrid(bool debug) {
    //Draw node
    for(int i = 0; i < ROW; i++) {
        for(int j = 0; j < COL; j++) {
            int index = i * COL + j;

            Color nodeColor = GetNodeColor(grid[index].state);
            if(index == START_INDEX || index == END_INDEX)
                nodeColor = GetNodeColor(POINT);

            DrawRectangle(j * CELL_SIZE, i * CELL_SIZE, CELL_SIZE, CELL_SIZE, nodeColor);

            if(debug) {
                int index = i * COL + j;
                DrawText(std::to_string(index).c_str(), j * CELL_SIZE + 5, i * CELL_SIZE + 5, 14, BLACK);
            }
        }
    }

    //Horizontal line
    for(int i = 0; i < ROW; i++) {
        DrawLine(0, i * CELL_SIZE, COL * CELL_SIZE, i * CELL_SIZE + 1, BG_COLOR);
    }

    //Vertical line
    for(int i = 0; i < COL; i++) {
        DrawLine(i * CELL_SIZE, 0, i * CELL_SIZE + 1, ROW * CELL_SIZE, BG_COLOR);
    }
}

Color GetNodeColor(State state) {
    switch(state) {
        case NOR: return GRAY;
        case VISITED: return YELLOW;
        case FRONTIER: return GREEN;
        case BLOCK: return BG_COLOR;
        case POINT: return RED;
        case PATH: return BLUE;
        default: return GRAY;
    }
}

void SetUpNode(int i, int j) {
    int index = i * COL + j;
    int north = (i - 1) * COL + j;
    int south = (i + 1) * COL + j;
    int west = i * COL + j - 1;
    int east = i * COL + j + 1;

    //north
    if(i > 0) {
        grid[index].nei.push_back(north);
    }

    //south
    if(i < ROW - 1) {
        grid[index].nei.push_back(south);
    }

    //west
    if(j > 0) {
        grid[index].nei.push_back(west);
    }

    //east
    if(j < COL - 1) {
        grid[index].nei.push_back(east);
    }
}

bool found = true;
std::queue<int> frontier;

void InitBFS() {
    //Clear grid

    found = false;

    for(int i = 0; i < ROW; i++) {
        for(int j = 0; j < COL; j++) {
            int index = i * COL + j;
            if(grid[index].state != BLOCK) {
                grid[index].state = NOR;
            }
        }
    }

    do {
        START_INDEX = GetRange(0, ROW * COL);
    } while (grid[START_INDEX].state == BLOCK);

    do {
        END_INDEX = GetRange(0, ROW * COL);
    } while (grid[END_INDEX].state == BLOCK || END_INDEX == START_INDEX);

    grid[START_INDEX].state = POINT;
    grid[END_INDEX].state = POINT;

    //Clear frontier
    while(!frontier.empty()) {
        frontier.pop();
    }

    frontier.push(START_INDEX);
    grid[START_INDEX].state = FRONTIER;
}

void UpdateBFS() {
    if(found || frontier.empty()) {
        return;
    }

    int cur = frontier.front();
    frontier.pop();
    grid[cur].state = VISITED;

    for(auto nei : grid[cur].nei) {
        if(IsNotVisit(grid[nei].state))
            continue;

        //Found
        if(nei == END_INDEX) {
            grid[nei].parent = cur;
            grid[nei].state = VISITED;
            found = true;
            CreatePath();
            return;
        }
        
        frontier.push(nei);
        grid[nei].state = FRONTIER;
        grid[nei].parent = cur;
    }
}

bool IsNotVisit(State state) {
    switch(state) {
        case FRONTIER:
        case VISITED:
        case BLOCK:
        // case POINT:
            return true;
        default: return false;
    }
}

void CreatePath() {
    int cur = grid[END_INDEX].parent;

    while(cur != START_INDEX) {
        grid[cur].state = PATH;
        cur = grid[cur].parent;
    }

    grid[START_INDEX].state = POINT;
    grid[END_INDEX].state = POINT;
}