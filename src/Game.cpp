#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <chrono>

#include "../include/Game.h"
#include "../entt/entt.hpp"
#include "../include/components/Transform.h"
#include "../include/components/Sprite.h"
#include "../include/components/Collider.h"

Game::Game(const char* title, int xPos, int yPos, int width, int height, bool fullScreen) :
            running{}, window{} {
    if (SDL_Init(SDL_INIT_EVERYTHING) == -1) {
        std::cerr << "ERROR: Unable to initialize SDL: " << SDL_GetError() << std::endl;
        return;
    }
    std::cout << "SDL Subsystems Initialized..." << std::endl;

    if (IMG_Init(IMG_INIT_PNG) != IMG_INIT_PNG) {
        std::cerr << "ERROR: Unable to initialize Image library: " << SDL_GetError() << std::endl;
        return;
    }
    std::cout << "SDL Image library loaded!" << std::endl;

    window.create(title, xPos, yPos, width, height, fullScreen);

    fontManager.renderer = window.getRenderer();

    running = true;
}

Game::~Game() {
    IMG_Quit();
    SDL_Quit();
    std::cout << "Game cleaned!" << std::endl;
}

void Game::init() {
    gameLoop();
}

using namespace std::literals;
auto constexpr dt = std::chrono::duration<long long, std::ratio<1, 60>>{1};
using Clock = std::chrono::steady_clock;
using duration = decltype(Clock::duration{} + dt);
using time_point = std::chrono::time_point<Clock, duration>;

void Game::gameLoop() {
    time_point t {};
    time_point currentTime = Clock::now();
    duration accumulator = 0s;

    while(running) {
        handleEvents();

        time_point newTime = Clock::now();
        auto frameTime = newTime - currentTime;
        if (frameTime > 250ms)
            frameTime = 250ms;
        currentTime = newTime;

        accumulator += frameTime;

        while (accumulator >= dt) {
            update();
            t += dt;
            accumulator -= dt;
        }
        render();
    }
}

void Game::handleEvents() {
    SDL_PollEvent(&window.event);
    switch (window.event.type) {
        case SDL_QUIT:
            running = false;
            break;

        case SDL_KEYDOWN:
            dispatcher.trigger(KeyDown{window.event.key.keysym.sym});
            break;

        case SDL_KEYUP:
            dispatcher.trigger(KeyUp{window.event.key.keysym.sym});
            break;

        default:
            break;
    }
}

void Game::update() {
    movementSystem.update(&soundManager, &fontManager, window, registry);
    collisionSystem.update(&soundManager, collisionHolder);
}

void Game::render() {
    SDL_RenderClear(window.getRenderer());

    renderSystem.render(window.getRenderer(), registry);

    SDL_RenderPresent(window.getRenderer());
}