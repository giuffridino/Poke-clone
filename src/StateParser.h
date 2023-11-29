#pragma once
#ifndef __StateParser__
#define __StateParser__

#include <iostream>
#include <vector>
#include "tinyxml.h"

class GameObject;

class StateParser
{
public:
	bool parseState(const char* stateFile, std::string stateID, std::vector<GameObject*> *pObjects, std::vector<std::string> *pTextureIDs);

private:
	TiXmlElement *getFirstChildByID(TiXmlElement *pParent, std::string childID);
	void parseObjects(TiXmlElement* pStateRoot, std::vector<GameObject*> *pObjects);
    void parseTextures(TiXmlElement* pStateRoot, std::vector<std::string> *pTextureIDs);
};

#endif /* defined(__StateParser__) */