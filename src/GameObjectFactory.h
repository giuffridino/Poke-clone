#pragma once
#ifndef __GameObjectFactory__
#define __GameObjectFactory__

#include <string>
#include <map>
#include <iostream>
#include "GameObject.h"

class BaseCreator
{
public:
    virtual GameObject* createGameObject(void) const = 0;
	virtual ~BaseCreator(void) {};
};

class GameObjectFactory
{
public:
    static GameObjectFactory* Instance(void)
	{
		if (s_pInstance == 0)
		{
			s_pInstance = new GameObjectFactory();
		}
		return s_pInstance;
	}

    bool registerType(std::string typeID, BaseCreator* pCreator)
    {
        std::map<std::string, BaseCreator*>::iterator it = m_creators.find(typeID);
        bool success = m_creators.end() == it;
        if (success)
        {
            m_creators[typeID] = pCreator;
        }
        else
        {            
            delete pCreator;
        }
        return success;
    }

    GameObject* create(std::string typeID)
    {
        std::map<std::string, BaseCreator*>::iterator it = m_creators.find(typeID);
        bool success = m_creators.end() != it;
        GameObject *result;
        if (success)
        {
            BaseCreator* pCreator = (*it).second;
            result = pCreator->createGameObject();
        }
        else
        {
            std::cout << "Could not find type: " << typeID << "\n";
            result = nullptr;
        }
        
        return result;
    }

private:
    GameObjectFactory(void) {};
    ~GameObjectFactory(void) {};

    static GameObjectFactory* s_pInstance;

    std::map<std::string, BaseCreator*> m_creators;
};

typedef GameObjectFactory TheGameObjectFactory;

// GameObjectFactory* GameObjectFactory::s_pInstance = 0;

#endif /* defined(__GameObjectFactory__) */