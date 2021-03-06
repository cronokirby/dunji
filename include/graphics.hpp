#ifndef GRAPHICS_H
#define GRAPHICS_H

// Forward declarations from raylib
class Rectangle;
class Texture2d;
class Vector2;


class SpriteSheet {
    int px_scale;
    Texture2D texture;
public:
    SpriteSheet(int scale, const char* file_name);
    ~SpriteSheet();
    void draw(Rectangle px_source, Vector2 pos) const;
    void draw_pxpos(Rectangle px_source, Vector2 pos) const;
    void draw_rotated(Rectangle, Vector2, Vector2, float) const;
};


// A Sprite we can draw. 
// Only a finite number of sprites are available,
// So the interior enum should be preferred to construct one.
struct Sprite {
    enum SpriteIDX {
        Boy0, Boy1, Boy2, Boy3, Boy4, Boy5, Boy6, Boy7, Boy8,
        SqSprout0, SqSprout1, SqSprout2, SqSprout3,
        SqSprout4, SqSprout5, SqSprout6, SqSprout7,
        SqSprout8,
        Knife
    };

    enum Orientation {
        Left,
        Right
    };

    SpriteIDX sprite_i;
    Orientation orientation;
    
    Sprite(SpriteIDX sprite_i);
    Sprite(SpriteIDX s, Orientation o);

    void draw(const SpriteSheet& sheet, Vector2 pos) const;
    void draw_rotated(const SpriteSheet&, Vector2, Vector2, float) const;
};

#endif