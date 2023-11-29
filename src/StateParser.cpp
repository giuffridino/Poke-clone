#include "StateParser.h"
#include "TextureManager.h"
#include "Game.h"
#include "GameObjectFactory.h"
#include "LoaderParams.h"

bool StateParser::parseState(const char *stateFile, std::string stateID, std::vector<GameObject *> *pObjects, std::vector<std::string> *pTextureIDs)
{
    TiXmlDocument xmlDoc;
    if (!xmlDoc.LoadFile(stateFile))
    {
        std::cerr << xmlDoc.ErrorDesc() << "\n";
        return false;
    }

    TiXmlElement *pRoot = xmlDoc.RootElement();
    if (!pRoot)
    {
        std::cout << "ERROR - p root = nullptr\n";
        return false;
    }

    // pre declare the states root node
    TiXmlElement* pStateRoot = 0;
    for(TiXmlElement* e = pRoot->FirstChildElement(); e != NULL; e = e->NextSiblingElement())
    {
        if(e->Value() == stateID)
        {
            pStateRoot = e;
			break;
        }
    }
    // pre declare the texture root
    TiXmlElement* pTextureRoot = 0;
    for(TiXmlElement* e = pStateRoot->FirstChildElement(); e != NULL; e = e->NextSiblingElement())
    {
        std::cout << "trying to call std::string(\"TEXTURES\")\n";
        if(e->Value() == std::string("TEXTURES"))
        {
            std::cout << "texture was found\n";
            pTextureRoot = e;
			break;
        }
    }
    std::cout << "About to parseTextures\n";
    parseTextures(pTextureRoot, pTextureIDs);
    std::cout << "Textures parsed\n";
    // pre declare the object root node
    TiXmlElement* pObjectRoot = 0;
    for(TiXmlElement* e = pStateRoot->FirstChildElement(); e != NULL; e = e->NextSiblingElement())
    {
        std::cout << "trying to call std::string(\"OBJECTS\")\n";
        if(e->Value() == std::string("OBJECTS"))
        {
            pObjectRoot = e;
			break;
        }
    }
    parseObjects(pObjectRoot, pObjects);
    return true;

    // TiXmlElement *pStateRoot = getFirstChildByID(pRoot, stateID);
    // if (!pStateRoot)
    // {
    //     std::cout << "ERROR - pState root = nullptr\n";
    //     return false;
    // }

    // TiXmlElement *pTextureRoot = getFirstChildByID(pStateRoot, std::string("texture"));
    // if (!pTextureRoot)
    // {
    //     std::cout << "ERROR - pTexture root = nullptr\n";
    //     return false;
    // }
    // parseTextures(pTextureRoot, pTextureIDs);

    // TiXmlElement *pObjectRoot = getFirstChildByID(pStateRoot, std::string("object"));
    // if (!pObjectRoot)
    // {
    //     std::cout << "ERROR - pObject root = nullptr\n";
    //     return false;
    // }
    // parseObjects(pObjectRoot, pObjects);

    return true;
}

TiXmlElement *StateParser::getFirstChildByID(TiXmlElement *pParent, std::string childID)
{
    if (!pParent)
    {
        std::cout << "*pParent in getFirstChildByID is null when calling the childID:" << childID << "\n";
    }
    
    for (TiXmlElement *e = pParent->FirstChildElement(); e != nullptr; e = e->NextSiblingElement())
    {
        if (e->Value() == childID)
        {
            return e;
        }
    }
    return nullptr;
}

void StateParser::parseObjects(TiXmlElement *pStateRoot, std::vector<GameObject *> *pObjects)
{
    for (TiXmlElement *e = pStateRoot->FirstChildElement(); e != nullptr; e = e->NextSiblingElement())
    {
        int x = 0;
        e->Attribute("x", &x);
        int y = 0;
        e->Attribute("y", &y);
        Vector2 position = {(float) x, (float) y};
        int frameWidth = 0;
        e->Attribute("frameWidth", &frameWidth);
        int frameHeight = 0;
        e->Attribute("frameHeight", &frameHeight);
        // int scale = 1.0;
        // e->Attribute("scale", &scale);
        int animRow = 0;
        e->Attribute("animRow", &animRow);
        int animFrame = 0;
        e->Attribute("animFrame", &animFrame);
        int animNumFrames = 1;
        e->Attribute("animNumFrames", &animNumFrames);
        int frameCounter = 0;
        e->Attribute("frameCounter", &frameCounter);
        int frameDelay = 1;
        e->Attribute("frameDelay", &frameDelay);
        int callbackID = 0;
        Direction facing = stringToDirection(e->Attribute("facing"));
        e->Attribute("callbackID", &callbackID);
        std::string textureID = e->Attribute("textureID");
        std::string interactionText = e->Attribute("interactionText");


        GameObject *pGameObject = GameObjectFactory::Instance()->create(e->Attribute("type"));
        pGameObject->load(std::unique_ptr<LoaderParams>(new LoaderParams(textureID, position, frameWidth, frameHeight, animRow, animFrame, animNumFrames, frameCounter, frameDelay, facing, callbackID, interactionText)));
        pObjects->push_back(pGameObject);
    }
}

void StateParser::parseTextures(TiXmlElement *pStateRoot, std::vector<std::string> *pTextureIDs)
{
    for (TiXmlElement *e = pStateRoot->FirstChildElement(); e != nullptr; e = e->NextSiblingElement())
    {
        std::string filename = e->Attribute("filename");
        std::string ID = e->Attribute("ID");
        std::cout << "filename = " << filename << " and id = " << ID << "\n";
        pTextureIDs->push_back(ID);
        TheTextureManager::Instance()->load(filename, ID);
    }
}
