#pragma once
#ifndef __MenuButton__
#define __MenuButton__

#include "TrainerObject.h"
#include "GameObjectFactory.h"

class MenuButton : public TrainerObject
{
public:
	MenuButton(void);
	~MenuButton(void){};

	void load(const std::unique_ptr<LoaderParams> &pParams);
	void draw(void);
	void update(void);
	void clean(void);
	virtual void collision(void) {};
	void setCallback(void (*pCallback)()) { m_callback = pCallback; }
	int getCallbackID(void) { return m_callbackID; }

private:
	enum button_state
    {
        MOUSE_OUT = 0,
        MOUSE_OVER = 1,
        CLICKED = 2
    };

	bool m_bReleased;
	bool m_bRunCallback;
	bool m_bWasOutOfBounds;

	int m_callbackID;

	void (*m_callback)(void);
};

class MenuButtonCreator : public BaseCreator
{
	GameObject* createGameObject(void) const
	{
		return new MenuButton();
	}
};

#endif /* defined(__MenuButton__) */