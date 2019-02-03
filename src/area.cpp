#include <algorithm>
#include <iostream>
#include <math.h>
#include "../include/raylib.h"
#include "../include/area.hpp"
#include "../include/graphics.hpp"


template <typename T>
class FixedArr {
    T* data;
public:
    const int width;
    const int height;

    FixedArr(int w, int h) : width(w), height(h) {
        data = new T[w * h];
    }

    ~FixedArr() {
        delete[] data;
    }

    inline T get(int x, int y) const {
        return data[width * y + x];
    }

    inline void set(int x, int y, T t) {
        data[width * y + x] = t;
    }

    inline void set_all(T t) {
        for (int i = 0; i < width * height; ++i) {
            data[i] = t;
        }
    }
};


enum class Floor {
    None,
    Tile0, Tile1, Tile2,
    Tile3, Tile4, Tile5,
    Tile6, Tile7
};

void draw_floor(const SpriteSheet& sheet, Floor tile, int x, int y) {
    if (tile == Floor::None) return;
    Rectangle r;
    switch (tile) {
        case Floor::Tile0:
            r = Rectangle { 1, 4, 1, 1 };
            break;
        case Floor::Tile1:
            r = Rectangle { 2, 4, 1, 1 };
            break;
        case Floor::Tile2:
            r = Rectangle { 3, 4, 1, 1 };
            break;
        case Floor::Tile3:
            r = Rectangle { 1, 5, 1, 1 };
            break;
        case Floor::Tile4:
            r = Rectangle { 2, 5, 1, 1 };
            break;
        case Floor::Tile5:
            r = Rectangle { 3, 5, 1, 1 };
            break;
        case Floor::Tile6:
            r = Rectangle { 1, 6, 1, 1 };
            break;
        case Floor::Tile7:
            r = Rectangle { 2, 6, 1, 1 };
            break;
    }
    sheet.draw_pxpos(r, Vector2 { (float)x, (float)y });
}


enum class Wall {
    None,
    Left, Mid, Right,
    LeftCorner, RightCorner,
    EdgeLeft, EdgeMid, EdgeRight,
    EdgeLeftSide, EdgeRightSide,
    EdgeLeftCorner, EdgeRightCorner
};

bool is_top_wall(Wall wall) {
    return wall == Wall::EdgeLeft || 
           wall == Wall::EdgeMid || 
           wall == Wall::EdgeRight ||
           wall == Wall::EdgeLeftCorner ||
           wall == Wall::EdgeRightCorner;
}

// Returns all coordinates less than 0 if no collision
Rectangle wall_collision(Wall wall) {
    switch (wall) {
        case Wall::Left:
            return Rectangle { 0, 0, 48, 48 };
        case Wall::Mid:
            return Rectangle { 0, 0, 48, 48 };
        case Wall::Right:
            return Rectangle { 0, 0, 48, 48 };
        case Wall::LeftCorner:
            return Rectangle { 0, 0, 48, 48 };
        case Wall::RightCorner:
            return Rectangle { 0, 0, 48, 48 };
        case Wall::EdgeLeftSide:
            return Rectangle { 0, 0, 15, 48 };
        case Wall::EdgeRightSide:
            return Rectangle { 33, 0, 15, 48 };
        case Wall::EdgeLeftCorner:
            return Rectangle { 0, 0, 15, 48 };
        case Wall::EdgeRightCorner:
            return Rectangle { 33, 0, 15, 48 };
    }
    return Rectangle { -1, -1, -1, -1 };
}

void draw_wall(const SpriteSheet& sheet, Wall tile, int x, int y) {
    if (tile == Wall::None) return;
    Rectangle r;
    switch (tile) {
        case Wall::Left:
            r = Rectangle { 1, 1, 1, 1 };
            break;
        case Wall::Mid:
            r = Rectangle { 2, 1, 1, 1 };
            break;
        case Wall::Right:
            r = Rectangle { 3, 1, 1, 1 };
            break;
        case Wall::LeftCorner:
            r = Rectangle { 5, 9, 1, 1 };
            break;
        case Wall::RightCorner:
            r = Rectangle { 4, 9, 1, 1 };
            break;
        case Wall::EdgeLeft:
            r = Rectangle { 1, 0, 1, 1 };
            break;
        case Wall::EdgeMid:
            r = Rectangle { 2, 0, 1, 1 };
            break;
        case Wall::EdgeRight:
            r = Rectangle { 3, 0, 1, 1 };
            break;
        case Wall::EdgeLeftSide:
            r = Rectangle { 1, 8, 1, 1 };
            break;
        case Wall::EdgeRightSide:
            r = Rectangle { 0, 8, 1, 1 };
            break;
        case Wall::EdgeLeftCorner:
            r = Rectangle { 5, 8, 1, 1 };
            break;
        case Wall::EdgeRightCorner:
            r = Rectangle { 4, 8, 1, 1 };
            break;
    }
    sheet.draw_pxpos(r, Vector2 { (float)x, (float)y });
}


int closest_index(float f, int res) {
    return (int) (f / res);
}


