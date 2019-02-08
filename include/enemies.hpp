#ifndef ENEMIES_H
#define ENEMIES_H

#include "../include/graphics.hpp"

class Enemy {
public:
    virtual void draw(const SpriteSheet&) = 0;
};

class SqSprout : public Enemy {
    Sprite sprite;
    Vector2 pos;
public:
    SqSprout();
    void draw(const SpriteSheet&) override;
};

#endif