#pragma once
#ifndef __TrainerObject__
#define __TrainerObject__

#include "GameObject.h"
#include <string>
#include <memory>

class LoaderParams;

class TrainerObject : public GameObject
{
public:
    virtual ~TrainerObject(void) {} // For polymorphism
    // virtual void load(void);
    virtual void load(const std::unique_ptr<LoaderParams> &pParams);
    virtual void draw(void);
    virtual void update(void);
    virtual void clean(void){};
    virtual void collision(void) {};
    virtual std::string type(void) { return "TrainerObject"; }

protected:
    TrainerObject(void);

    // void doDyingAnimation(void);

    // int m_bulletFiringSpeed, m_bulletCounter;
    // int m_moveSpeed;
    // int m_dyingTime, m_dyingCounter;
    // bool m_bPlayedDeathSound;
};

#endif /* defined(__TrainerObject__) */