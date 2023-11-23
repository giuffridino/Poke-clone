#pragma once
#ifndef __Layer__
#define __Layer__

class Level;

class Layer
{
public:
    virtual void update(Level *pLevel) = 0;
    virtual void render(Level *pLevel) = 0;

    virtual ~Layer(void) {};
};
#endif /* defined(__Layer__) */