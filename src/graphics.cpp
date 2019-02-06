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

Rectangle get_source(int scale, Rectangle r) {
    return Rectangle { scale * r.x, scale * r.y, scale * r.width, scale * r.height };
}

void SpriteSheet::draw(Rectangle px_source, Vector2 pos) const {
    auto source = get_source(px_scale, px_source);
    DrawTextureRec(texture, source, pos, WHITE);
}

void SpriteSheet::draw_pxpos(Rectangle px_source, Vector2 px_pos) const {
    auto scaled = Vector2 { px_pos.x * px_scale, px_pos.y * px_scale };
    draw(px_source, scaled);
}

void SpriteSheet::draw_rotated(Rectangle px_source, Vector2 pos, Vector2 origin, float rot) const {
    auto source = get_source(px_scale, px_source);
    auto dest = Rectangle { pos.x, pos.y, source.width, source.height };
    auto origi = Vector2 { source.width, source.height };
    DrawTexturePro(texture, source, dest, origin, rot, WHITE);
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

Rectangle get_source(Sprite::SpriteIDX sprite_i, Sprite::Orientation o) {
    Rectangle px_source = sprite_source(sprite_i);
    if (o == Sprite::Left) {
        px_source.y += 2;
    }
    return px_source;
}

void Sprite::draw(const SpriteSheet& sheet, Vector2 pos) const {
    Rectangle px_source = get_source(sprite_i, orientation);
    sheet.draw(px_source, pos);
}

void Sprite::draw_rotated(const SpriteSheet& sheet, Vector2 pos, Vector2 origin, float rot) const {
    Rectangle px_source = get_source(sprite_i, orientation);
    sheet.draw_rotated(px_source, pos, origin, rot);
}