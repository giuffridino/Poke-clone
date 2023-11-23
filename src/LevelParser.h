#pragma once
#ifndef __LevelParser__
#define __LevelParser__

#include "Level.h"
#include "tinyxml.h"
#include <vector>

class LevelParser
{
public:
    Level* parseLevel(const char* levelFile);

private:
    void parseTilesets(TiXmlElement* pTilesetRoot, std::vector<Tileset>* pTilesets);

    void parseTileLayer(TiXmlElement* pTileElement, std::vector<Layer*> *pLayers, const std::vector<Tileset>* pTilesets, std::vector<TileLayer*> *pCollisionLayers, std::vector<TileLayer*> *pRedrawLayers);

    void parseTextures(TiXmlElement* pTextureRoot);

    void parseObjectLayer(TiXmlElement* pObjectElement, std::vector<ObjectLayer*> *pLayers, Level* pLevel);

    int m_tileSize;
    int m_width;
    int m_height;
};
#endif /* defined(__LevelParser__) */