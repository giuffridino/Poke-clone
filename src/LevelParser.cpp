#include "LevelParser.h"
#include "TextureManager.h"
#include "Game.h"
#include "TileLayer.h"
#include "ObjectLayer.h"
#include "base64.h"
#include "ObjectLayer.h"
#include "GameObjectFactory.h"
#include "LoaderParams.h"
#include <memory>
#include "C:/raylib-projects/Poke-clone/zlib128-dll/include/zlib.h" 


Level* LevelParser::parseLevel(const char* levelFile)
{
    std::cout << "Entering parselevel\n";
    TiXmlDocument levelDocument;
    if (!levelDocument.LoadFile(levelFile))
    {
        std::cerr << levelDocument.ErrorDesc() << "\n";
        // return false;
    }

    Level* pLevel = new Level();

    TiXmlElement* pRoot = levelDocument.RootElement();
    pRoot->Attribute("tilewidth", &m_tileSize);
    pRoot->Attribute("width", &m_width);
    pRoot->Attribute("height", &m_height);

    // we know that properties is the first child of the root
    TiXmlElement* pProperties = pRoot->FirstChildElement("properties");
    std::cout << " pRoot->FirstChildElement()->Value(): " << pRoot->FirstChildElement()->Value() << "\n";
    if (pProperties)
    {
        for(TiXmlElement* e = pProperties->FirstChildElement("property"); e != NULL; e = e->NextSiblingElement("property"))
        {
            std::cout << "INSIDE pPROPERTIES FOR LOOP " << e->Value() << "\n";
            parseTextures(e);
            // if(e->Value() == std::string("property"))
            // {
            //     parseTextures(e);
            // }
        }
    }
    else
    {
        std::cout << "No properties found\n";
    }
    // we must parse the textures needed for this level, which have been added to properties
    
    // we must now parse the tilesets
    for(TiXmlElement* e = pRoot->FirstChildElement(); e != NULL; e = e->NextSiblingElement())
    {
        if(e->Value() == std::string("tileset"))
        {
            parseTilesets(e, pLevel->getTilesets());
        }
    }
    // parse any object or tile layers
    for(TiXmlElement* e = pRoot->FirstChildElement(); e != NULL; e = e->NextSiblingElement())
    {
        if(e->Value() == std::string("objectgroup") || e->Value() == std::string("layer"))
        {
            if(e->FirstChildElement()->Value() == std::string("object"))
            {
                std::cout << "parseObjectLayer()\n";
                parseObjectLayer(e, pLevel->getObjectLayers(), pLevel);
            }
            else if(e->FirstChildElement()->Value() == std::string("data") ||
                    (e->FirstChildElement()->NextSiblingElement() != 0 && e->FirstChildElement()->NextSiblingElement()->Value() == std::string("data")))
            {
                std::cout << "parseTileLayer()\n";
                parseTileLayer(e, pLevel->getLayers(), pLevel->getTilesets(), pLevel->getCollisionLayers(), pLevel->getRedrawLayers());
            }
        }
    }
    pLevel->getPlayer()->setCollisionLayers(pLevel->getCollisionLayers());
    pLevel->getPlayer()->setRedrawLayers(pLevel->getRedrawLayers());
    std::cout << "Done with parselevel\n";
    return pLevel;
}

void LevelParser::parseTilesets(TiXmlElement* pTilesetRoot, std::vector<Tileset>* pTilesets)
{
    // std::cout << "Entering parsetilesets\n";
    TheTextureManager::Instance()->load(pTilesetRoot->FirstChildElement()->Attribute("source"), pTilesetRoot->Attribute("name"));
    // std::cout << "Loaded\n";
    Tileset tileset = {0, 0, 0, 0, 0, 0, 0, 0, ""};
    pTilesetRoot->FirstChildElement()->Attribute("width", &tileset.width);
    pTilesetRoot->FirstChildElement()->Attribute("height", &tileset.height);
    pTilesetRoot->Attribute("firstgid", &tileset.firstGridID);
    pTilesetRoot->Attribute("tilewidth", &tileset.tileWidth);
    pTilesetRoot->Attribute("tileheight", &tileset.tileHeight);
    pTilesetRoot->Attribute("spacing", &tileset.spacing);
    pTilesetRoot->Attribute("margin", &tileset.margin);
    tileset.name = pTilesetRoot->Attribute("name");
    tileset.numColumns = tileset.width / (tileset.tileWidth + tileset.spacing);
    std::cout << "parsetilesets tileset.numColumns:" << tileset.numColumns << "\n";
    std::cout << "parsetilesets tileset.width:" << tileset.width << "\n";
    std::cout << "parsetilesets tileset.tileWidth:" << tileset.tileWidth << "\n";
    std::cout << "parsetilesets tileset.spacing:" << tileset.spacing << "\n";

    pTilesets->push_back(tileset);
    // std::cout << "Done parsetilesets\n";
}

