#pragma once
#ifndef __Layer__
#define __Layer__

class Map;

class Layer
{
public:
    virtual void update(Map *pMap) = 0;
    virtual void render(Map *pMap) = 0;

    virtual ~Layer(void) {};
};
#endif /* defined(__Layer__) */