class AreaImpl {
    FixedArr<Floor> floors;
    FixedArr<Wall> walls;
public:
    AreaImpl(int w, int h) : floors(w, h), walls(w, h) {
        floors.set_all(Floor::None);
        for (int y = 1; y < floors.height; ++y) {
            for (int x = 0; x < floors.width; ++x) {
                floors.set(x, y, Floor::Tile0);
            }
        }
        for (int x = 1; x < walls.width - 1; ++x) {
            walls.set(x, 0, Wall::EdgeMid);
            walls.set(x, 1, Wall::Mid);
            walls.set(x, walls.height - 1, Wall::Mid);
            walls.set(x, walls.height - 2, Wall::EdgeMid);
        }
        std::cout << (int)floors.get(2, 0) << "\n";
        for (int y = 1; y < walls.height - 2; ++y) {
            walls.set(0, y, Wall::EdgeLeftSide);
            walls.set(walls.width - 1, y, Wall::EdgeRightSide);
        }
        walls.set(0, walls.height - 2, Wall::EdgeLeftCorner);
        walls.set(0, walls.height - 1, Wall::Left);
        walls.set(0, 1, Wall::LeftCorner);
        walls.set(0, 0, Wall::EdgeLeft);
        walls.set(walls.width - 1, walls.height - 2, Wall::EdgeRightCorner);
        walls.set(walls.width - 1, walls.height - 1, Wall::Right);
        walls.set(walls.width - 1, 1, Wall::RightCorner);
        walls.set(walls.width - 1, 0, Wall::EdgeRight);
    }

    Vector2 allowed_move(Vector2 mov, Rectangle box) const {
        if (mov.x != 0) {
            mov.x = allowed_x(mov.x, box);
        }
        if (mov.y != 0) {
            mov.y = allowed_y(mov.y, box);
        }
        return mov;
    }


    int allowed_x(int x_mov, Rectangle box) const {
        int min_tile = closest_index(box.y, 48);
        int max_tile = closest_index(box.y + box.height - 1, 48);
        bool left = x_mov < 0;

        int right_x = box.x + box.width - 1;

        int min_x = closest_index(left ? box.x + x_mov : box.x, 48);
        int max_x = closest_index(left ? right_x : right_x + x_mov, 48);
        for (int y = min_tile; y <= max_tile; ++y) {
            for (int x = min_x; x <= max_x; ++x) {
                auto wall = walls.get(x, y);
                auto coll = wall_collision(wall);
                if (coll.x >= 0) {
                    if (left) {
                        int delta = x * 48 + coll.x + coll.width - box.x;
                        x_mov = std::max(-abs(delta), x_mov);
                    } else {
                        int delta = x * 48 + coll.x - (box.x + box.width);
                        x_mov = std::min(abs(delta), x_mov);
                    }
                }
            }
        }
        return x_mov;
    }

    int allowed_y(int y_mov, Rectangle box) const {
        int min_tile = closest_index(box.x, 48);
        int max_tile = closest_index(box.x + box.width - 1, 48);
        bool up = y_mov < 0;

        int down_y = box.y + box.height - 1;

        int min_y = closest_index(up ? box.y + y_mov : box.y, 48);
        int max_y = closest_index(up ? down_y : down_y + y_mov, 48);
        for (int y = min_y; y <= max_y; ++y) {
            for (int x = min_tile; x <= max_tile; ++x) {
                auto wall = walls.get(x, y);
                auto coll = wall_collision(wall);
                if (coll.x >= 0) {
                    if (up) {
                        int delta = y * 48 + coll.y + coll.height - box.y;
                        y_mov = std::max(-abs(delta), y_mov);
                    } else {
                        int delta = y * 48 + coll.y - (box.y + box.height);
                        y_mov = std::min(abs(delta), y_mov);
                    }
                }
            }
        }
        return y_mov;
    }

    void draw_bottom(const SpriteSheet& sheet) const {
        for (int y = 0; y < floors.height; ++y) {
            for (int x = 0; x < floors.width; ++x) {
                auto flor = floors.get(x, y);
                draw_floor(sheet, flor, x, y);
                auto wall = walls.get(x, y);
                draw_wall(sheet, wall, x, y);
            }
        }
    }

    void draw_top(const SpriteSheet& sheet) const {
        for (int y = 0; y < walls.height; ++y) {
            for (int x = 0; x < walls.width; ++x) {
                auto wall = walls.get(x, y);
                if (is_top_wall(wall)) {
                    draw_wall(sheet, wall, x, y);
                }
            }
        }
    }
};


Area::Area(int w, int h) {
    pimpl = new AreaImpl(w, h);
}

Area::~Area() {
    delete pimpl;
}

Vector2 Area::allowed_move(Vector2 move, Rectangle box) const {
    return pimpl->allowed_move(move, box);
}

void Area::draw_bottom(const SpriteSheet& sheet) const {
    pimpl->draw_bottom(sheet);
}

void Area::draw_top(const SpriteSheet& sheet) const {
    pimpl->draw_top(sheet);
}
