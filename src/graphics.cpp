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

void SpriteSheet::draw_pxpos(Rectangle px_source, Vector2 px_pos) const {
    auto scaled = Vector2 { px_pos.x * px_scale, px_pos.y * px_scale };
    draw(px_source, scaled);
}


Sprite::Sprite(SpriteIDX s, Orientation o) : sprite_i(s), orientation(o) {}
Sprite::Sprite(SpriteIDX sprite_i) : Sprite::Sprite(sprite_i, Right) {}

Rectangle sprite_source(const Sprite::SpriteIDX sprite) {
    switch (sprite) {
        case Sprite::Boy0:
            return Rectangle { 7, 4, 1, 2 };
        case Sprite::Boy1:
            return Rectangle { 8, 4, 1, 2 };
        case Sprite::Boy2:
            return Rectangle { 9, 4, 1, 2 };
        case Sprite::Boy3:
            return Rectangle { 10, 4, 1, 2 };
        case Sprite::Boy4:
            return Rectangle { 11, 4, 1, 2 };
        case Sprite::Boy5:
            return Rectangle { 12, 4, 1, 2 };
        case Sprite::Boy6:
            return Rectangle { 13, 4, 1, 2 };
        case Sprite::Boy7:
            return Rectangle { 14, 4, 1, 2 };
        case Sprite::Boy8:
            return Rectangle { 15, 4, 1, 2 };
        case Sprite::Knife:
            return Rectangle { 19, 6, 1, 2 };
    }
}

void Sprite::draw(const SpriteSheet& sheet, Vector2 pos) const {
    Rectangle px_source = sprite_source(sprite_i);
    if (orientation == Left) {
        px_source.y += 2;
    }
    sheet.draw(px_source, pos);
}
