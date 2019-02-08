#ifndef AREA_H
#define AREA_H

#include <memory>

class AreaImpl;
class SpriteSheet;
class Rectangle;
class Enemy;

class Area {
    AreaImpl* pimpl;
public:
    Area(int, int);
    ~Area();

    Vector2 allowed_move(Vector2, Rectangle) const;
    void draw_bottom(const SpriteSheet&) const;
    void draw_top(const SpriteSheet&) const;
    void add_enemy(std::unique_ptr<Enemy>);
};

#endif