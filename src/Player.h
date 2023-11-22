#pragma once
#ifndef __Player__
#define __Player__

#include "raylib.h"
#include <string>
#include <vector>
#include "TrainerObject.h"
#include "Constants.h"
#include "GameObjectFactory.h"
// #include "CollisionManager.h"

class TileLayer;

class Player : public TrainerObject
{
public:
    Player();
    ~Player();
    virtual void load(const std::unique_ptr<LoaderParams> &pParams);
    virtual void update();
    virtual void draw();
    virtual void clean() {};
    virtual std::string type() { return "Player"; }

    Direction getInputDirection();
    Vector2 getPosition() { return m_position; }
    int getWidth() { return m_frameWidth; }

    std::vector<TileLayer*>* getCollisionLayers() { return m_collisionLayers; }
    void setCollisionLayers(std::vector<TileLayer*>* layers) { m_collisionLayers = layers; }
    bool checkPlayerTileCollision();

private:
    std::vector<TileLayer*>* m_collisionLayers;
    // Texture2D m_texture;
    // std::string m_textureID;
    // Vector2 m_position = {0.0f, 0.0f};
    // bool m_bIsMoving = false;

    // const int m_frameWidth = 16;
    // const int m_frameHeight = 32;
    // int m_animRow = 0;
    // int m_animFrame = 0;
    // int m_animNumFrames = 4;
    // int m_frameDelay = 10;
    // int m_frameCounter = 0;

    // Direction m_facing = SOUTH;
    // Direction m_lastFacing = SOUTH;
    // int m_moveTime = 0;
    // int m_framesToCrossOneTile = 8;  //enable a selection switch between 8 and 4 (faster) for the user in order to speed up movement (nice feature)
    // int m_speed = 64 / m_framesToCrossOneTile;

};

class PlayerCreator : public BaseCreator
{
	GameObject* createGameObject(void) const
	{
		return new Player();
	}
};

#endif /* defined(__Player__) */