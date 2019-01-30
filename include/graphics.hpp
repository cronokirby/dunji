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
};


// A Sprite we can draw. 
// Only a finite number of sprites are available,
// So the interior enum should be preferred to construct one.
struct Sprite {
    enum SpriteIDX {
        Boy1
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
};

#endif