void LevelParser::parseTileLayer(TiXmlElement* pTileElement, std::vector<Layer*> *pLayers, const std::vector<Tileset>* pTilesets, std::vector<TileLayer*> *pCollisionLayers, std::vector<TileLayer*> *pRedrawLayers)
{
    TileLayer *pTileLayer = new TileLayer(m_tileSize, *pTilesets);

    bool collidable = false;
    bool redrawable = false;

    std::vector<std::vector<int>> data;

    std::string decodedIDs;
    TiXmlElement* pDataNode = nullptr;


    for (TiXmlElement *e = pTileElement->FirstChildElement(); e != nullptr; e = e->NextSiblingElement())
    {
        if (e->Value() == std::string("properties"))
        {
            for (TiXmlElement *property = e->FirstChildElement(); property != nullptr; property = property->NextSiblingElement())
            {
                if (property->Value() == std::string("property"))
                {
                    if (property->Attribute("name") == std::string("collidable"))
                    {
                        collidable = true;
                    }
                    if (property->Attribute("name") == std::string("redrawable"))
                    {
                        redrawable = true;
                    }
                }
            }
        }
        if (e->Value() == std::string("data"))
        {
            pDataNode = e;
        }
    }

    for (TiXmlNode *e = pDataNode->FirstChild(); e != nullptr; e = e->NextSibling())
    {
        TiXmlText* text = e->ToText();
        std::string t = text->Value();
        decodedIDs = base64_decode(t);
    }

    uLongf sizeofids = m_width * m_height * sizeof(int);
    std::vector<unsigned> ids(sizeofids);
    uncompress((Bytef*)&ids[0], &sizeofids, (const Bytef*)decodedIDs.c_str(), decodedIDs.size());

    std::vector<int> layerRow(m_width);
    for (int j = 0; j < m_height; j++)
    {
        data.push_back(layerRow);
    }

    for (int rows = 0; rows < m_height; rows++)
    {
        for (int cols = 0; cols < m_width; cols++)
        {
            data[rows][cols] = ids[rows * m_width + cols];
        }
    }
    pTileLayer->setTileIDs(data);
    pTileLayer->setMapWidth(m_width);
    if (collidable)
    {
        pCollisionLayers->push_back(pTileLayer);
    }
    else if (redrawable)
    {
        std::cout << "pushing back in pRedrawLayers\n";
        pRedrawLayers->push_back(pTileLayer);
    }
    else
    {
        pLayers->push_back(pTileLayer); 
    }
}

void LevelParser::parseTextures(TiXmlElement *pTextureRoot)
{
    std::cout << "parseTextures value: " << pTextureRoot->Attribute("value") << " name: " << pTextureRoot->Attribute("name") << "\n";
    TheTextureManager::Instance()->load(pTextureRoot->Attribute("value"), pTextureRoot->Attribute("name"));
    // for (TiXmlNode *e = pTextureRoot->FirstChild(); e != nullptr; e = e->NextSiblingElement())
    // {
    //     if (e->Value() == std::string("property"))
    //     {
    //         TheTextureManager::Instance()->load(pTextureRoot->Attribute("value"), pTextureRoot->Attribute("name"));
    //     }
    // }
}

