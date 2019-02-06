#ifndef PLAYER_H
#define PLAYER_H

class Area;
class Sprite;
class Vector2;


class Weapon {
    Sprite sprite;
    Vector2 offset;
    float rotation;
    bool done_slashing;
public:
    Weapon();
    void set_orientation(Sprite::Orientation);
    void update(float);
    bool done() const;
    void draw(const SpriteSheet&, Vector2) const;
};

class Player {
    Vector2 pos;
    Weapon weapon;
    bool attacking;
    Sprite sprite;
    int walk_timer;
public:
    Player();

    void update(const Area&, float);

    void draw(const SpriteSheet&) const;
};

#endif