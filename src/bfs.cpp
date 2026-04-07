#include "bfs.h"

void Init() {
    found = false;
    start_index = -1;
    end_index = -1;
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

void BFSRun() {
    Init();

    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "BFS");
    
    while(!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(BG_COLOR);

        if(IsKeyDown(KEY_R)) Init();

        if(IsKeyDown(KEY_F)) StartBFS();

        UpdateBFS();
        DrawGrid();

        DrawFPS(10, 10);
        EndDrawing();
    }
    CloseWindow();
}

void DrawGrid() {
    //Draw node
    for(int i = 0; i < ROW; i++) {
        for(int j = 0; j < COL; j++) {
            int index = i * COL + j;

            Color nodeColor = GetNodeColor(grid[index].state);
            if(index == start_index || index == end_index)
                nodeColor = GetNodeColor(POINT);

            DrawRectangle(j * NODE_SIZE, i * NODE_SIZE, NODE_SIZE, NODE_SIZE, nodeColor);

            if(debug) {
                int index = i * COL + j;
                DrawText(std::to_string(index).c_str(), j * NODE_SIZE + 5, i * NODE_SIZE + 5, 14, BLACK);
            }
        }
    }

    //Horizontal line
    for(int i = 0; i < ROW; i++) {
        DrawLine(0, i * NODE_SIZE, COL * NODE_SIZE, i * NODE_SIZE + 1, BG_COLOR);
    }

    //Vertical line
    for(int i = 0; i < COL; i++) {
        DrawLine(i * NODE_SIZE, 0, i * NODE_SIZE + 1, ROW * NODE_SIZE, BG_COLOR);
    }
}

void StartBFS() {
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
        start_index = GetRange(0, ROW * COL);
    } while (grid[start_index].state == BLOCK);

    do {
        end_index = GetRange(0, ROW * COL);
    } while (grid[end_index].state == BLOCK || end_index == start_index);

    grid[start_index].state = POINT;
    grid[end_index].state = POINT;

    //Clear bfs_frontier
    while(!bfs_frontier.empty()) {
        bfs_frontier.pop();
    }

    bfs_frontier.push(start_index);
    grid[start_index].state = FRONTIER;
}

void UpdateBFS() {
    if(found || bfs_frontier.empty()) {
        return;
    }

    int cur = bfs_frontier.front();
    bfs_frontier.pop();
    grid[cur].state = VISITED;

    for(const int& nei : grid[cur].nei) {
        if(!AbleVisit(grid[nei].state)) {
            continue;
        }

        //Founded
        if(nei == end_index) {
            grid[nei].parent = cur;
            grid[nei].state = VISITED;
            found = true;
            CreatePath();
            return;
        }

        bfs_frontier.push(nei);
        grid[nei].state = FRONTIER;
        grid[nei].parent = cur;
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

bool AbleVisit(State state) {
    switch(state) {
        case FRONTIER:
        case VISITED:
        case BLOCK:
            return false;
        default: return true;
    }
}

void CreatePath() {
    int cur = grid[end_index].parent;

    while(cur != start_index) {
        grid[cur].state = PATH;
        cur = grid[cur].parent;
    }

    grid[start_index].state = POINT;
    grid[start_index].state = POINT;
}