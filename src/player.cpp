#include <math.h>

#include "../include/raylib.h"
#include "../include/graphics.hpp"
#include "../include/player.hpp"


Player::Player() : 
    sprite(Sprite::Boy1), 
    pos(Vector2 { 100, 100 }),
    walk_timer(0) {}

Sprite::SpriteIDX next_player_walk(Sprite::SpriteIDX player_sprite) {
    switch (player_sprite) {
        case Sprite::Boy4:
            return Sprite::Boy5;
        case Sprite::Boy5:
            return Sprite::Boy6;
        case Sprite::Boy6:
            return Sprite::Boy7;
        default:
            return Sprite::Boy4;
    }
}


void Player::update(float dT) {
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
    float stretch = 300 * dT / length;
    // This is mainly to avoid the case where the length is 0, and we blow up
    if (length >= 1) {
        pos.x += direction.x *= stretch;
        pos.y += direction.y *= stretch;

        if (walk_timer >= 5) {
            sprite.sprite_i = next_player_walk(sprite.sprite_i);
            walk_timer = 0;
        }
        walk_timer += 1;
    } else {
        walk_timer = 0;
        sprite.sprite_i = Sprite::Boy1;
    }
}

void Player::draw(const SpriteSheet& sheet) const {
    sprite.draw(sheet, pos);
}
