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

    int allowed_x(int, Rectangle) const;
    int allowed_y(int, Rectangle) const;
    void draw(const SpriteSheet&) const;
};

#endif