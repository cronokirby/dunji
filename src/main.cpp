#include <iostream>
#include "../include/raylib.h"

#include "../include/area.hpp"
#include "../include/graphics.hpp"
#include "../include/player.hpp"


int main() {
    InitWindow(1024, 768, "Dunji");

    SpriteSheet sheet(3, "../res/dunji-sheet.png");
    Player player {};
    Area area(10, 10);

    SetTargetFPS(60);
    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(BLACK);
        float dT = GetFrameTime();
        player.update(area, dT);
        area.draw(sheet);
        player.draw(sheet);
        EndDrawing();
    }
    CloseWindow();
    return 0;
}
