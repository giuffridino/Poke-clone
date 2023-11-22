#pragma once
#ifndef __TileLayer__
#define __TileLayer__

#include <raylib.h>
#include <vector>
#include "Layer.h"

class Level;
struct Tileset;

class TileLayer : public Layer
{
public:
    TileLayer(int tileSize, const std::vector<Tileset> &tilesets);
    virtual ~TileLayer(void){};

    virtual void update(Level *pLevel);
    virtual void render(void);

    void setTileIDs(const std::vector<std::vector<int>> &data) { m_tileIDs = data; }
    void setTileSize(int tileSize) { m_tileSize = tileSize; }
    void setMapWidth(int mapWidth) { m_mapWidth = mapWidth; }
    int getTileIDByPosition(int xIndex, int yIndex);
    Tileset getTilesetByID(int tileID);
    int getTileSize(void) { return m_tileSize; }
    const std::vector<std::vector<int>> &getTileIDs(void) { return m_tileIDs; }
    const Vector2 getPosition(void) { return m_position; }

private:
    int m_numColumns;
    int m_numRows;
    int m_tileSize;
    int m_mapWidth;
    Vector2 m_position;
    Vector2 m_velocity;
    const std::vector<Tileset> &m_tilesets;
    std::vector<std::vector<int>> m_tileIDs;
};
#endif /* defined(__TileLayer__) */