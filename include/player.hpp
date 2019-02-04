#ifndef PLAYER_H
#define PLAYER_H

class Area;
class Sprite;
class SpriteSheet;
class Vector2;
class Texture2D;


class Player {
    Vector2 pos;
    Sprite sprite;
    Texture2D real_sprite;
    int walk_timer;
public:
    Player();

    void update(const Area&, float);

    void draw(const SpriteSheet&) const;
};

#endif