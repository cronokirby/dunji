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

    int allowed_x(int x_mov, Rectangle box) const;
    void draw(const SpriteSheet&) const;
};

#endif