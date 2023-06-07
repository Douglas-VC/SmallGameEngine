#ifndef PONG_GAME_H
#define PONG_GAME_H
#include <SDL2/SDL.h>
#include "../entt/entt.hpp"
#include "Window.h"

#include "systems/RenderSystem.h"
#include "systems/MovementSystem.h"
#include "systems/CollisionSystem.h"

#include "FontManager.h"
#include "SoundManager.h"

class Game {
private:
    bool running;
    Window window;
    entt::registry registry;
    entt::dispatcher dispatcher;

    RenderSystem renderSystem;
    MovementSystem movementSystem;
    CollisionSystem collisionSystem;

    CollisionSystem::CollisionHolder collisionHolder{};

    FontManager fontManager;
    SoundManager soundManager;

public:
    Game(const char* title, int xPos, int yPos, int width, int height, bool fullScreen);
    ~Game();

    void init();

private:
    void gameLoop();
    void handleEvents();
    void update();
    void render();
};

#endif //PONG_GAME_H