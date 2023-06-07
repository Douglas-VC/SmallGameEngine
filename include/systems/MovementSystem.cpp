#include <SDL2/SDL.h>
#include "MovementSystem.h"
#include "../Random.h"
#include "../components/Transform.h"
#include "../components/Sprite.h"

void MovementSystem::onKeyDown(const KeyDown& key_down) noexcept {
}

void MovementSystem::onKeyUp(const KeyUp& key_up) noexcept {
}

float randDir(const float vel) {
    switch (randomInt(0, 1)) {
        case 0:
            return vel;

        case 1:
            return -vel;
    }
}

void MovementSystem::update(SoundManager *soundManager, FontManager *fontManager, Window &window, entt::registry& registry) {
}
