#include "TextureManager.h"
#include <iostream>

TextureManager* TextureManager::s_pInstance = nullptr;

bool TextureManager::load(std::string fileName, std::string id)
{
    std::cout << "Loading texture: " << fileName << " with id: " << id << "\n";
    Texture2D texture = LoadTexture(fileName.c_str());
    if(texture.id != (unsigned int) -1)
    {
        m_textureMap[id] = texture;
        return true;
    }
    return false;
}

// void TextureManager::draw(std::string id, int x, int y, int width, int height, double scale, double rotation, Vector2 origin)
// {
//     drawFrame(id, x, y, width, height, 0, 0, scale, rotation, alpha);
// }

void TextureManager::drawFrame(std::string id, int x, int y, int width, int height, int currentRow, int currentFrame, Vector2 origin)
{
    // std::cout << "Calling TextureManager::drawFrame()\n";
    Rectangle srcRect;
    Rectangle destRect;
    srcRect.x = width * currentFrame;
    srcRect.y = height * currentRow;
    srcRect.width = width;
    srcRect.height = height;
    destRect.x = x;
    destRect.y = y;
    destRect.width = width;
    destRect.height = height;

    // std::cout << "Drawing frame with id: " << id << " " << x << " " << y << " " << width <<  " " << height << "\n";
    // std::cout << "srcRect: " << srcRect.x << " " << srcRect.y << " " << srcRect.width <<  " " << srcRect.height << "\n";
    // std::cout << "destRect: " << destRect.x << " " << destRect.y << " " << destRect.width <<  " " << destRect.height << "\n";
    // std::cout << "m_textureMap[id].id = " << m_textureMap[id].id << "\n";
    DrawTexturePro(m_textureMap[id], srcRect, destRect, origin, 0.0f, WHITE);
}

void TextureManager::drawTile(std::string id, int margin, int spacing, int x, int y, int width, int height, int currentRow, int currentFrame)
{
    Rectangle srcRect, destRect;
    srcRect.x = margin + (spacing + width) * currentFrame;
    srcRect.y = margin + (spacing + height) * currentRow;
    destRect.x = x;
    destRect.y = y;
    srcRect.width = destRect.width = width;
    srcRect.height = destRect.height = height;
    DrawTexturePro(m_textureMap[id], srcRect, destRect, Vector2{0.0f, 0.0f}, 0.0f, WHITE);
    // SDL_RenderCopyEx(pRenderer, m_textureMap[id], &srcRect, &destRect, 0, 0, SDL_FLIP_NONE);
}

void TextureManager::clearTextureMap(void)
{
    m_textureMap.clear();
}

void TextureManager::unload(std::string id)
{
    UnloadTexture(m_textureMap[id]);
}