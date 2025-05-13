// TileMap.h
#ifndef TILEMAP_H
#define TILEMAP_H

#include "raylib.h"
#include "Geometry.h"
#include <vector>
#include <string>
#include <fstream>

class TileMap {
public:
    TileMap(const std::string& mapFile, Texture2D tileset, int tileSize = 32);
    void draw() const;
    void loadCollisionZones(std::vector<Rectangle>& collisionRects);

private:
    std::vector<std::string> mapData;
    Texture2D tileset;
    int tileSize;
};

#endif