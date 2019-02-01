#ifndef AREA_H
#define AREA_H

class AreaImpl;
class SpriteSheet;
class Rectangle;

class Area {
    AreaImpl* pimpl;
public:
    Area(int, int);
    ~Area();

    Vector2 allowed_move(Vector2, Rectangle) const;
    void draw(const SpriteSheet&) const;
};

#endif