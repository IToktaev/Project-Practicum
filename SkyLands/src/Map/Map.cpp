#include "TileType.h"
#include "Map.h"
#include <fstream>
#include <string>
#include <iostream>

TileType Map::MapGetTile(float worldX, float worldY) const {
    if (worldX < 0.0f || worldY < 0.0f) {
        return TileType::Empty;
    }

    const int col = static_cast<int>(worldX / TILE_SIZE);
    const int row = static_cast<int>(worldY / TILE_SIZE);

    if (col >= static_cast<int>(m_width) ||
        row >= static_cast<int>(m_height)) {
        return TileType::Empty;
    }

    const int index = row * static_cast<int>(m_width) + col;

    return m_grid[index];
}

bool Map::MapIsSolid(float worldX, float worldY) const  {
    return MapGetTile(worldX, worldY) == TileType::Solid;
}

void Map::MapInit() {
    std::ifstream file("../assets/levels/testLevel.txt");

    if (!file.is_open()) {
        std::cout << "Failed to open file\n";
        return;  
    }

    if (!m_tilesetTexture.loadFromFile("../assets/levels/tileset.png")) {
        std::cout << "Failed to open tileset\n";
        return;
    }

    m_grid.clear();
    m_width = 0;
    m_height = 0;

    std::string line;

    while (std::getline(file, line)) {
        m_width = line.size();

        for (int x = 0; x < m_width; x++) {
            if (line[x] == EMPTY_TILE) {
                m_grid.push_back(TileType::Empty);
            } else if (line[x] == SOLID_TILE) {
                m_grid.push_back(TileType::Solid);
            }
        }

        m_height++;
    }
}

void Map::MapDraw(sf::RenderWindow& window) {
    sf::Sprite tileSprite(m_tilesetTexture);

    for (int y = 0; y < m_height; y++) {
        for (int x = 0; x < m_width; x++) {
            int textureX = x * TILE_SIZE;
            int textureY = y * TILE_SIZE;

            tileSprite.setTextureRect(
                sf::IntRect(
                    {textureX, textureY},
                    {static_cast<int>(TILE_SIZE), static_cast<int>(TILE_SIZE)}
                )
            );
            
            tileSprite.setPosition({
                static_cast<float>(x * TILE_SIZE),
                static_cast<float>(y * TILE_SIZE)
            });

            window.draw(tileSprite);
        }
    }
}