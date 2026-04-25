#include "ss.h"

int main() {
    SetTraceLogLevel(LOG_NONE);
    SetConfigFlags(FLAG_WINDOW_UNDECORATED);
    SetWindowPosition(1920/2, 1080/2);
    RunSS();
}