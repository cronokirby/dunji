#include <iostream>
#include <math.h>
#include "../include/raylib.h"

#include "../include/graphics.hpp"


class Player {
    Vector2 pos;
    Sprite sprite;
public:
    Player() : sprite(Sprite::Boy1), pos(Vector2 { 100, 100 }) {}
    
    void update(float dT) {
        Vector2 direction { 0, 0 };
        if (IsKeyDown(KEY_A)) {
            direction.x = -1;
            sprite.orientation = Sprite::Left;
        } else if (IsKeyDown(KEY_D)) {
            direction.x = 1;
            sprite.orientation = Sprite::Right;
        }
        if (IsKeyDown(KEY_W)) {
            direction.y = -1;
        } else if (IsKeyDown(KEY_S)) {
            direction.y = 1;
        }
        float length = sqrt(direction.x * direction.x + direction.y * direction.y);
        float stretch = 200 * dT / length;
        // This is mainly to avoid the case where the length is 0, and we blow up
        if (length >= 1) {
            pos.x += direction.x *= stretch;
            pos.y += direction.y *= stretch;
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
