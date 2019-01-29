#include <iostream>
#include "../include/raylib.h"


class SpriteSheet {
    int px_scale;
    Texture2D texture;
public:
    SpriteSheet(int scale, const char* file_name) {
        px_scale = scale * 16;
        auto image = LoadImage(file_name);
        ImageResizeNN(&image, image.width * scale, image.height * scale);
        texture = LoadTextureFromImage(image);
        UnloadImage(image);
    }

    ~SpriteSheet() {
        UnloadTexture(texture);
    }

    void draw(Rectangle px_source, Vector2 pos) const {
        auto source = Rectangle { 
            px_scale * px_source.x,
            px_scale * px_source.y,
            px_scale * px_source.width,
            px_scale * px_source.height,
        };
        DrawTextureRec(texture, source, pos, WHITE);
    }
};


// A Sprite we can draw. 
// Only a finite number of sprites are available,
// So the interior enum should be preferred to construct one.
class Sprite {
public:
    enum SpriteIDX {
        Boy1
    };

    Sprite(SpriteIDX sprite_i) : sprite_i(sprite_i) {}

    void draw(const SpriteSheet& sheet, Vector2 pos) const {
        Rectangle px_source = sprite_source();
        sheet.draw(px_source, pos);
    }

private:
    SpriteIDX sprite_i;

    Rectangle sprite_source() const {
        switch (sprite_i) {
            case Boy1:
                return Rectangle { 7, 4, 1, 2 };
        }
    }
};


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
