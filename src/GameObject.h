
#pragma once
#ifndef __GameObject__
#define __GameObject__

#include "raylib.h"
#include <string>
#include <memory>
#include "Constants.h"
// #include "Vector2D.h"

class LoaderParams;

class GameObject
{
public:
	virtual ~GameObject(void){};
	virtual void load(const std::unique_ptr<LoaderParams> &pParams) = 0;
	// virtual void load(const std::unique_ptr<LoaderParams> &pParams) = 0;
	virtual void draw(void) = 0;
	virtual void update(void) = 0;
	virtual void clean(void) = 0;
	// virtual void collision(void) = 0;
	virtual std::string type(void) = 0;

	Vector2& getPosition(void) { return m_position; }

	int getWidth(void) { return m_frameWidth; }
	int getHeight(void) { return m_frameHeight; }

	// void scroll(float scrollSpeed) 
	// {
	// 	if (type() != std::string("Player"))
	// 	{
	// 		m_position.x = (m_position.x - scrollSpeed);
	// 	}
	// }

	void setUpdating(bool updating) { m_bUpdating = updating; }
	// bool updating(void) { return m_bUpdating; }
	bool dead(void) { return m_bDead; }
	// bool dying(void) { return m_bDying; }

	std::string getTextureID(void) { return m_textureID; }

protected:
	GameObject(void) : m_textureID(""),
	m_position{0.0f, 0.0f}, 
	m_bIsMoving(false),
	m_frameWidth(0), m_frameHeight(0),
	m_animRow(0), m_animFrame(0), m_animNumFrames(1), m_frameCounter(0), m_frameDelay(10),
	m_facing(SOUTH), m_lastFacing(SOUTH),
	m_moveTime(0), m_framesToCrossOneTile(8), m_speed(16/m_framesToCrossOneTile),
	m_bUpdating(false), m_bDead(false)
	{
	}

	std::string m_textureID;	
	Vector2 m_position;
	bool m_bIsMoving;
	int m_frameWidth, m_frameHeight;
	int m_animRow, m_animFrame, m_animNumFrames, m_frameCounter, m_frameDelay;
	Direction m_facing, m_lastFacing;
	int m_moveTime, m_framesToCrossOneTile, m_speed;
	bool m_bUpdating, m_bDead;
	// bool m_bDying;
	// // Flip
	// SDL_RendererFlip m_flip;
	// Object variables
	// double m_scale, m_rotation, m_alpha;

	// Texture2D m_texture;
    // std::string m_textureID;
    // Vector2 m_position = {0.0f, 0.0f};
    // bool m_bIsMoving = false;

    // const int m_frameWidth = 16;
    // const int m_frameHeight = 32;
    // int m_animRow = 0;
    // int m_animFrame = 0;
    // int m_animNumFrames = 4;
    // int m_frameCounter = 0;
    // int m_frameDelay = 10;

    // Direction m_facing = SOUTH;
    // Direction m_lastFacing = SOUTH;
    // int m_moveTime = 0;
    // int m_framesToCrossOneTile = 8;  //enable a selection switch between 8 and 4 (faster) for the user in order to speed up movement (nice feature)
    // int m_speed = 64 / m_framesToCrossOneTile;
};

#endif /* defined(__GameObject__) */