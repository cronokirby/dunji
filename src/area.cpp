#include <algorithm>
#include <iostream>
#include <math.h>
#include "../include/raylib.h"
#include "../include/area.hpp"
#include "../include/graphics.hpp"


enum class Floor {
    None,
    Tile0, Tile1, Tile2,
    Tile3, Tile4, Tile5,
    Tile6, Tile7,
    Wall
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
        case Floor::Wall:
            r = Rectangle { 1, 1, 1, 1 };
            break;
    }
    sheet.draw_pxpos(r, Vector2 { (float)x, (float)y });
}

int closest_index(float f, int res) {
    return (int) (f / res);
}


class AreaImpl {
    int floor_width;
    int floor_height;
    Floor* floor_tiles;
public:
    AreaImpl(int w, int h) : floor_width(w), floor_height(h) {
        floor_tiles = new Floor[w * h];
        for (int i = 0; i < w * h; ++i) {
            floor_tiles[i] = Floor::Tile0;
        }
        floor_tiles[21] = Floor::Wall;
    }

    ~AreaImpl() {
        delete[] floor_tiles;
    }

    int allowed_x(int x_mov, Rectangle box) const {
        int min_tile = closest_index(box.y, 48);
        int max_tile = closest_index(box.y + box.height, 48);

        int distance = 1000000;
        for (int y = min_tile; y <= max_tile; ++y) {
            if (x_mov < 0) {
                for (int x = 0; x < floor_width; ++x) {
                    auto tile = floor_tiles[y * floor_width + x];
                    if (tile == Floor::Wall) {
                        std::cout << x << "\n";
                        int d = abs((x + 1) * 48 - box.x);
                        distance = std::min(distance, d);
                    }
                 }            
            } else {
                for (int x = floor_width - 1; x >= 0; --x) {
                    auto tile = floor_tiles[y * floor_width + x];
                    if (tile == Floor::Wall) {
                        int d = abs((x - 1) * 48 - box.x);
                        distance = std::min(distance, d);
                    }
                }
            }
        }

        if (x_mov < 0) {
            return std::max(x_mov, -distance);
        } else {
            return std::min(distance, x_mov);
        }
    }

    void draw(const SpriteSheet& sheet) const {
        for (int y = 0; y < floor_height; ++y) {
            for (int x = 0; x < floor_width; ++x) {
                auto tile = floor_tiles[y * floor_width + x];
                draw_floor(sheet, tile, x, y);
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

int Area::allowed_x(int x_mov, Rectangle box) const {
    return pimpl->allowed_x(x_mov, box);
}

void Area::draw(const SpriteSheet& sheet) const {
    pimpl->draw(sheet);
}
