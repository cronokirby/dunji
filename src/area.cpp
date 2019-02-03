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
    Wall0, Wall1, Wall2,
    WallRightCorner, WallLeftCorner,
    Edge0, Edge1, Edge2,
    EdgeRight, EdgeLeft,
    EdgeRightCorner, EdgeLeftCorner,
    InvisibleWall
};

void draw_floor(const SpriteSheet& sheet, Floor tile, int x, int y) {
    if (tile == Floor::None || tile == Floor::InvisibleWall) return;
    Rectangle r;
    bool is_edge = false;
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
        case Floor::Wall0:
            r = Rectangle { 1, 1, 1, 1 };
            break;
        case Floor::Wall1:
            r = Rectangle { 2, 1, 1, 1 };
            break;
        case Floor::Wall2:
            r = Rectangle { 3, 1, 1, 1 };
            break;
        case Floor::WallLeftCorner:
            r = Rectangle { 5, 9, 1, 1 };
            break;
        case Floor::WallRightCorner:
            r = Rectangle { 4, 9, 1, 1 };
            break;
        case Floor::Edge0:
            r = Rectangle { 1, 0, 1, 1 };
            is_edge = true;
            break;
        case Floor::Edge1:
            r = Rectangle { 2, 0, 1, 1 };
            is_edge = true;
            break;
        case Floor::Edge2:
            r = Rectangle { 3, 0, 1, 1 };
            is_edge = true;
            break;
        case Floor::EdgeLeft:
            r = Rectangle { 1, 8, 1, 1 };
            is_edge = true;
            break;
        case Floor::EdgeRight:
            r = Rectangle { 0, 8, 1, 1 };
            is_edge = true;
            break;
        case Floor::EdgeLeftCorner:
            r = Rectangle { 5, 8, 1, 1 };
            is_edge = true;
            break;
        case Floor::EdgeRightCorner:
            r = Rectangle { 4, 8, 1, 1 };
            is_edge = true;
            break;
    }
    sheet.draw_pxpos(Rectangle { 1, 4, 1, 1 }, Vector2 { (float)x, (float)y });
    sheet.draw_pxpos(r, Vector2 { (float)x, (float)y });
}

bool is_wall(Floor tile) {
    return tile == Floor::Wall0 || 
           tile == Floor::Wall1 ||
           tile == Floor::Wall2 ||
           tile == Floor::InvisibleWall;
}

int closest_index(float f, int res) {
    return (int) (f / res);
}


class AreaImpl {
    int floor_width;
    int floor_height;
    Floor* floor_tiles;
public:
    AreaImpl(int w, int h) : floor_width(w + 2), floor_height(h + 2) {
        int size = floor_width * floor_height;
        floor_tiles = new Floor[size];
        for (int i = 0; i < size; ++i) {
            floor_tiles[i] = Floor::Tile0;
        }
        for (int y = 0; y < floor_height; ++y) {
            floor_tiles[floor_width * y] = Floor::InvisibleWall;
            floor_tiles[floor_width * y + floor_width - 1] = Floor::InvisibleWall;
        }
        for (int x = 0; x < w + 2; ++x) {
            floor_tiles[x] = Floor::InvisibleWall;
            floor_tiles[floor_width * (floor_height - 1) + x] = Floor::InvisibleWall;
        }
        for (int y = 1; y <= 9; ++y) {
            floor_tiles[floor_width * y + 1] = Floor::EdgeLeft;
            floor_tiles[floor_width * y + floor_width - 2] = Floor::EdgeRight;
        }
        for (int x = 2; x <= 9; ++x) {
            floor_tiles[x] = Floor::Edge0;
            floor_tiles[floor_width * 1 + x] = Floor::Wall1;
            floor_tiles[floor_width * (floor_height - 1) + x] = Floor::Wall1;
            floor_tiles[floor_width * (floor_height - 2) + x] = Floor::Edge0;
        }
        floor_tiles[floor_width + 1] = Floor::WallLeftCorner;
        floor_tiles[1] = Floor::Edge0;
        floor_tiles[floor_width + floor_width - 2] = Floor::WallRightCorner;
        floor_tiles[floor_width - 2] = Floor::Edge2;
        floor_tiles[floor_width * (floor_height - 1) + 1] = Floor::Wall0;
        floor_tiles[floor_width * (floor_height - 2) + 1] = Floor::EdgeLeftCorner;
        floor_tiles[floor_width * (floor_height - 1) + floor_width - 2] = Floor::Wall2;
        floor_tiles[floor_width * (floor_height - 2) + floor_width - 2] = Floor::EdgeRightCorner;
    }

    ~AreaImpl() {
        delete[] floor_tiles;
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
                auto tile = floor_tiles[y * floor_width + x];
                if (is_wall(tile)) {
                    int delta;
                    if (left) {
                        delta = (x + 1) * 48 - box.x;
                        x_mov = std::max(-abs(delta), x_mov);
                    } else {
                        delta = x * 48 - (box.x + box.width);
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
                auto tile = floor_tiles[y * floor_width + x];
                if (is_wall(tile)) {
                    int delta;
                    if (up) {
                        delta = (y + 1) * 48 - box.y;
                        y_mov = std::max(-abs(delta), y_mov);
                    } else {
                        delta = y * 48 - (box.y + box.height);
                        y_mov = std::min(abs(delta), y_mov);
                    }
                }
            }
        }
        return y_mov;
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

Vector2 Area::allowed_move(Vector2 move, Rectangle box) const {
    return pimpl->allowed_move(move, box);
}

void Area::draw(const SpriteSheet& sheet) const {
    pimpl->draw(sheet);
}
