#include "../include/raylib.h"
#include "../include/graphics.hpp"


SpriteSheet::SpriteSheet(int scale, const char* file_name) {
    px_scale = scale * 16;
    auto image = LoadImage(file_name);
    ImageResizeNN(&image, image.width * scale, image.height * scale);
    texture = LoadTextureFromImage(image);
    UnloadImage(image);
}

SpriteSheet::~SpriteSheet() {
    UnloadTexture(texture);
}

void SpriteSheet::draw(Rectangle px_source, Vector2 pos) const {
    auto source = Rectangle { 
        px_scale * px_source.x,
        px_scale * px_source.y,
        px_scale * px_source.width,
        px_scale * px_source.height,
    };
    DrawTextureRec(texture, source, pos, WHITE);
}


Sprite::Sprite(SpriteIDX s, Orientation o) : sprite_i(s), orientation(o) {}
Sprite::Sprite(SpriteIDX sprite_i) : Sprite::Sprite(sprite_i, Right) {}

void Sprite::draw(const SpriteSheet& sheet, Vector2 pos) const {
    Rectangle px_source = sprite_source();
    if (orientation == Left) {
        px_source.y += 2;
    }
    sheet.draw(px_source, pos);
}

Rectangle Sprite::sprite_source() const {
    switch (sprite_i) {
        case Boy1:
            return Rectangle { 7, 4, 1, 2 };
    }
}
