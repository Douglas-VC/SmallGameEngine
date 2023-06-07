#ifndef PONG_COLLISIONSYSTEM_H
#define PONG_COLLISIONSYSTEM_H

#include "../../entt/entt.hpp"
#include "../SoundManager.h"

class CollisionSystem {
public:
    CollisionSystem() = default;
    ~CollisionSystem() = default;

    struct CollisionHolder {

        entt::registry* registry;
    };

    void update(SoundManager *soundManager, CollisionHolder &collisionHolder);
};

#endif //PONG_COLLISIONSYSTEM_H
