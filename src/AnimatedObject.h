#pragma once
#ifndef __AnimatedObject__
#define __AnimatedObject__

#include "TrainerObject.h"
#include "GameObjectFactory.h"

class AnimatedObject : public TrainerObject
{
public:
	AnimatedObject(void);
	virtual ~AnimatedObject(void){};

	virtual void load(const std::unique_ptr<LoaderParams> &pParams);

	virtual void draw(void);
	virtual void update(void);
	virtual void clean(void);
	virtual std::string type(void) { return "AnimatedObject"; }
};

class AnimatedObjectCreator : public BaseCreator
{
	GameObject* createGameObject() const
	{
		return new AnimatedObject();
	}
};

#endif /* defined(__AnimatedObject__) */