void LevelParser::parseObjectLayer(TiXmlElement* pObjectElement, std::vector<ObjectLayer*> *pLayers, Level* pLevel)
{
    std::cout << "Entering parseObjectLayer\n";
    ObjectLayer* pObjectLayer = new ObjectLayer();

    std::cout << pObjectElement->FirstChildElement()->Value() << "\n";

    for (TiXmlElement* e = pObjectElement->FirstChildElement(); e != nullptr; e = e->NextSiblingElement())
    {
        // std::cout << e->Value() << "\n";
        if (e->Value() == std::string("object"))
        {
            std::string type = e->Attribute("type");
            GameObject* pGameObject = GameObjectFactory::Instance()->create(type);
            if (!pGameObject)
            {
                std::cout << "Failed to create pGameObject: " << type << "\n";
            }
            else
            {
                // pGameObject->load(std::unique_ptr<LoaderParams>( new LoaderParams(textureID, m_position, frameWidth, frameHeight, animRow, animFrame, animNumFrames, frameCounter, frameDelay, facing, callbackID)));
                std::string textureID;
                Vector2 position;
                int x, y;
                int frameWidth = 0, frameHeight = 0;
                int animRow = 0, animFrame = 0, animNumFrames = 0, frameCounter = 0, frameDelay = 10;
                Direction facing = SOUTH;
                int callbackID = 0;

                e->Attribute("x", &x);
                e->Attribute("y", &y);
                position = {(float) x, (float) y};
                for (TiXmlElement* properties = e->FirstChildElement(); properties != nullptr; properties = properties->NextSiblingElement())
                {
                    if (properties->Value() == std::string("properties"))
                    {
                        for(TiXmlElement* property = properties->FirstChildElement(); property != NULL; property = property->NextSiblingElement())
                        {
                            if(property->Value() == std::string("property"))
                            {
                                if (property->Attribute("name") == std::string("textureID"))
                                {
                                    textureID = property->Attribute("value");
                                }
                                else if (property->Attribute("name") == std::string("width"))
                                {
                                    property->Attribute("value", &frameWidth);
                                }
                                else if (property->Attribute("name") == std::string("height"))
                                {
                                    property->Attribute("value", &frameHeight);
                                }
                                else if (property->Attribute("name") == std::string("animRow"))
                                {
                                    property->Attribute("value", &animRow);
                                }
                                else if (property->Attribute("name") == std::string("animFrame"))
                                {
                                    property->Attribute("value", &animFrame);
                                }
                                else if (property->Attribute("name") == std::string("animNumFrames"))
                                {
                                    // std::cout << "Setting up animNumFrames: " << property->Attribute("value") << "\n";
                                    property->Attribute("value", &animNumFrames);
                                }
                                else if (property->Attribute("name") == std::string("frameCounter"))
                                {
                                    property->Attribute("value", &frameCounter);
                                }
                                else if (property->Attribute("name") == std::string("frameDelay"))
                                {
                                    property->Attribute("value", &frameDelay);
                                }
                                else if (property->Attribute("name") == std::string("facing"))
                                {
                                    facing = stringToDirection(property->Attribute("value"));
                                }
                                else if (property->Attribute("name") == std::string("callbackID"))
                                {
                                    property->Attribute("value", &callbackID);
                                }
                            }
                        }
                    }
                }
                pGameObject->load(std::unique_ptr<LoaderParams>( new LoaderParams(textureID, position, frameWidth, frameHeight, animRow, animFrame, animNumFrames, frameCounter, frameDelay, facing, callbackID)));
                if (type == "Player")
                {
                    pLevel->setPlayer(dynamic_cast<Player*>(pGameObject));
                }
                pObjectLayer->getGameObjects()->push_back(pGameObject);
            }
            // std::cout << "x: " << x << "\n";
            // std::cout << "y: " << y << "\n";
            // std::cout << "width: " << width << "\n";
            // std::cout << "height: " << height << "\n";
            // std::cout << "textureID: " << textureID << "\n";
            // std::cout << "numFrames: " << numFrames << "\n";
            // std::cout << "callbackID: " << callbackID << "\n";
            // std::cout << "animSpeed: " << animSpeed << "\n";
        }
    }
    pLayers->push_back(pObjectLayer);
    std::cout << "Done with parseObjectLayer\n";
}