#include <iostream>
#include "../include/raylib.h"

#include "../include/graphics.hpp"


int main() {
    InitWindow(1024, 768, "Hello World");

    SpriteSheet sheet(2, "../res/dunji-sheet.png");
    Sprite player(Sprite::Boy1);

    SetTargetFPS(60);
    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(BLACK);
        player.draw(sheet, GetMousePosition());
        EndDrawing();
    }
    CloseWindow();
    return 0;
}
