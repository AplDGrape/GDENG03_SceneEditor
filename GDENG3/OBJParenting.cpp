#include "OBJParenting.h"
#include "AGameObject.h"

OBJParenting::OBJParenting(AGameObject* owner) : owner(owner) {}

OBJParenting::~OBJParenting() {}

void OBJParenting::setParent(AGameObject* newParent)
{
    if (parent != nullptr)
        parent->getParenting()->removeChild(owner);

    parent = newParent;

    if (newParent != nullptr)
        newParent->getParenting()->children.push_back(owner);
}

void OBJParenting::removeParent()
{
    if (parent != nullptr)
    {
        parent->getParenting()->removeChild(owner);
        parent = nullptr;
    }
}

AGameObject* OBJParenting::getParent() const
{
    return parent;
}

void OBJParenting::removeChild(AGameObject* child)
{
    children.erase(std::remove(children.begin(), children.end(), child), children.end());
}

const std::vector<AGameObject*>& OBJParenting::getChildren() const
{
    return children;
}

void OBJParenting::updateTransformFromParent()
{
    if (parent && !owner->hasPhysics())
        owner->ComputeLocalMatrix();

    for (AGameObject* child : children)
        child->getParenting()->updateTransformFromParent();
}

bool OBJParenting::isAncestorOf(AGameObject* potentialChild) const
{
    AGameObject* current = potentialChild->getParenting()->getParent();

    while (current != nullptr)
    {
        if (current == owner)
            return true;
        current = current->getParenting()->getParent();
    }

    return false;
}
