#include <math.h>

#include "../include/raylib.h"
#include "../include/area.hpp"
#include "../include/graphics.hpp"
#include "../include/player.hpp"


Player::Player() : 
    sprite(Sprite::Boy1), 
    pos(Vector2 { 100, 150 }),
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

Rectangle player_walk_box(Vector2 pos) {
    return Rectangle { pos.x + 9, pos.y + 48 + 21, 48 - 18, 48 - 21 };
}


void Player::update(const Area& area, float dT) {
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
    float stretch = 400 * dT / length;
    if (IsKeyDown(KEY_LEFT_SHIFT)) {
        stretch /= 80;
    }
    // This is mainly to avoid the case where the length is 0, and we blow up
    if (length >= 1) {
        Vector2 try_move { direction.x * stretch, direction.y * stretch };
        auto collision = player_walk_box(pos);
        auto move = area.allowed_move(try_move, collision);
        pos.x += move.x;
        pos.y += move.y;

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
