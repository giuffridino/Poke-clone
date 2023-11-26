#pragma once
#ifndef __GrassObject__
#define __GrassObject__

#include "TrainerObject.h"
#include "GameObjectFactory.h"

class GrassObject : public TrainerObject
{
public:
	GrassObject(void);
	virtual ~GrassObject(void){};

	virtual void load(const std::unique_ptr<LoaderParams> &pParams);

	virtual void draw(void);
	virtual void update(void);
	virtual void clean(void);
	virtual std::string type(void) { return "GrassObject"; }

    void performAnimation(void);
    bool updating(void) { return m_bUpdating; }
    void setUpdating(bool updating) { m_bUpdating = updating;}

private:
    int m_delay = 0;
    // bool m_bUpdating = false;
};

class GrassObjectCreator : public BaseCreator
{
	GameObject* createGameObject() const
	{
		return new GrassObject();
	}
};

#endif /* defined(__GrassObject__) */