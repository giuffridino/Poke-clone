#pragma once
#ifndef __InteractableObject__
#define __InteractableObject__

#include "TrainerObject.h"
#include "GameObjectFactory.h"
#include <string>

class InteractableObject : public TrainerObject
{
public:
	InteractableObject(void);
	virtual ~InteractableObject(void){};

	virtual void load(const std::unique_ptr<LoaderParams> &pParams);

	virtual void draw(void){};
	virtual void update(void){};
	virtual void clean(void){};
	virtual std::string type(void) { return "InteractableObject"; }

// private:
// 	std::string m_interactionText = "";
};

class InteractableObjectCreator : public BaseCreator
{
	GameObject* createGameObject() const
	{
		return new InteractableObject();
	}
};

#endif /* defined(__InteractableObject__) */