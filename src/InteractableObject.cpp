#include "InteractableObject.h"


InteractableObject::InteractableObject(void) : TrainerObject() { }

void InteractableObject::load(std::unique_ptr<LoaderParams> const &pParams)
{
    TrainerObject::load((pParams));
}