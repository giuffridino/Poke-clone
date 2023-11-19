#pragma once
#ifndef __Level__
#define __Level__

#include <string>
#include "Player.h"
#include "TileLayer.h"

struct Tileset
{
    int firstGridID;
    int tileWidth;
    int tileHeight;
    int spacing;
    int margin;
    int width;
    int height;
    int numColumns;
    std::string name;
};

class Level
{
public:
	
	~Level(void);
    void render(void);
    void update(void);

    std::vector<Tileset>* getTilesets(void) { return &m_tilesets; }
    std::vector<Layer*>* getLayers(void) { return &m_layers; }
    std::vector<TileLayer*>* getCollisionLayers(void) { return &m_collisionLayers; }
    const std::vector<TileLayer*>& getCollidableLayers(void) { return m_collisionLayers; }

    void setPlayer(Player* pPlayer) { m_pPlayer = pPlayer; }
    Player* getPlayer(void) { return m_pPlayer; }

private:
    friend class LevelParser;
    Level(void);
    
    Player* m_pPlayer; 

    std::vector<Tileset> m_tilesets;
    std::vector<Layer*> m_layers;
    std::vector<TileLayer*> m_collisionLayers;
};
#endif /* defined(__Level__) */