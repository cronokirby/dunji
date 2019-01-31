#ifndef AREA_H
#define AREA_H

class SpriteSheet;
class AreaImpl;

class Area {
    AreaImpl* pimpl;
public:
    Area(int, int);
    ~Area();

    void draw(const SpriteSheet&) const;
};

#endif