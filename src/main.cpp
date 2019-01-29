#include <iostream>
#include "../include/raylib.h"


// A Sprite we can draw. 
// Only a finite number of sprites are available,
// So the interior enum should be preferred to construct one.
class Sprite {
public:
    enum SpriteIDX {
        Boy1
    };

    Sprite(SpriteIDX sprite_i) : sprite_i(sprite_i) {}

private:
    SpriteIDX sprite_i;
};


int main() {
    InitWindow(1024, 768, "Hello World");

    auto image = LoadImage("../res/dunji-sheet.png");
    ImageResizeNN(&image, image.width * 2, image.height * 2);
    auto sheet = LoadTextureFromImage(image);
    UnloadImage(image);
    SetTargetFPS(60);
    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(BLACK);
        DrawTexture(sheet, 0, 0, WHITE);
        EndDrawing();
    }
    UnloadTexture(sheet);
    CloseWindow();
    return 0;
}
