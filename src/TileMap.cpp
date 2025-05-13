// TileMap.cpp
#include "TileMap.h"
#include <iostream>

TileMap::TileMap(const std::string& mapFile, Texture2D tileset, int tileSize)
    : tileset(tileset), tileSize(tileSize) {
    std::ifstream file(mapFile);
    std::string line;
    while (std::getline(file, line)) {
        mapData.push_back(line);
    }
}

void TileMap::draw() const {
    for (size_t y = 0; y < mapData.size(); ++y) {
        for (size_t x = 0; x < mapData[y].size(); ++x) {
            char tile = mapData[y][x];
            Rectangle source = { 0, 0, (float)tileSize, (float)tileSize };

            if (tile == '#') {
                source.x = (float)tileSize; // muro
            } else {
                source.x = 0; // suelo
            }

            Vector2 position = { x * tileSize * 1.0f, y * tileSize * 1.0f };
            DrawTextureRec(tileset, source, position, WHITE);
        }
    }
}

void TileMap::loadCollisionZones(std::vector<Rectangle>& collisionRects) {
    for (size_t y = 0; y < mapData.size(); ++y) {
        for (size_t x = 0; x < mapData[y].size(); ++x) {
            if (mapData[y][x] == '#') {
                Rectangle rect = {
                    x * tileSize * 1.0f,
                    y * tileSize * 1.0f,
                    (float)tileSize,
                    (float)tileSize
                };
                collisionRects.push_back(rect);
            }
        }
    }
}
