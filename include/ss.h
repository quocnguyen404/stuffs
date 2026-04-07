#ifndef SS_H
#define SS_H

#include <vector>

#include <raylib.h>
#include "salt.h"

#define     SCREEN_WIDTH            800
#define     SCREEN_HEIGHT           450
#define     COL_WIDTH               5
#define     COL_NUM                 SCREEN_WIDTH / COL_WIDTH

#define     MIN_HEIGHT              50
#define     MAX_HEIGHT              SCREEN_HEIGHT - MIN_HEIGHT
#define     STEP_PER_FRAME          50

#define     COL_DONE_COLOR          GREEN
#define     COL_NOT_DONE_COLOR      WHITE
#define     COL_OUTLINE_COLOR       GRAY
#define     BG_COLOR                BLACK

static std::vector<int> arr;
static int index_1;
static int index_2;

static bool isDone;

void InitSS();
void RunSS();
void UpdateSS();
void DrawSS();



#endif //SS_H