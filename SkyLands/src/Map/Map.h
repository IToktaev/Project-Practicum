#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "TileType.h"

const uint32_t TILE_SIZE = 50;

struct EntityTile {
    int col;
    int row;
};

class Map {
    public:
        void MapInit(int mapId);
        void MapDraw(sf::RenderWindow& window);
        TileType MapGetTile(float worldX, float worldY) const;
        bool MapIsSolid(float worldX, float worldY) const;

        uint32_t GetWidth() { return m_width; }
        uint32_t GetHeight() { return m_height; }
        std::vector<EntityTile> GetThorns() { return m_thorns; }
        std::vector<EntityTile> GetKits() { return m_kits; }

    private:
        std::vector<TileType> m_grid;
        uint32_t m_width = 0;
        uint32_t m_height = 0;
        sf::Texture m_tilesetTexture;
        
        std::vector<EntityTile> m_thorns;
        std::vector<EntityTile> m_kits;
};