#ifndef BFS_H
#define BFS_H

#include <vector>
#include <queue>
#include <string>

#include <raylib.h>

#include "salt.h"

#define     SCREEN_WIDTH    800
#define     SCREEN_HEIGHT   450

#define     NODE_SIZE       20
#define     ROW             SCREEN_HEIGHT / NODE_SIZE
#define     COL             SCREEN_WIDTH  / NODE_SIZE
#define     BLOCK_RATE      0.15

#define     BG_COLOR        BLACK

enum State {
    NOR,
    VISITED,
    FRONTIER,
    BLOCK,
    POINT,
    PATH
};

struct Node {
    State               state;
    std::vector<int>    nei;
    int                 parent;
};

static Node grid[ROW * COL];

static int start_index;
static int end_index;

static bool found;
static std::queue<int> bfs_frontier;

static bool debug;

void Init();

void BFSRun();
void DrawGrid();

void StartBFS();
void UpdateBFS();

void SetUpNode(int, int);
Color GetNodeColor(State);
bool AbleVisit(State);
void CreatePath();

#endif //BFS_H