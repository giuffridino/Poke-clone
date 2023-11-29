#pragma once
#ifndef __MapParser__
#define __MapParser__

#include "Map.h"
#include "tinyxml.h"
#include <vector>

class MapParser
{
public:
    Map* parseMap(const char* mapFile);

private:
    void parseTilesets(TiXmlElement* pTilesetRoot, std::vector<Tileset>* pTilesets);

    void parseTileLayer(TiXmlElement* pTileElement, std::vector<Layer*> *pLayers, const std::vector<Tileset>* pTilesets, std::vector<TileLayer*> *pCollisionLayers, std::vector<TileLayer*> *pRedrawLayers);

    void parseTextures(TiXmlElement* pTextureRoot);

    void parseObjectLayer(TiXmlElement* pObjectElement, std::vector<ObjectLayer*> *pLayers, Map* pMap);

    int m_tileSize;
    int m_width;
    int m_height;
};
#endif /* defined(__MapParser__) */