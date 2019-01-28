#include <iostream>
#include "../include/raylib.h"


int main() {
    InitWindow(1024, 768, "Hello World");
    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(GetColor(0xFF0000FF));
        EndDrawing();
    }
    CloseWindow();
    return 0;
}
