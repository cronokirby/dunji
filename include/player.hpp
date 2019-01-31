#ifndef PLAYER_H
#define PLAYER_H

class Vector2;
class Sprite;
class SpriteSheet;


class Player {
    Vector2 pos;
    Sprite sprite;
    int walk_timer;
public:
    Player();

    void update(float);

    void draw(const SpriteSheet&) const;
};

#endif