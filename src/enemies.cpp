#include "../include/raylib.h"
#include "../include/enemies.hpp"
#include "../include/graphics.hpp"


SqSprout::SqSprout() : sprite(Sprite::SqSprout0), pos(Vector2 { 200, 200 }) {}

void SqSprout::draw(const SpriteSheet& sheet) {
    sprite.draw(sheet, pos);
}
