#include <iostream>
#include "../include/raylib.h"
#include "../include/area.hpp"
#include "../include/graphics.hpp"


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
    sheet.draw_pxpos(r, Vector2 { x, y });
}


class Wall {
    Vector2 pos;
public:
    Wall(int x, int y) {
        // 3x 16x16 sprites
        pos = Vector2 { x * 48, y * 48 };
    }

    Wall() : Wall(0, 0) {}

    Rectangle hitbox() const {
        return Rectangle { pos.x, pos.y, 48, 48 };
    }

    void draw(const SpriteSheet& sheet) const {
        auto source = Rectangle { 1, 1, 1, 1 };
        sheet.draw(source, pos);
    }
};

class AreaImpl {
    int floor_width;
    int floor_height;
    Floor* floor_tiles;
    int wall_count;
    Wall* walls;
public:
    AreaImpl(int w, int h) : floor_width(w), floor_height(h) {
        floor_tiles = new Floor[w * h];
        for (int i = 0; i < w * h; ++i) {
            floor_tiles[i] = Floor::Tile0;
        }
        wall_count = 1;
        walls = new Wall[1];
        walls[0] = Wall(10, 10);
    }

    ~AreaImpl() {
        delete[] floor_tiles;
        delete[] walls;
    }

    void draw(const SpriteSheet& sheet) const {
        for (int y = 0; y < floor_height; ++y) {
            for (int x = 0; x < floor_width; ++x) {
                auto tile = floor_tiles[y * floor_width + x];
                draw_floor(sheet, tile, x, y);
            }
        }
        for (int i = 0; i < wall_count; ++i) {
            walls[i].draw(sheet);
        }
    }
};


Area::Area(int w, int h) {
    pimpl = new AreaImpl(w, h);
}

Area::~Area() {
    delete pimpl;
}

void Area::draw(const SpriteSheet& sheet) const {
    pimpl->draw(sheet);
}
