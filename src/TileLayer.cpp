#include "TileLayer.h"
#include "Game.h"
#include "TextureManager.h"
#include "Level.h"
#include "raymath.h"
#include <iostream>

TileLayer::TileLayer(int tileSize, const std::vector<Tileset> &tilesets) : m_tileSize(tileSize), m_position{0.0f, 0.0f}, m_velocity{0.0f, 0.0f}, m_tilesets(tilesets)
{
    m_numColumns = Game::Instance()->getGameWidth() / m_tileSize;
    m_numRows = Game::Instance()->getGameHeight() / m_tileSize;
}

void TileLayer::update(Level *pLevel)
{
    // m_position = Vector2Add(m_position,m_velocity);
    // m_velocity.setX(1);
}

void TileLayer::render(void)
{
    std::cout << "rendering TileLayer\n";
    int x, y, xOffset, yOffset = 0;

    y = int(m_position.y) / m_tileSize;
    x = int(m_position.x) / m_tileSize;

    xOffset = int(m_position.x) % m_tileSize;
    yOffset = int(m_position.y) % m_tileSize;

    int rowMax = m_numRows + 1;
    int columnMax = m_numColumns + 1;
    // std::cout << "TileLayer::render() -- m_numRows: " << m_numRows << ", m_numColumns: " << m_numColumns << "\n";
    for (int i = 0; i < rowMax; i++)
    {
        for (int j = 0; j < columnMax; j++)
        {
            int id = getTileIDByPosition(j + x, i + y);
            // std::cout << "id: " << id << "\n";
            // m_tileIDs[i + y][j + x];
            if (id == 0)
            {
                continue;
            }
            Tileset tileset = getTilesetByID(id);
            id--;
            // std::cout << "id: " << id << "\n";
            // std::cout << "tileset.firstGridID: " << tileset.firstGridID << "\n";
            // std::cout << "tileset.name: " << tileset.name << "\n";
            // std::cout << "tileset.numColumns: " << tileset.numColumns << "\n";
            // std::cout << "(id - (tileset.firstGridID - 1)) % tileset.numColumns: " << (id - (tileset.firstGridID - 1)) % tileset.numColumns << "\n";
            // std::cout << "(id - (tileset.firstGridID - 1)) / tileset.numColumns: " << (id - (tileset.firstGridID - 1)) / tileset.numColumns << "\n";
            TextureManager::Instance()->drawTile(tileset.name, tileset.margin, tileset.spacing, (j * m_tileSize) - xOffset, (i * m_tileSize) - yOffset, m_tileSize, m_tileSize, (id - (tileset.firstGridID - 1)) / tileset.numColumns, (id - (tileset.firstGridID - 1)) % tileset.numColumns);
            // std::cout << "Done with drawTile\n";
        }
    }
}

Tileset TileLayer::getTilesetByID(int tileID)
{
    for (unsigned int i = 0; i < m_tilesets.size(); i++)
    {
        if (i + 1 <= m_tilesets.size() - 1 && tileID >= m_tilesets[i].firstGridID && tileID < m_tilesets[i + 1].firstGridID)
        {
            return m_tilesets[i];
        }
    }
    if (m_tilesets.size() > 0)
    {
        return m_tilesets[m_tilesets.size() - 1];
    }
    else
    {
        std::cout << "did not find any tileset, returning empty tileset\n";
        Tileset t = {0, 0, 0, 0, 0, 0, 0, 0, ""};
        return t;
    }
}

int TileLayer::getTileIDByPosition(int xIndex, int yIndex)
{
    int xIndexMax = m_tileIDs[0].size();
    int yIndexMax = m_tileIDs.size();
    if ((xIndex < 0) || (xIndexMax <= xIndex) || (yIndex < 0) || (yIndexMax <= yIndex))
    {
        return 0;
    }
    return m_tileIDs[yIndex][xIndex];
}