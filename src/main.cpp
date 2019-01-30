#include <iostream>
#include "../include/raylib.h"

#include "../include/graphics.hpp"


class Player {
    Vector2 pos;
    Sprite sprite;
public:
    Player() : sprite(Sprite::Boy1), pos(Vector2 { 0, 0 }) {}
    
    void update(float dT) {
        if (IsKeyDown(KEY_A)) {
            pos.x -= 200 * dT;
        } else if (IsKeyDown(KEY_W)) {
            pos.y -= 200 * dT;
        } else if (IsKeyDown(KEY_D)) {
            pos.x += 200 * dT;
        } else if (IsKeyDown(KEY_S)) {
            pos.y += 200 * dT;
        }
    }

    void draw(const SpriteSheet& sheet) const {
        sprite.draw(sheet, pos);
    }
};


int main() {
    InitWindow(1024, 768, "Hello World");

    SpriteSheet sheet(2, "../res/dunji-sheet.png");
    Player player {};

    SetTargetFPS(60);
    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(BLACK);
        float dT = GetFrameTime();
        player.update(dT);
        player.draw(sheet);
        EndDrawing();
    }
    CloseWindow();
    return 0;
}
