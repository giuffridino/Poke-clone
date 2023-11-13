#pragma once
#ifndef __TextureManager__
#define __TextureManager__

#include "raylib.h"
#include <map>
#include <string>

class TextureManager
{
public:
    static TextureManager* Instance(void)
    {
        if (s_pInstance == nullptr)
        {
            s_pInstance = new TextureManager();
        }
        return s_pInstance;        
    }

    bool load(std::string fileName, std::string id);
    void clearTextureMap(void);
    void unload(std::string id);
    // Draw
    // void draw(std::string id, int x, int y, int width, int height, double scale, double rotation, double alpha);

    // Draw frame
    void drawFrame(std::string id, int x, int y, int width, int height, int currentRow, int currentFrame, Vector2 origin);

    // Draw tile from tileset
    // void drawTile(std::string id, int margin, int spacing, int x, int y, int width, int height, int currentRow, int currentFrame);

    std::map<std::string, Texture2D> getTextureMap() { return m_textureMap; }
    
private:
    TextureManager(void) {};
    ~TextureManager(void) {};
    static TextureManager* s_pInstance;
    std::map<std::string, Texture2D> m_textureMap;
    
};

typedef TextureManager TheTextureManager;

#endif /* defined(__TextureManager__) */