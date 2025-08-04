#pragma once

#include <vector>
#include <algorithm>

class AGameObject;

class OBJParenting
{
public:
    OBJParenting(AGameObject* owner);
    ~OBJParenting();

    void setParent(AGameObject* newParent);
    void removeParent();
    AGameObject* getParent() const;

    void removeChild(AGameObject* child);
    const std::vector<AGameObject*>& getChildren() const;

    void updateTransformFromParent();
    bool isAncestorOf(AGameObject* potentialChild) const;

private:
    AGameObject* owner = nullptr;
    AGameObject* parent = nullptr;
    std::vector<AGameObject*> children;
};
